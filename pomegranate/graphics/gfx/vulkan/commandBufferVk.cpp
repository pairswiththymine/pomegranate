#include "pch.hpp"

#include "commandBufferVk.hpp"

#include "bufferVk.hpp"
#include "contextVk.hpp"
#include "descriptorSetVk.hpp"
#include "gfxVk.hpp"
#include "instanceVk.hpp"
#include "pipelineLayoutVk.hpp"
#include "pipelineVk.hpp"
#include "textureVk.hpp"

namespace pom::gfx {
    CommandBufferVk::CommandBufferVk(InstanceVk* instance, CommandBufferSpecialization specialization, u32 count) :
        CommandBuffer(specialization), instance(instance),
        pool(specialization == CommandBufferSpecialization::TRANSFER ? instance->transferCommandPool
                                                                     : instance->graphicsCommandPool),
        count(count)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(count <= POM_MAX_FRAMES_IN_FLIGHT,
                   "Command buffers are only meant to hold less than the number of frames in flight, try using "
                   "multiple command buffers.");

        VkFenceCreateInfo fenceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT,
        };

        VkCommandBufferAllocateInfo commandBufferAllocateCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext = nullptr,
            .commandPool = pool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, // TODO: secondary command buffers how? doesn't make sense in gl?
            .commandBufferCount = count,
        };

        for (u32 i = 0; i < count; i++) {
            POM_CHECK_VK(vkCreateFence(instance->getVkDevice(), &fenceCreateInfo, nullptr, &recordingFences[i]),
                         "Failed to create recording fence");

            POM_CHECK_VK(
                vkAllocateCommandBuffers(instance->getVkDevice(), &commandBufferAllocateCreateInfo, commandBuffers),
                "Failed to allocate command buffers.");
        }
    }

    CommandBufferVk::~CommandBufferVk()
    {
        POM_PROFILE_FUNCTION();
        vkWaitForFences(instance->getVkDevice(), count, recordingFences, VK_TRUE, UINT64_MAX);
        for (auto& recordingFence : recordingFences) {
            vkDestroyFence(instance->getVkDevice(), recordingFence, nullptr);
        }

        vkFreeCommandBuffers(instance->getVkDevice(), pool, count, commandBuffers);
    }

    void CommandBufferVk::begin()
    {
        POM_PROFILE_FUNCTION();
        // currentIndex = (currentIndex + 1) % count;

        vkWaitForFences(instance->getVkDevice(), 1, &getCurrentRecordingFence(), VK_TRUE, UINT32_MAX);
        vkResetFences(instance->getVkDevice(), 1, &getCurrentRecordingFence());

        VkCommandBufferBeginInfo commandBufferBeginInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,
            .flags = 0,
            .pInheritanceInfo = nullptr,
        };

        POM_CHECK_VK(vkBeginCommandBuffer(getCurrentCommandBuffer(), &commandBufferBeginInfo),
                     "Failed to begin recording command buffer.");
    }

    void CommandBufferVk::beginRenderPass(Ref<RenderPass> renderPass, Context* context)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(renderPass->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched render pass api.");
        POM_ASSERT(context->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched context api.");
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        auto* rp = dynamic_cast<RenderPassVk*>(renderPass.get());
        auto* ctx = dynamic_cast<ContextVk*>(context);

        VkRenderPassBeginInfo renderPassBeginInfo = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = rp->getHandle(),
            .framebuffer = ctx->swapchainFramebuffers[ctx->swapchainImageIndex],
            .renderArea = { .offset = { 0, 0 }, .extent = ctx->swapchainExtent },
            .clearValueCount = rp->getClearColorCountVk(),
            .pClearValues = rp->getClearColorsVk(),
        };

        vkCmdBeginRenderPass(getCurrentCommandBuffer(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void CommandBufferVk::endRenderPass()
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        vkCmdEndRenderPass(getCurrentCommandBuffer());
    }

    void CommandBufferVk::end()
    {
        POM_PROFILE_FUNCTION();
        POM_CHECK_VK(vkEndCommandBuffer(getCurrentCommandBuffer()), "Failed to end recording command buffer.");
    }

    void CommandBufferVk::submit()
    {
        POM_PROFILE_FUNCTION();
        VkSubmitInfo submitInfo = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .pWaitDstStageMask = nullptr,
            .commandBufferCount = 1,
            .pCommandBuffers = &getCurrentCommandBuffer(),
            .signalSemaphoreCount = 0,
            .pSignalSemaphores = nullptr,
        };

        VkQueue queue = specialization == CommandBufferSpecialization::TRANSFER ? instance->transferQueue
                                                                                : instance->graphicsQueue;

        POM_CHECK_VK(vkQueueSubmit(queue, 1, &submitInfo, getCurrentRecordingFence()), "Failed to submit to queue");
    }

    void CommandBufferVk::setViewport(const Viewport& viewport)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        const VkViewport v = toVkViewport(viewport);
        vkCmdSetViewport(getCurrentCommandBuffer(), 0, 1, &v);
    }

    void CommandBufferVk::setScissor(const maths::ivec2& offset, const maths::uvec2& extent)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        VkRect2D scissor { .offset = { offset.x, offset.y }, .extent = { extent.x, extent.y } };
        vkCmdSetScissor(getCurrentCommandBuffer(), 0, 1, &scissor);
    }

    void CommandBufferVk::draw(u32 vertexCount, u32 vertexOffset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        vkCmdDraw(getCurrentCommandBuffer(), vertexCount, 1, vertexOffset, 0);
    }

    void CommandBufferVk::drawInstanced(u32 vertexCount, u32 instanceCount, u32 vertexOffset, u32 instanceOffset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        vkCmdDraw(getCurrentCommandBuffer(), vertexCount, instanceCount, vertexOffset, instanceOffset);
    }

    void CommandBufferVk::drawIndexed(u32 indexCount, u32 firstIndex, i32 vertexOffset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        vkCmdDrawIndexed(getCurrentCommandBuffer(), indexCount, 1, firstIndex, vertexOffset, 0);
    }

    void CommandBufferVk::dispatch(u32 groupCountX, u32 groupCountY, u32 groupCountZ)
    {
        POM_PROFILE_FUNCTION();

        vkCmdDispatch(getCurrentCommandBuffer(), groupCountX, groupCountY, groupCountZ);
    }

    void CommandBufferVk::bindVertexBuffer(Ref<Buffer> vertexBuffer, u32 bindPoint, usize offset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(vertexBuffer->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched vertex buffer api");
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");
        POM_ASSERT(vertexBuffer->getUsage() & BufferUsage::VERTEX,
                   "Attempting to use a buffer created without the vertex BufferUsage.")

        VkBuffer buffer = dynamic_cast<BufferVk*>(vertexBuffer.get())->getBuffer();
        vkCmdBindVertexBuffers(getCurrentCommandBuffer(), bindPoint, 1, &buffer, &offset);
    }

    void CommandBufferVk::bindIndexBuffer(Ref<Buffer> indexBuffer, IndexType type, usize offset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(indexBuffer->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched index buffer api");
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");
        POM_ASSERT(indexBuffer->getUsage() & BufferUsage::INDEX,
                   "Attempting to use a buffer created without the index BufferUsage.")

        vkCmdBindIndexBuffer(getCurrentCommandBuffer(),
                             dynamic_cast<BufferVk*>(indexBuffer.get())->getBuffer(),
                             offset,
                             toVkIndexType(type));
    }

    void CommandBufferVk::bindPipeline(Ref<Pipeline> pipeline)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(pipeline->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched index buffer api");
        POM_ASSERT(specialization == CommandBufferSpecialization::GRAPHICS,
                   "Attempting to use graphics command with a command buffer without that ability.");

        auto pipelineVk = dynamic_cast<PipelineVk*>(pipeline.get());

        vkCmdBindPipeline(getCurrentCommandBuffer(),
                          pipelineVk->getRenderPass() ? VK_PIPELINE_BIND_POINT_GRAPHICS
                                                      : VK_PIPELINE_BIND_POINT_COMPUTE,
                          pipelineVk->getHandle());
    }

    void CommandBufferVk::copyBufferToBuffer(Buffer* src, Buffer* dst, usize size, usize srcOffset, usize dstOffset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(src->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched buffer api");
        POM_ASSERT(dst->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched buffer api");
        POM_ASSERT(src->getSize() - srcOffset >= size, "Attempting to copy from a buffer of insufficient size.");
        POM_ASSERT(dst->getSize() - dstOffset >= size, "Attempting to copy into a buffer of insufficient size.");

        VkBuffer srcBuffer = dynamic_cast<BufferVk*>(src)->getBuffer();
        VkBuffer dstBuffer = dynamic_cast<BufferVk*>(dst)->getBuffer();

        VkBufferCopy region = {
            .srcOffset = srcOffset,
            .dstOffset = dstOffset,
            .size = size,
        };

        vkCmdCopyBuffer(getCurrentCommandBuffer(), srcBuffer, dstBuffer, 1, &region);
    }

    void CommandBufferVk::bindDescriptorSet(PipelineBindPoint bindPoint,
                                            Ref<PipelineLayout> pipelineLayout,
                                            u32 set,
                                            Ref<DescriptorSet> descriptorSet)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(pipelineLayout->getAPI() == GraphicsAPI::VULKAN,
                   "attempting to use mismatched pipeline layout api.");
        POM_ASSERT(descriptorSet->getAPI() == GraphicsAPI::VULKAN, "attempting to use mismatched descriptor set api.");

        auto* layout = dynamic_cast<PipelineLayoutVk*>(pipelineLayout.get());
        auto* descSet = dynamic_cast<DescriptorSetVk*>(descriptorSet.get());

        VkDescriptorSet descSetVk = descSet->getVkDescriptorSet();

        vkCmdBindDescriptorSets(getCurrentCommandBuffer(),
                                toVkPipelineBindPoint(bindPoint),
                                layout->getVkPipelineLayout(),
                                set,
                                1,
                                &descSetVk,
                                0,
                                nullptr);
    }

    void CommandBufferVk::setPushConstants(Ref<PipelineLayout> pipelineLayout,
                                           ShaderStageFlags stages,
                                           usize size,
                                           const void* data,
                                           usize offset)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(pipelineLayout->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched buffer api");
        POM_ASSERT(size % 4 == 0, "size parameter must be a multiple of 4 bytes")
        POM_ASSERT(offset % 4 == 0, "size parameter must be a multiple of 4 bytes")

        vkCmdPushConstants(getCurrentCommandBuffer(),
                           dynamic_cast<PipelineLayoutVk*>(pipelineLayout.get())->getVkPipelineLayout(),
                           toVkShaderStageFlags(stages),
                           offset,
                           size,
                           data);
    }

    void CommandBufferVk::copyBufferToTexture(Buffer* src,
                                              Texture* dst,
                                              usize size,
                                              usize srcOffset,
                                              u32 mipLevel,
                                              const maths::ivec3& dstOffset,
                                              const maths::uvec3& dstExtent)
    {
        POM_PROFILE_FUNCTION();
        POM_ASSERT(src->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched buffer api");
        POM_ASSERT(dst->getAPI() == GraphicsAPI::VULKAN, "Attempting to use mismatched buffer api");
        POM_ASSERT(src->getSize() - srcOffset >= size, "Attempting to copy from a buffer of insufficient size.");
        POM_ASSERT(dst->getUsage() & TextureUsage::TRANSFER_DST,
                   "Attempting to copy into a texture that was created without the usage TextureUsage::TRANSFER_DST.");

        auto* buffer = dynamic_cast<BufferVk*>(src);
        auto* texture = dynamic_cast<TextureVk*>(dst);

        transitionImageLayoutVk(texture, texture->getVkImageLayout(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevel);

        VkBufferImageCopy region = {
            .bufferOffset = srcOffset,
            .bufferRowLength = 0,
            .bufferImageHeight = 0,
            .imageSubresource = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = mipLevel,
                .baseArrayLayer = 0,
                .layerCount = texture->createInfo.arrayLayers,
            },
            .imageOffset = { dstOffset.x, dstOffset.y, dstOffset.z },
            .imageExtent = { dstExtent.x, dstExtent.y, dstExtent.z },
        };

        vkCmdCopyBufferToImage(getCurrentCommandBuffer(),
                               buffer->getBuffer(),
                               texture->getVkImage(),
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                               1,
                               &region);

        transitionImageLayoutVk(texture, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL, mipLevel);
    }

    void CommandBufferVk::transitionImageLayoutVk(TextureVk* texture,
                                                  VkImageLayout oldLayout,
                                                  VkImageLayout newLayout,
                                                  u32 baseMip,
                                                  u32 mips)
    {
        POM_PROFILE_FUNCTION();
        VkImageMemoryBarrier barrier = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            .pNext = nullptr,
            .srcAccessMask = 0,
            .dstAccessMask = 0,
            .oldLayout = oldLayout,
            .newLayout = newLayout,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = texture->getVkImage(),
            .subresourceRange = { //FIXME: whenever this is implemented
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = baseMip,
                .levelCount = mips,
                .baseArrayLayer = 0,
                .layerCount = texture->createInfo.arrayLayers,
            },
        };

        VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_NONE_KHR;
        VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_NONE_KHR;

        // NOTE: there are probably errors in here..
        switch (oldLayout) {
        case VK_IMAGE_LAYOUT_UNDEFINED:
        case VK_IMAGE_LAYOUT_PREINITIALIZED: {
            barrier.srcAccessMask = 0;

            srcStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        } break;
        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL: {
            barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

            srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        } break;
        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: {
            barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

            srcStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT; // last time depth stencil attachments are stored
        } break;
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: {
            barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;

            srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
                           | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT; // NOTE: there may be an better stage for this
        } break;
        default: {
            srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
        }
        }

        switch (newLayout) {
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: {
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: {
            barrier.srcAccessMask |= VK_ACCESS_TRANSFER_READ_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL: {
            barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            dstStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        } break;
        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: {
            barrier.dstAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

            dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT; // before depth stencil load
        } break;
        case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: {
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_GENERAL: {
            // FIXME: pretty sure this isn't right..
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } break;
        case VK_IMAGE_LAYOUT_UNDEFINED:
        case VK_IMAGE_LAYOUT_PREINITIALIZED: {
            POM_FATAL("bad new image layout, cannot transition into undefined or preinitialized.");
        } break;
        default: {
            dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
        }
        }

        vkCmdPipelineBarrier(getCurrentCommandBuffer(),
                             srcStageMask,
                             dstStageMask,
                             0,
                             0,
                             nullptr,
                             0,
                             nullptr,
                             1,
                             &barrier);

        texture->imageLayout = newLayout;
    }

} // namespace pom::gfx
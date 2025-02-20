#include "pch.hpp"

#include "pipelineLayoutVk.hpp"

#include "bufferVk.hpp"
#include "gfxVk.hpp"
#include "instanceVk.hpp"
#include "textureVk.hpp"

namespace pom::gfx {
    PipelineLayoutVk::PipelineLayoutVk(InstanceVk* instance,
                                       u32 numDescSets,
                                       std::initializer_list<Descriptor> descriptors,
                                       std::initializer_list<PushConstant> pushConstants) :
        instance(instance)
    {
        POM_PROFILE_FUNCTION();
        std::unordered_map<DescriptorType, u32> descriptorTypes;

        for (const auto& descriptor : descriptors) {
            descriptorTypes[descriptor.type] += descriptor.count;
            descriptorSetBindings[descriptor.set].push_back({
                .binding = descriptor.binding,
                .descriptorType = toVkDescriptorType(descriptor.type),
                .descriptorCount = descriptor.count,
                .stageFlags = toVkShaderStageFlags(descriptor.stages),
                .pImmutableSamplers = nullptr,
            });
        }

        if (!descriptorTypes.empty()) {
            auto* poolSizes = new VkDescriptorPoolSize[descriptorTypes.size()];
            u32 i = 0;
            for (auto [type, count] : descriptorTypes) {
                poolSizes[i] = {
                    .type = toVkDescriptorType(type),
                    .descriptorCount = count * numDescSets, // FIXME: passable
                };
                i++;
            }

            VkDescriptorPoolCreateInfo poolCreateInfo = {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                .pNext = nullptr,
                // NOTE: idk how to fix it but this is prob dumb to use
                .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
                // FIXME: more than 2 descriptor sets will be bound.
                .maxSets = static_cast<u32>(descriptorSetBindings.size()) * numDescSets, // FIXME: passable
                .poolSizeCount = static_cast<u32>(descriptorTypes.size()),
                .pPoolSizes = poolSizes,
            };

            POM_CHECK_VK(vkCreateDescriptorPool(instance->getVkDevice(), &poolCreateInfo, nullptr, &pool),
                         "could not create descriptor pool.");
        }

        if (descriptorSetBindings.size() > 4) {
            POM_WARN("Creating a pipeline layout with more than 4 descriptor sets, this may cause issues especially on "
                     "integrated CPUs");
        }

        std::vector<VkDescriptorSetLayout> descSetLayouts(descriptorSetBindings.size());
        for (u32 i = 0; i < descriptorSetBindings.size(); i++) {
            VkDescriptorSetLayoutCreateInfo descSetLayoutCreateInfo = {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0,
                .bindingCount = static_cast<u32>(descriptorSetBindings[i].size()),
                .pBindings = descriptorSetBindings[i].data(),
            };

            POM_CHECK_VK(vkCreateDescriptorSetLayout(instance->getVkDevice(),
                                                     &descSetLayoutCreateInfo,
                                                     nullptr,
                                                     &descriptorSetLayouts[i]),
                         "Failed to create descriptor set layout.");

            descSetLayouts[i] = descriptorSetLayouts[i];
        }

        std::vector<VkPushConstantRange> pushConstantRanges;
        pushConstantRanges.reserve(pushConstants.size());
        for (const auto& pc : pushConstants) {
            pushConstantRanges.push_back({
                .stageFlags = toVkShaderStageFlags(pc.stages),
                .offset = pc.offset,
                .size = pc.size,
            });
        }

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .setLayoutCount = static_cast<u32>(descSetLayouts.size()),
            .pSetLayouts = descSetLayouts.data(),
            .pushConstantRangeCount = static_cast<u32>(pushConstantRanges.size()),
            .pPushConstantRanges = pushConstantRanges.data(),
        };

        POM_CHECK_VK(
            vkCreatePipelineLayout(instance->getVkDevice(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout),
            "failed to create pipeline");
    }

    PipelineLayoutVk::~PipelineLayoutVk()
    {
        POM_PROFILE_FUNCTION();
        vkDestroyPipelineLayout(instance->getVkDevice(), pipelineLayout, nullptr);
        if (pool != VK_NULL_HANDLE) {
            vkDestroyDescriptorPool(instance->getVkDevice(), pool, nullptr);
        }
        for (auto& layout : descriptorSetLayouts) {
            vkDestroyDescriptorSetLayout(instance->getVkDevice(), layout.second, nullptr);
        }
    }

} // namespace pom::gfx
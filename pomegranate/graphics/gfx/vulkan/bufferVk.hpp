#pragma once

#include "../buffer.hpp"

#include "instanceVk.hpp"

namespace pom::gfx {

    /// @addtogroup vulkan
    /// @{

    /// Vulkan Buffer, should be created implicitly through `Buffer::create`. Contains the buffer and corresponding
    /// memory.
    class POM_API BufferVk final : public Buffer {
    public:
        BufferVk(InstanceVk* instance, BufferUsage usage, size_t size);
        ~BufferVk() final;

        [[nodiscard]] constexpr GraphicsAPI getAPI() const final
        {
            return GraphicsAPI::VULKAN;
        }

        [[nodiscard]] VkBuffer getBuffer()
        {
            return buffer;
        }

        [[nodiscard]] void* map(size_t offset, size_t size) final;
        void unmap() final;

    protected:
        InstanceVk* instance;
        VkBuffer buffer;
        VkDeviceMemory memory;
    };
} // namespace pom::gfx
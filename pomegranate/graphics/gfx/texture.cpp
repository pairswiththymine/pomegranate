#include "pch.hpp"

#include "texture.hpp"

#include "instance.hpp"

#include "vulkan/instanceVk.hpp"
#include "vulkan/textureVk.hpp"

namespace pom::gfx {
    Ref<Texture> Texture::create(TextureCreateInfo createInfo,
                                 u32 width,
                                 u32 height,
                                 u32 depth,
                                 const void* initialData,
                                 usize initialDataOffset,
                                 usize initialDataSize)
    {
        POM_PROFILE_FUNCTION();
        switch (Instance::get()->getAPI()) {
        case GraphicsAPI::VULKAN: {
            return Ref<Texture>(new TextureVk(dynamic_cast<InstanceVk*>(Instance::get()),
                                              createInfo,
                                              width,
                                              height,
                                              depth,
                                              initialData,
                                              initialDataOffset,
                                              initialDataSize));
        }
        }
    }

    Ref<Texture> Texture::createDirect(TextureCreateInfo createInfo,
                                       u32 width,
                                       u32 height,
                                       u32 depth,
                                       usize initialDataSize,
                                       const void* initialData)
    {
        POM_PROFILE_FUNCTION();
        switch (Instance::get()->getAPI()) {
        case GraphicsAPI::VULKAN: {
            return Ref<Texture>(new TextureVk(dynamic_cast<InstanceVk*>(Instance::get()),
                                              createInfo,
                                              width,
                                              height,
                                              depth,
                                              initialDataSize,
                                              initialData));
        }
        }
    }

    [[nodiscard]] Ref<TextureView> TextureView::create(const Ref<Texture>& texture, TextureViewCreateInfo createInfo)
    {
        POM_PROFILE_FUNCTION();
        switch (Instance::get()->getAPI()) {
        case GraphicsAPI::VULKAN: {
            POM_ASSERT(texture->getAPI() == GraphicsAPI::VULKAN, "mismatched graphics apis, expected Vulkan");
            return Ref<TextureView>(new TextureViewVk(texture.dynCast<TextureVk>(), createInfo));
        }
        }
    }

    Texture::Texture(TextureCreateInfo createInfo, u32 width, u32 height, u32 depth) :
        extent(width, height, depth), createInfo(createInfo)
    {
    }
} // namespace pom::gfx
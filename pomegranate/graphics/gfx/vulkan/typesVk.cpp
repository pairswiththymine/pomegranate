#include "pch.hpp"

#include "typesVk.hpp"

namespace pom::gfx {
    constexpr VkFormat toVkFormat(Format f)
    {
        switch (f) {
        case Format::R8_UNORM: {
            return VK_FORMAT_R8_UNORM;
        } break;
        case Format::R8_SNORM: {
            return VK_FORMAT_R8_SNORM;
        } break;
        case Format::R8_USCALED: {
            return VK_FORMAT_R8_USCALED;
        } break;
        case Format::R8_SSCALED: {
            return VK_FORMAT_R8_SSCALED;
        } break;
        case Format::R8_UINT: {
            return VK_FORMAT_R8_UINT;
        } break;
        case Format::R8_SINT: {
            return VK_FORMAT_R8_SINT;
        } break;
        case Format::R8G8_UNORM: {
            return VK_FORMAT_R8G8_UNORM;
        } break;
        case Format::R8G8_SNORM: {
            return VK_FORMAT_R8G8_SNORM;
        } break;
        case Format::R8G8_USCALED: {
            return VK_FORMAT_R8G8_USCALED;
        } break;
        case Format::R8G8_SSCALED: {
            return VK_FORMAT_R8G8_SSCALED;
        } break;
        case Format::R8G8_UINT: {
            return VK_FORMAT_R8G8_UINT;
        } break;
        case Format::R8G8_SINT: {
            return VK_FORMAT_R8G8_SINT;
        } break;
        case Format::R8G8B8_UNORM: {
            return VK_FORMAT_R8G8B8_UNORM;
        } break;
        case Format::R8G8B8_SNORM: {
            return VK_FORMAT_R8G8B8_SNORM;
        } break;
        case Format::R8G8B8_USCALED: {
            return VK_FORMAT_R8G8B8_USCALED;
        } break;
        case Format::R8G8B8_SSCALED: {
            return VK_FORMAT_R8G8B8_SSCALED;
        } break;
        case Format::R8G8B8_UINT: {
            return VK_FORMAT_R8G8B8_UINT;
        } break;
        case Format::R8G8B8_SINT: {
            return VK_FORMAT_R8G8B8_SINT;
        } break;
        case Format::R8G8B8_SRGB: {
            return VK_FORMAT_R8G8B8_SRGB;
        } break;
        case Format::B8G8R8_UNORM: {
            return VK_FORMAT_B8G8R8_UNORM;
        } break;
        case Format::B8G8R8_SNORM: {
            return VK_FORMAT_B8G8R8_SNORM;
        } break;
        case Format::B8G8R8_USCALED: {
            return VK_FORMAT_B8G8R8_USCALED;
        } break;
        case Format::B8G8R8_SSCALED: {
            return VK_FORMAT_B8G8R8_SSCALED;
        } break;
        case Format::B8G8R8_UINT: {
            return VK_FORMAT_B8G8R8_UINT;
        } break;
        case Format::B8G8R8_SINT: {
            return VK_FORMAT_B8G8R8_SINT;
        } break;
        case Format::B8G8R8_SRGB: {
            return VK_FORMAT_B8G8R8_SRGB;
        } break;
        case Format::R8G8B8A8_UNORM: {
            return VK_FORMAT_R8G8B8A8_UNORM;
        } break;
        case Format::R8G8B8A8_SNORM: {
            return VK_FORMAT_R8G8B8A8_SNORM;
        } break;
        case Format::R8G8B8A8_USCALED: {
            return VK_FORMAT_R8G8B8A8_USCALED;
        } break;
        case Format::R8G8B8A8_SSCALED: {
            return VK_FORMAT_R8G8B8A8_SSCALED;
        } break;
        case Format::R8G8B8A8_UINT: {
            return VK_FORMAT_R8G8B8A8_UINT;
        } break;
        case Format::R8G8B8A8_SINT: {
            return VK_FORMAT_R8G8B8A8_SINT;
        } break;
        case Format::R8G8B8A8_SRGB: {
            return VK_FORMAT_R8G8B8A8_SRGB;
        } break;
        case Format::B8G8R8A8_UNORM: {
            return VK_FORMAT_B8G8R8A8_UNORM;
        } break;
        case Format::B8G8R8A8_SNORM: {
            return VK_FORMAT_B8G8R8A8_SNORM;
        } break;
        case Format::B8G8R8A8_USCALED: {
            return VK_FORMAT_B8G8R8A8_USCALED;
        } break;
        case Format::B8G8R8A8_SSCALED: {
            return VK_FORMAT_B8G8R8A8_SSCALED;
        } break;
        case Format::B8G8R8A8_UINT: {
            return VK_FORMAT_B8G8R8A8_UINT;
        } break;
        case Format::B8G8R8A8_SINT: {
            return VK_FORMAT_B8G8R8A8_SINT;
        } break;
        case Format::B8G8R8A8_SRGB: {
            return VK_FORMAT_B8G8R8A8_SRGB;
        } break;
        case Format::R16_UNORM: {
            return VK_FORMAT_R16_UNORM;
        } break;
        case Format::R16_SNORM: {
            return VK_FORMAT_R16_SNORM;
        } break;
        case Format::R16_USCALED: {
            return VK_FORMAT_R16_USCALED;
        } break;
        case Format::R16_SSCALED: {
            return VK_FORMAT_R16_SSCALED;
        } break;
        case Format::R16_UINT: {
            return VK_FORMAT_R16_UINT;
        } break;
        case Format::R16_SINT: {
            return VK_FORMAT_R16_SINT;
        } break;
        case Format::R16_SFLOAT: {
            return VK_FORMAT_R16_SFLOAT;
        } break;
        case Format::R16G16_UNORM: {
            return VK_FORMAT_R16G16_UNORM;
        } break;
        case Format::R16G16_SNORM: {
            return VK_FORMAT_R16G16_SNORM;
        } break;
        case Format::R16G16_USCALED: {
            return VK_FORMAT_R16G16_USCALED;
        } break;
        case Format::R16G16_SSCALED: {
            return VK_FORMAT_R16G16_SSCALED;
        } break;
        case Format::R16G16_UINT: {
            return VK_FORMAT_R16G16_UINT;
        } break;
        case Format::R16G16_SINT: {
            return VK_FORMAT_R16G16_SINT;
        } break;
        case Format::R16G16_SFLOAT: {
            return VK_FORMAT_R16G16_SFLOAT;
        } break;
        case Format::R16G16B16_UNORM: {
            return VK_FORMAT_R16G16B16_UNORM;
        } break;
        case Format::R16G16B16_SNORM: {
            return VK_FORMAT_R16G16B16_SNORM;
        } break;
        case Format::R16G16B16_USCALED: {
            return VK_FORMAT_R16G16B16_USCALED;
        } break;
        case Format::R16G16B16_SSCALED: {
            return VK_FORMAT_R16G16B16_SSCALED;
        } break;
        case Format::R16G16B16_UINT: {
            return VK_FORMAT_R16G16B16_UINT;
        } break;
        case Format::R16G16B16_SINT: {
            return VK_FORMAT_R16G16B16_SINT;
        } break;
        case Format::R16G16B16_SFLOAT: {
            return VK_FORMAT_R16G16B16_SFLOAT;
        } break;
        case Format::R16G16B16A16_UNORM: {
            return VK_FORMAT_R16G16B16A16_UNORM;
        } break;
        case Format::R16G16B16A16_SNORM: {
            return VK_FORMAT_R16G16B16A16_SNORM;
        } break;
        case Format::R16G16B16A16_USCALED: {
            return VK_FORMAT_R16G16B16A16_USCALED;
        } break;
        case Format::R16G16B16A16_SSCALED: {
            return VK_FORMAT_R16G16B16A16_SSCALED;
        } break;
        case Format::R16G16B16A16_UINT: {
            return VK_FORMAT_R16G16B16A16_UINT;
        } break;
        case Format::R16G16B16A16_SINT: {
            return VK_FORMAT_R16G16B16A16_SINT;
        } break;
        case Format::R16G16B16A16_SFLOAT: {
            return VK_FORMAT_R16G16B16A16_SFLOAT;
        } break;
        case Format::R32_UINT: {
            return VK_FORMAT_R32_UINT;
        } break;
        case Format::R32_SINT: {
            return VK_FORMAT_R32_SINT;
        } break;
        case Format::R32_SFLOAT: {
            return VK_FORMAT_R32_SFLOAT;
        } break;
        case Format::R32G32_UINT: {
            return VK_FORMAT_R32G32_UINT;
        } break;
        case Format::R32G32_SINT: {
            return VK_FORMAT_R32G32_SINT;
        } break;
        case Format::R32G32_SFLOAT: {
            return VK_FORMAT_R32G32_SFLOAT;
        } break;
        case Format::R32G32B32_UINT: {
            return VK_FORMAT_R32G32B32_UINT;
        } break;
        case Format::R32G32B32_SINT: {
            return VK_FORMAT_R32G32B32_SINT;
        } break;
        case Format::R32G32B32_SFLOAT: {
            return VK_FORMAT_R32G32B32_SFLOAT;
        } break;
        case Format::R32G32B32A32_UINT: {
            return VK_FORMAT_R32G32B32A32_UINT;
        } break;
        case Format::R32G32B32A32_SINT: {
            return VK_FORMAT_R32G32B32A32_SINT;
        } break;
        case Format::R32G32B32A32_SFLOAT: {
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        } break;
        default: {
            return VK_FORMAT_UNDEFINED;
        }
        };
    }

    constexpr Format fromVkFormat(VkFormat f)
    {
        switch (f) {
        case VK_FORMAT_R8_UNORM: {
            return Format::R8_UNORM;
        } break;
        case VK_FORMAT_R8_SNORM: {
            return Format::R8_SNORM;
        } break;
        case VK_FORMAT_R8_USCALED: {
            return Format::R8_USCALED;
        } break;
        case VK_FORMAT_R8_SSCALED: {
            return Format::R8_SSCALED;
        } break;
        case VK_FORMAT_R8_UINT: {
            return Format::R8_UINT;
        } break;
        case VK_FORMAT_R8_SINT: {
            return Format::R8_SINT;
        } break;
        case VK_FORMAT_R8G8_UNORM: {
            return Format::R8G8_UNORM;
        } break;
        case VK_FORMAT_R8G8_SNORM: {
            return Format::R8G8_SNORM;
        } break;
        case VK_FORMAT_R8G8_USCALED: {
            return Format::R8G8_USCALED;
        } break;
        case VK_FORMAT_R8G8_SSCALED: {
            return Format::R8G8_SSCALED;
        } break;
        case VK_FORMAT_R8G8_UINT: {
            return Format::R8G8_UINT;
        } break;
        case VK_FORMAT_R8G8_SINT: {
            return Format::R8G8_SINT;
        } break;
        case VK_FORMAT_R8G8B8_UNORM: {
            return Format::R8G8B8_UNORM;
        } break;
        case VK_FORMAT_R8G8B8_SNORM: {
            return Format::R8G8B8_SNORM;
        } break;
        case VK_FORMAT_R8G8B8_USCALED: {
            return Format::R8G8B8_USCALED;
        } break;
        case VK_FORMAT_R8G8B8_SSCALED: {
            return Format::R8G8B8_SSCALED;
        } break;
        case VK_FORMAT_R8G8B8_UINT: {
            return Format::R8G8B8_UINT;
        } break;
        case VK_FORMAT_R8G8B8_SINT: {
            return Format::R8G8B8_SINT;
        } break;
        case VK_FORMAT_R8G8B8_SRGB: {
            return Format::R8G8B8_SRGB;
        } break;
        case VK_FORMAT_B8G8R8_UNORM: {
            return Format::B8G8R8_UNORM;
        } break;
        case VK_FORMAT_B8G8R8_SNORM: {
            return Format::B8G8R8_SNORM;
        } break;
        case VK_FORMAT_B8G8R8_USCALED: {
            return Format::B8G8R8_USCALED;
        } break;
        case VK_FORMAT_B8G8R8_SSCALED: {
            return Format::B8G8R8_SSCALED;
        } break;
        case VK_FORMAT_B8G8R8_UINT: {
            return Format::B8G8R8_UINT;
        } break;
        case VK_FORMAT_B8G8R8_SINT: {
            return Format::B8G8R8_SINT;
        } break;
        case VK_FORMAT_B8G8R8_SRGB: {
            return Format::B8G8R8_SRGB;
        } break;
        case VK_FORMAT_R8G8B8A8_UNORM: {
            return Format::R8G8B8A8_UNORM;
        } break;
        case VK_FORMAT_R8G8B8A8_SNORM: {
            return Format::R8G8B8A8_SNORM;
        } break;
        case VK_FORMAT_R8G8B8A8_USCALED: {
            return Format::R8G8B8A8_USCALED;
        } break;
        case VK_FORMAT_R8G8B8A8_SSCALED: {
            return Format::R8G8B8A8_SSCALED;
        } break;
        case VK_FORMAT_R8G8B8A8_UINT: {
            return Format::R8G8B8A8_UINT;
        } break;
        case VK_FORMAT_R8G8B8A8_SINT: {
            return Format::R8G8B8A8_SINT;
        } break;
        case VK_FORMAT_R8G8B8A8_SRGB: {
            return Format::R8G8B8A8_SRGB;
        } break;
        case VK_FORMAT_B8G8R8A8_UNORM: {
            return Format::B8G8R8A8_UNORM;
        } break;
        case VK_FORMAT_B8G8R8A8_SNORM: {
            return Format::B8G8R8A8_SNORM;
        } break;
        case VK_FORMAT_B8G8R8A8_USCALED: {
            return Format::B8G8R8A8_USCALED;
        } break;
        case VK_FORMAT_B8G8R8A8_SSCALED: {
            return Format::B8G8R8A8_SSCALED;
        } break;
        case VK_FORMAT_B8G8R8A8_UINT: {
            return Format::B8G8R8A8_UINT;
        } break;
        case VK_FORMAT_B8G8R8A8_SINT: {
            return Format::B8G8R8A8_SINT;
        } break;
        case VK_FORMAT_B8G8R8A8_SRGB: {
            return Format::B8G8R8A8_SRGB;
        } break;
        case VK_FORMAT_R16_UNORM: {
            return Format::R16_UNORM;
        } break;
        case VK_FORMAT_R16_SNORM: {
            return Format::R16_SNORM;
        } break;
        case VK_FORMAT_R16_USCALED: {
            return Format::R16_USCALED;
        } break;
        case VK_FORMAT_R16_SSCALED: {
            return Format::R16_SSCALED;
        } break;
        case VK_FORMAT_R16_UINT: {
            return Format::R16_UINT;
        } break;
        case VK_FORMAT_R16_SINT: {
            return Format::R16_SINT;
        } break;
        case VK_FORMAT_R16_SFLOAT: {
            return Format::R16_SFLOAT;
        } break;
        case VK_FORMAT_R16G16_UNORM: {
            return Format::R16G16_UNORM;
        } break;
        case VK_FORMAT_R16G16_SNORM: {
            return Format::R16G16_SNORM;
        } break;
        case VK_FORMAT_R16G16_USCALED: {
            return Format::R16G16_USCALED;
        } break;
        case VK_FORMAT_R16G16_SSCALED: {
            return Format::R16G16_SSCALED;
        } break;
        case VK_FORMAT_R16G16_UINT: {
            return Format::R16G16_UINT;
        } break;
        case VK_FORMAT_R16G16_SINT: {
            return Format::R16G16_SINT;
        } break;
        case VK_FORMAT_R16G16_SFLOAT: {
            return Format::R16G16_SFLOAT;
        } break;
        case VK_FORMAT_R16G16B16_UNORM: {
            return Format::R16G16B16_UNORM;
        } break;
        case VK_FORMAT_R16G16B16_SNORM: {
            return Format::R16G16B16_SNORM;
        } break;
        case VK_FORMAT_R16G16B16_USCALED: {
            return Format::R16G16B16_USCALED;
        } break;
        case VK_FORMAT_R16G16B16_SSCALED: {
            return Format::R16G16B16_SSCALED;
        } break;
        case VK_FORMAT_R16G16B16_UINT: {
            return Format::R16G16B16_UINT;
        } break;
        case VK_FORMAT_R16G16B16_SINT: {
            return Format::R16G16B16_SINT;
        } break;
        case VK_FORMAT_R16G16B16_SFLOAT: {
            return Format::R16G16B16_SFLOAT;
        } break;
        case VK_FORMAT_R16G16B16A16_UNORM: {
            return Format::R16G16B16A16_UNORM;
        } break;
        case VK_FORMAT_R16G16B16A16_SNORM: {
            return Format::R16G16B16A16_SNORM;
        } break;
        case VK_FORMAT_R16G16B16A16_USCALED: {
            return Format::R16G16B16A16_USCALED;
        } break;
        case VK_FORMAT_R16G16B16A16_SSCALED: {
            return Format::R16G16B16A16_SSCALED;
        } break;
        case VK_FORMAT_R16G16B16A16_UINT: {
            return Format::R16G16B16A16_UINT;
        } break;
        case VK_FORMAT_R16G16B16A16_SINT: {
            return Format::R16G16B16A16_SINT;
        } break;
        case VK_FORMAT_R16G16B16A16_SFLOAT: {
            return Format::R16G16B16A16_SFLOAT;
        } break;
        case VK_FORMAT_R32_UINT: {
            return Format::R32_UINT;
        } break;
        case VK_FORMAT_R32_SINT: {
            return Format::R32_SINT;
        } break;
        case VK_FORMAT_R32_SFLOAT: {
            return Format::R32_SFLOAT;
        } break;
        case VK_FORMAT_R32G32_UINT: {
            return Format::R32G32_UINT;
        } break;
        case VK_FORMAT_R32G32_SINT: {
            return Format::R32G32_SINT;
        } break;
        case VK_FORMAT_R32G32_SFLOAT: {
            return Format::R32G32_SFLOAT;
        } break;
        case VK_FORMAT_R32G32B32_UINT: {
            return Format::R32G32B32_UINT;
        } break;
        case VK_FORMAT_R32G32B32_SINT: {
            return Format::R32G32B32_SINT;
        } break;
        case VK_FORMAT_R32G32B32_SFLOAT: {
            return Format::R32G32B32_SFLOAT;
        } break;
        case VK_FORMAT_R32G32B32A32_UINT: {
            return Format::R32G32B32A32_UINT;
        } break;
        case VK_FORMAT_R32G32B32A32_SINT: {
            return Format::R32G32B32A32_SINT;
        } break;
        case VK_FORMAT_R32G32B32A32_SFLOAT: {
            return Format::R32G32B32A32_SFLOAT;
        } break;
        default: {
            return Format::UNDEFINED;
        }
        };
    }

    constexpr VkAttachmentLoadOp toVkAttachmentLoadOp(LoadOperation o)
    {
        switch (o) {
        case LoadOperation::LOAD: {
            return VK_ATTACHMENT_LOAD_OP_LOAD;
        } break;
        case LoadOperation::CLEAR: {
            return VK_ATTACHMENT_LOAD_OP_CLEAR;
        } break;
        case LoadOperation::DONTCARE: {
            return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        } break;
        }
    }

    constexpr LoadOperation fromVkAttachmentLoadOp(VkAttachmentLoadOp o)
    {
        switch (o) {
        case VK_ATTACHMENT_LOAD_OP_LOAD: {
            return LoadOperation::LOAD;
        } break;
        case VK_ATTACHMENT_LOAD_OP_CLEAR: {
            return LoadOperation::CLEAR;
        } break;
        case VK_ATTACHMENT_LOAD_OP_DONT_CARE: {
            return LoadOperation::DONTCARE;
        } break;
        default: {
            // FIXME: there has to be a better way to do this.
#ifdef _DEBUG
            POM_ERROR("Bad vk attachment load operation.");
#endif
            return LoadOperation::LOAD;
        }
        }
    }

    constexpr VkAttachmentStoreOp toVkAttachmentStoreOp(StoreOperation o)
    {
        switch (o) {
        case StoreOperation::STORE: {
            return VK_ATTACHMENT_STORE_OP_STORE;
        } break;
        case StoreOperation::DONTCARE: {
            return VK_ATTACHMENT_STORE_OP_DONT_CARE;
        } break;
        }
    }

    constexpr StoreOperation fromVkAttachmentStoreOp(VkAttachmentStoreOp o)
    {
        switch (o) {
        case VK_ATTACHMENT_STORE_OP_STORE: {
            return StoreOperation::STORE;
        } break;
        case VK_ATTACHMENT_STORE_OP_DONT_CARE: {
            return StoreOperation::DONTCARE;
        } break;
        default: {
            // FIXME: there has to be a better way to do this.
#ifdef _DEBUG
            POM_ERROR("Bad vk attachment store operation.");
#endif
            return StoreOperation::STORE;
        }
        }
    }

    constexpr VkBufferUsageFlags toVkBufferUsageFlags(BufferUsage u)
    {
        VkBufferUsageFlags ret = 0;

        if (u & BufferUsage::VERTEX) {
            ret |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        }
        if (u & BufferUsage::INDEX) {
            ret |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        }
        if (u & BufferUsage::UNIFORM) {
            ret |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        }
        if (u & BufferUsage::TRANSFER_SRC) {
            ret |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        }
        if (u & BufferUsage::TRANSFER_DST) {
            ret |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        }

        return ret;
    }

    constexpr BufferUsage fromVkBufferUsageFlags(VkBufferUsageFlags u)
    {
        auto ret = static_cast<BufferUsage>(0);

        if (u & VK_BUFFER_USAGE_VERTEX_BUFFER_BIT) {
            ret |= BufferUsage::VERTEX;
        }
        if (u & VK_BUFFER_USAGE_INDEX_BUFFER_BIT) {
            ret |= BufferUsage::INDEX;
        }
        if (u & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) {
            ret |= BufferUsage::UNIFORM;
        }
        if (u & VK_BUFFER_USAGE_TRANSFER_SRC_BIT) {
            ret |= BufferUsage::TRANSFER_SRC;
        }
        if (u & VK_BUFFER_USAGE_TRANSFER_DST_BIT) {
            ret |= BufferUsage::TRANSFER_DST;
        }

        return ret;
    }

    constexpr VkIndexType toVkIndexType(IndexType t)
    {
        switch (t) {
        case IndexType::U16: {
            return VK_INDEX_TYPE_UINT16;
        } break;
        case IndexType::U32: {
            return VK_INDEX_TYPE_UINT32;
        } break;
        }
    }

    constexpr IndexType fromVkIndexType(VkIndexType t)
    {
        switch (t) {
        case VK_INDEX_TYPE_UINT16: {
            return IndexType::U16;
        } break;
        case VK_INDEX_TYPE_UINT32: {
            return IndexType::U32;
        } break;
        default: {
            // FIXME: there has to be a better way to do this.
#ifdef _DEBUG
            POM_ERROR("Bad vk index type.");
#endif
            return IndexType::U32;
        }
        }
    }

    POM_API constexpr const char* fromVkResultToString(VkResult r)
    {
        switch (r) {
        case VK_SUCCESS: {
            return "VK_SUCCESS";
        } break;
        case VK_NOT_READY: {
            return "VK_NOT_READY";
        } break;
        case VK_TIMEOUT: {
            return "VK_TIMEOUT";
        } break;
        case VK_EVENT_SET: {
            return "VK_EVENT_SET";
        } break;
        case VK_EVENT_RESET: {
            return "VK_EVENT_RESET";
        } break;
        case VK_INCOMPLETE: {
            return "VK_INCOMPLETE";
        } break;
        case VK_ERROR_OUT_OF_HOST_MEMORY: {
            return "VK_ERROR_OUT_OF_HOST_MEMORY";
        } break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: {
            return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        } break;
        case VK_ERROR_INITIALIZATION_FAILED: {
            return "VK_ERROR_INITIALIZATION_FAILED";
        } break;
        case VK_ERROR_DEVICE_LOST: {
            return "VK_ERROR_DEVICE_LOST";
        } break;
        case VK_ERROR_MEMORY_MAP_FAILED: {
            return "VK_ERROR_MEMORY_MAP_FAILED";
        } break;
        case VK_ERROR_LAYER_NOT_PRESENT: {
            return "VK_ERROR_LAYER_NOT_PRESENT";
        } break;
        case VK_ERROR_EXTENSION_NOT_PRESENT: {
            return "VK_ERROR_EXTENSION_NOT_PRESENT";
        } break;
        case VK_ERROR_FEATURE_NOT_PRESENT: {
            return "VK_ERROR_FEATURE_NOT_PRESENT";
        } break;
        case VK_ERROR_INCOMPATIBLE_DRIVER: {
            return "VK_ERROR_INCOMPATIBLE_DRIVER";
        } break;
        case VK_ERROR_TOO_MANY_OBJECTS: {
            return "VK_ERROR_TOO_MANY_OBJECTS";
        } break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED: {
            return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        } break;
        case VK_ERROR_FRAGMENTED_POOL: {
            return "VK_ERROR_FRAGMENTED_POOL";
        } break;
        case VK_ERROR_UNKNOWN: {
            return "VK_ERROR_UNKNOWN";
        } break;
        case VK_ERROR_OUT_OF_POOL_MEMORY: {
            return "VK_ERROR_OUT_OF_POOL_MEMORY";
        } break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: {
            return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
        } break;
        case VK_ERROR_FRAGMENTATION: {
            return "VK_ERROR_FRAGMENTATION";
        } break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: {
            return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
        } break;
        case VK_ERROR_SURFACE_LOST_KHR: {
            return "VK_ERROR_SURFACE_LOST_KHR";
        } break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: {
            return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        } break;
        case VK_SUBOPTIMAL_KHR: {
            return "VK_SUBOPTIMAL_KHR";
        } break;
        case VK_ERROR_OUT_OF_DATE_KHR: {
            return "VK_ERROR_OUT_OF_DATE_KHR";
        } break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: {
            return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        } break;
        case VK_ERROR_VALIDATION_FAILED_EXT: {
            return "VK_ERROR_VALIDATION_FAILED_EXT";
        } break;
        case VK_ERROR_INVALID_SHADER_NV: {
            return "VK_ERROR_INVALID_SHADER_NV";
        } break;
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: {
            return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
        } break;
        case VK_ERROR_NOT_PERMITTED_EXT: {
            return "VK_ERROR_NOT_PERMITTED_EXT";
        } break;
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: {
            return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
        } break;
        case VK_THREAD_IDLE_KHR: {
            return "VK_THREAD_IDLE_KHR";
        } break;
        case VK_THREAD_DONE_KHR: {
            return "VK_THREAD_DONE_KHR";
        } break;
        case VK_OPERATION_DEFERRED_KHR: {
            return "VK_OPERATION_DEFERRED_KHR";
        } break;
        case VK_OPERATION_NOT_DEFERRED_KHR: {
            return "VK_OPERATION_NOT_DEFERRED_KHR";
        } break;
        case VK_PIPELINE_COMPILE_REQUIRED_EXT: {
            return "VK_PIPELINE_COMPILE_REQUIRED_EXT";
        } break;
        default: {
            return "Uknown VkResult";
        }
        }
    }

} // namespace pom::gfx
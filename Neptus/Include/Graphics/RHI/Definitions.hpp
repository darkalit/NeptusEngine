#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

namespace Neptus {
namespace Graphics {
enum class CullMode : u8 {
    BACK,
    FRONT,
    BOTH,
};

enum class BlendType : u8 {
    NONE,

};

enum class BufferUsage : u8 {
    STATIC,
    DYNAMIC,
    STREAM,
};

enum class RHIFormat : u8 {
    NONE,

    R8_U,
    R8_UNORM,
    R8G8_UNORM,
    R8G8B8_UNORM,
    R8G8B8A8_UNORM,

    R11G11B10_F,
    R10G10B10A2_UNORM,

    R32_U,
    R32G32_U,
    R32G32B32_U,
    R32G32B32A32_U,

    R32_I,
    R32G32_I,
    R32G32B32_I,
    R32G32B32A32_I,

    R16_F,
    R16G16_F,
    R16G16B16_F,
    R16G16B16A16_F,

    R32_F,
    R32G32_F,
    R32G32B32_F,
    R32G32B32A32_F,

    D16_UNORM,
    D32_F,
    D16_UNORM_S8_U,
    D24_UNORM_S8_U,
    D32_F_S8_U,

    SCREEN,
};

static bool IsDepthStencilFormat(RHIFormat format) {
    switch (format) {
    case RHIFormat::D32_F_S8_U:
    case RHIFormat::D24_UNORM_S8_U:
    case RHIFormat::D16_UNORM_S8_U:
        return true;
    default:
        return false;
    }
}

static bool IsDepthFormat(RHIFormat format) {
    switch (format) {
    case RHIFormat::D32_F:
    case RHIFormat::D32_F_S8_U:
    case RHIFormat::D24_UNORM_S8_U:
    case RHIFormat::D16_UNORM_S8_U:
    case RHIFormat::D16_UNORM:
        return true;
    default:
        return false;
    }
}

static bool IsStencilFormat(RHIFormat format) {
    switch (format) {
    case RHIFormat::D32_F_S8_U:
    case RHIFormat::D24_UNORM_S8_U:
    case RHIFormat::D16_UNORM_S8_U:
        return true;
    default:
        return false;
    }
}

static u32 GetFormatByteSize(RHIFormat format) {
    switch (format) {
    case RHIFormat::NONE:
        return 0;
    case RHIFormat::R8_U:
    case RHIFormat::R8_UNORM:
        return 1;
    case RHIFormat::R8G8_UNORM:
    case RHIFormat::R16_F:
    case RHIFormat::D16_UNORM:
        return 2;
    case RHIFormat::R8G8B8_UNORM:
    case RHIFormat::D16_UNORM_S8_U:
        return 3;
    case RHIFormat::R32_U:
    case RHIFormat::R32_I:
    case RHIFormat::R32_F:
    case RHIFormat::R8G8B8A8_UNORM:
    case RHIFormat::R10G10B10A2_UNORM:
    case RHIFormat::R11G11B10_F:
    case RHIFormat::R16G16_F:
    case RHIFormat::D32_F:
    case RHIFormat::D24_UNORM_S8_U:
        return 4;
    case RHIFormat::R16G16B16_F:
        return 6;
    case RHIFormat::R32G32_U:
    case RHIFormat::R32G32_I:
    case RHIFormat::R32G32_F:
    case RHIFormat::R16G16B16A16_F:
        return 8;
    case RHIFormat::R32G32B32_U:
    case RHIFormat::R32G32B32_I:
    case RHIFormat::R32G32B32_F:
        return 12;
    case RHIFormat::R32G32B32A32_U:
    case RHIFormat::R32G32B32A32_I:
    case RHIFormat::R32G32B32A32_F:
        return 16;
    default:
        return 0;
    }
}

enum class DrawType : u8 {
    POINT,
    TRIANGLE,
    LINES,
};

enum class DataType : u8 {
    FLOAT,
    UNSIGNED_INT,
    UNSIGNED_BYTE,
};

enum class TextureWrap : u8 {
    NONE,
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
};

} // namespace Graphics
} // namespace Neptus

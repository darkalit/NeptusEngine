#pragma once

#include "Graphics/RHI/Definitions.hpp"

#include <glad/gl.h>

namespace Neptus {
namespace Graphics {
static i32 DataTypeToGL(const DataType type) {
    switch (type) {
    case DataType::FLOAT:
        return GL_FLOAT;
    case DataType::UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    case DataType::UNSIGNED_BYTE:
        return GL_UNSIGNED_BYTE;
    }
    return 0;
}

static i32 DrawTypeToGL(const DrawType type) {
    switch (type) {
    case DrawType::POINT:
        return GL_POINTS;
    case DrawType::TRIANGLE:
        return GL_TRIANGLES;
    case DrawType::LINES:
        return GL_LINES;
    }
    return 0;
}

static i32 BufferUsageToGL(const BufferUsage usage) {
    switch (usage) {
    case BufferUsage::STATIC:
        return GL_STATIC_DRAW;
    case BufferUsage::DYNAMIC:
        return GL_DYNAMIC_DRAW;
    case BufferUsage::STREAM:
        return GL_STREAM_DRAW;
    }
    return 0;
}

static i32 RHIFormatToGL(RHIFormat format, bool srgb = true) {
    switch (format) {
    case RHIFormat::NONE:
        return 0;
    case RHIFormat::R8_UNORM:
        return GL_R8;
    case RHIFormat::R8G8_UNORM:
        return GL_RG8;
    case RHIFormat::R8G8B8_UNORM:
        return srgb ? GL_SRGB8 : GL_RGB8;
    case RHIFormat::R8G8B8A8_UNORM:
        return srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8;
    case RHIFormat::R11G11B10_F:
        return GL_R11F_G11F_B10F;
    case RHIFormat::R10G10B10A2_UNORM:
        return GL_RGB10_A2;
    case RHIFormat::R16_F:
        return GL_R16F;
    case RHIFormat::R16G16_F:
        return GL_RG16F;
    case RHIFormat::R16G16B16_F:
        return GL_RGB16F;
    case RHIFormat::R16G16B16A16_F:
        return GL_RGBA16F;
    case RHIFormat::R32G32_F:
        return GL_RG32F;
    case RHIFormat::R32G32B32_F:
        return GL_RGB32F;
    case RHIFormat::R32G32B32A32_F:
        return GL_RGBA32F;
    case RHIFormat::D16_UNORM:
        return GL_DEPTH_COMPONENT16;
    case RHIFormat::D24_UNORM_S8_U:
        return GL_DEPTH24_STENCIL8;
    case RHIFormat::D32_F:
        return GL_DEPTH_COMPONENT32F;
    case RHIFormat::D32_F_S8_U:
        return GL_DEPTH32F_STENCIL8;
    default:
        return 0;
    }
}

static i32 RHIFormatToBaseGL(RHIFormat format, bool srgb = true) {
    switch (format) {
    case RHIFormat::NONE:
        return 0;
    case RHIFormat::R8G8B8_UNORM:
        return srgb ? GL_SRGB : GL_RGB;
    case RHIFormat::R8G8B8A8_UNORM:
        return srgb ? GL_SRGB_ALPHA : GL_RGBA;
    case RHIFormat::R8_UNORM:
    case RHIFormat::R16_F:
        return GL_RED;
    case RHIFormat::R8G8_UNORM:
    case RHIFormat::R16G16_F:
    case RHIFormat::R32G32_F:
        return GL_RG;
    case RHIFormat::R11G11B10_F:
    case RHIFormat::R16G16B16_F:
    case RHIFormat::R32G32B32_F:
        return GL_RGB;
    case RHIFormat::R10G10B10A2_UNORM:
    case RHIFormat::R16G16B16A16_F:
    case RHIFormat::R32G32B32A32_F:
        return GL_RGBA;
    case RHIFormat::D16_UNORM:
    case RHIFormat::D32_F:
        return GL_DEPTH_COMPONENT;
    case RHIFormat::D24_UNORM_S8_U:
    case RHIFormat::D32_F_S8_U:
        return GL_DEPTH_STENCIL;
    default:
        return 0;
    }
}

static i32 GLFormatToBase(i32 format) {
    switch (format) {
    case GL_R8:
        return GL_RED;
    case GL_RG8:
    case GL_RG16F:
        return GL_RG;
    case GL_RGB:
    case GL_SRGB8:
    case GL_RGB8:
    case GL_RGB16:
    case GL_RGB32F:
    case GL_SRGB:
    case GL_R11F_G11F_B10F:
        return GL_RGB;
    case GL_RGBA:
    case GL_RGB10_A2:
    case GL_SRGB_ALPHA:
    case GL_RGBA32F:
    case GL_RGBA16F:
    case GL_RGBA16:
    case GL_RGBA8:
        return GL_RGBA;
    case GL_DEPTH24_STENCIL8:
    case GL_DEPTH32F_STENCIL8:
    case GL_DEPTH_STENCIL:
        return GL_DEPTH_STENCIL;
    case GL_DEPTH_COMPONENT:
    case GL_DEPTH_COMPONENT16:
    case GL_DEPTH_COMPONENT24:
    case GL_DEPTH_COMPONENT32:
    case GL_DEPTH_COMPONENT32F:
        return GL_DEPTH_COMPONENT;

    default:
        return 0;
    }
}

static i32 GLTypeFromFormat(RHIFormat format) {
    switch (format) {
    case RHIFormat::R8_U:
    case RHIFormat::R8_UNORM:
    case RHIFormat::R8G8_UNORM:
    case RHIFormat::R8G8B8_UNORM:
    case RHIFormat::R8G8B8A8_UNORM:
    case RHIFormat::R10G10B10A2_UNORM:
        return GL_UNSIGNED_BYTE;
    case RHIFormat::R32_U:
    case RHIFormat::R32G32_U:
    case RHIFormat::R32G32B32_U:
    case RHIFormat::R32G32B32A32_U:
        return GL_UNSIGNED_INT;
    case RHIFormat::R32_I:
    case RHIFormat::R32G32_I:
    case RHIFormat::R32G32B32_I:
    case RHIFormat::R32G32B32A32_I:
        return GL_INT;
    case RHIFormat::R16_F:
    case RHIFormat::R16G16_F:
    case RHIFormat::R11G11B10_F:
    case RHIFormat::R16G16B16_F:
    case RHIFormat::R16G16B16A16_F:
    case RHIFormat::R32_F:
    case RHIFormat::R32G32_F:
    case RHIFormat::R32G32B32_F:
    case RHIFormat::R32G32B32A32_F:
    case RHIFormat::D16_UNORM:
    case RHIFormat::D32_F:
    case RHIFormat::D32_F_S8_U:
    case RHIFormat::D16_UNORM_S8_U:
    case RHIFormat::D24_UNORM_S8_U:
        return GL_FLOAT;
    default:
        return GL_UNSIGNED_BYTE;
    }
}

static i32 TextureWrapToGL(const TextureWrap wrap) {
    switch (wrap) {
    case TextureWrap::NONE:
        return 0;
    case TextureWrap::REPEAT:
        return GL_REPEAT;
    case TextureWrap::MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
    case TextureWrap::CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    case TextureWrap::CLAMP_TO_BORDER:
        return GL_CLAMP_TO_BORDER;
    }

    return 0;
}
} // namespace Graphics
} // namespace Neptus

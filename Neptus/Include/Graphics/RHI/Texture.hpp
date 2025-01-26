#pragma once

#include "Core/API.hpp"
#include "Core/Asset.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Definitions.hpp"

#include <string>

namespace Neptus {
namespace Graphics {
using TextureHandle = void*;

enum class TextureFilter : u8 {
    NONE,
    LINEAR,
    NEAREST,
};

enum TextureFlags : u8 {
    TEXTURE_SAMPLED = BIT(0),
    TEXTURE_STORAGE = BIT(1),
    TEXTURE_RENDER_TARGET = BIT(2),
    TEXTURE_DEPTH_STENCIL = BIT(3),
    TEXTURE_DEPTH_STENCIL_READONLY = BIT(4),
    TEXTURE_CREATE_MIPS = BIT(5),
    TEXTURE_MIP_VIEWS = BIT(6),
};

struct NP_API TextureProps {
    RHIFormat Format = RHIFormat::R8G8B8_UNORM;
    TextureFilter MinFilter = TextureFilter::NEAREST;
    TextureFilter MagFilter = TextureFilter::NEAREST;
    TextureWrap Wrap = TextureWrap::REPEAT;
    TextureFlags Flags = TEXTURE_CREATE_MIPS;
    bool Srgb = false;
};

struct NP_API TextureLoadOptions {
    bool FlipX = false;
    bool FlipY = false;
};

enum class TextureType : u8 {
    COLOR,
    DEPTH,
    DEPTH_STENCIL,
};

class NP_API Texture : public Asset {
    ASSET(Texture)
public:
    virtual void Bind(u32 slot = 0) const = 0;
    virtual void Unbind(u32 slot = 0) const = 0;
    virtual std::string GetFilepath() const = 0;
    virtual TextureType GetTextureType() const = 0;
    RHIFormat GetFormat() const;
    TextureHandle GetHandle() const;

    static u32 BitsToChannelCount(u32 bits);
    static u32 BitsFromFormat(RHIFormat format);
    static RHIFormat BitsToFormat(u32 bits);

    friend class Framebuffer;

protected:
    virtual void Release() = 0;

    union {
        u32 m_Handle;
    };

    TextureProps m_Properties = {};
    u32 m_Width = 0;
    u32 m_Height = 0;
    u32 m_Bits = 0;
    u32 m_ChannelCount = 0;
};

class NP_API Texture2D final : public Texture {
public:
    Texture2D() = default;
    Texture2D(u32 width, u32 height, TextureProps = {});
    Texture2D(void* data, u32 width, u32 height, TextureProps props = {},
              TextureLoadOptions loadOptions = {});
    Texture2D(const std::string& filepath, TextureProps props = {},
              TextureLoadOptions loadOptions = {});
    Texture2D(Texture2D&& other) noexcept;
    ~Texture2D();

    Texture2D& operator=(Texture2D&& other) noexcept;

    void Bind(u32 slot) const override;
    void Unbind(u32 slot) const override;
    std::string GetFilepath() const override;
    TextureType GetTextureType() const override { return TextureType::COLOR; }

    static void ImGuiImage(const Texture2D& texture);

protected:
    void Release() override;

    u32 m_MipLevels = 1;
};

inline u32 Texture::BitsToChannelCount(u32 bits) {
    switch (bits) {
    case 8:
        return 1;
    case 16:
        return 2;
    case 24:
    case 48:
    case 96:
        return 3;
    case 32:
    case 64:
    case 128:
        return 4;
    default:
        return 4;
    }
}

inline u32 Texture::BitsFromFormat(RHIFormat format) {
    switch (format) {
    case RHIFormat::NONE:
        break;
    case RHIFormat::R8_U:
    case RHIFormat::R8_UNORM:
        return 8;
    case RHIFormat::R8G8_UNORM:
    case RHIFormat::R16_F:
    case RHIFormat::D16_UNORM:
        return 16;
    case RHIFormat::R8G8B8_UNORM:
    case RHIFormat::D16_UNORM_S8_U:
        return 24;
    case RHIFormat::R8G8B8A8_UNORM:
    case RHIFormat::R11G11B10_F:
    case RHIFormat::R10G10B10A2_UNORM:
    case RHIFormat::R32_U:
    case RHIFormat::R32_I:
    case RHIFormat::R16G16_F:
    case RHIFormat::R32_F:
    case RHIFormat::D32_F:
    case RHIFormat::D24_UNORM_S8_U:
        return 32;
    case RHIFormat::D32_F_S8_U:
        return 40;
    case RHIFormat::R16G16B16_F:
        return 48;
    case RHIFormat::R32G32_U:
    case RHIFormat::R32G32_I:
    case RHIFormat::R32G32_F:
    case RHIFormat::R16G16B16A16_F:
        return 64;
    case RHIFormat::R32G32B32_U:
    case RHIFormat::R32G32B32_I:
    case RHIFormat::R32G32B32_F:
        return 96;
    case RHIFormat::R32G32B32A32_U:
    case RHIFormat::R32G32B32A32_I:
    case RHIFormat::R32G32B32A32_F:
        return 128;
    default:
        return 32;
    }

    return 32;
}


inline RHIFormat Texture::BitsToFormat(u32 bits) {
    switch (bits) {
    case 8:
        return RHIFormat::R8_UNORM;
    case 16:
        return RHIFormat::R8G8_UNORM;
    case 24:
        return RHIFormat::R8G8B8_UNORM;
    case 32:
        return RHIFormat::R8G8B8A8_UNORM;
    default:
        return RHIFormat::NONE;
    }
}
} // namespace Graphics
} // namespace Neptus

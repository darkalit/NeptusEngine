#include "Graphics/RHI/Texture.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"
#include "Utils/LoadImage.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <imgui.h>

namespace Neptus {
namespace Graphics {
u32 LoadTexture(const void* data, u32 width, u32 height, u32 channelCount,
                const TextureProps& textureProps, u32 mipLevels = 1) {
    u32 handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    const i32 minFilter =
        textureProps.MinFilter == TextureFilter::LINEAR &&
                textureProps.Flags & TextureFlags::TEXTURE_CREATE_MIPS
            ? GL_LINEAR_MIPMAP_LINEAR
            : GL_NEAREST;
    const i32 magFilter = textureProps.MagFilter == TextureFilter::LINEAR
                              ? GL_LINEAR
                              : GL_NEAREST;
    const i32 wrapST = TextureWrapToGL(textureProps.Wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapST);

    i32 internalFormat =
        RHIFormatToBaseGL(textureProps.Format, textureProps.Srgb);
    i32 dataFormat = GLFormatToBase(internalFormat);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat,
                 GLTypeFromFormat(textureProps.Format), data);

    if (textureProps.Flags & TextureFlags::TEXTURE_CREATE_MIPS) {
        glGenerateMipmap(GL_TEXTURE_2D);
        mipLevels = static_cast<u32>(
            glm::floor(glm::log2(static_cast<f32>(glm::max(width, height)))));
        mipLevels++;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return handle;
}

Texture2D::Texture2D(u32 width, u32 height, TextureProps props) {
    m_Width = width;
    m_Height = height;
    m_Properties = props;
    m_Bits = BitsFromFormat(props.Format);
    m_ChannelCount = BitsToChannelCount(m_Bits);

    m_Handle = LoadTexture(nullptr, m_Width, m_Height, m_ChannelCount, m_Properties);
}

Texture2D::Texture2D(void* data, u32 width, u32 height, TextureProps props,
                         TextureLoadOptions loadOptions) {}

Texture2D::Texture2D(const std::string& filepath, TextureProps props,
                         TextureLoadOptions loadOptions) {
    m_Properties = props;
    auto [Data, Width, Height, Bits, IsHDR] =
        LoadImageFromFile(filepath, loadOptions.FlipY);

    m_Width = Width;
    m_Height = Height;
    m_Bits = Bits;
    m_ChannelCount = BitsToChannelCount(Bits);
    m_Properties.Format = BitsToFormat(Bits);

    m_Handle = LoadTexture(Data, m_Width, m_Height, m_ChannelCount, m_Properties);
    delete[] Data;
}

Texture2D::Texture2D(Texture2D&& other) noexcept {
    m_Handle = other.m_Handle;
    other.m_Handle = 0;
    m_Id = std::move(other.m_Id);
    m_Bits = other.m_Bits;
    m_Width = other.m_Width;
    m_Height = other.m_Height;
    m_ChannelCount = other.m_ChannelCount;
    m_MipLevels = other.m_ChannelCount;
    m_Properties = other.m_Properties;
    m_Status = other.m_Status;
    other.m_Status = AssetFlag::INVALID;
}

Texture2D::~Texture2D() {
    Release();
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
        m_Id = std::move(other.m_Id);
        m_Bits = other.m_Bits;
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        m_ChannelCount = other.m_ChannelCount;
        m_MipLevels = other.m_ChannelCount;
        m_Properties = other.m_Properties;
        m_Status = other.m_Status;
        other.m_Status = AssetFlag::INVALID;
    }

    return *this;
}

void Texture2D::Bind(u32 slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Handle);
}

void Texture2D::Unbind(u32 slot) const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Texture2D::GetFilepath() const {
    return "";
}

void Texture2D::ImGuiImage(const Texture2D& texture) {
    ImGui::Image(reinterpret_cast<void*>(texture.m_Handle), ImGui::GetContentRegionAvail(), {0.0f, 1.0f}, {1.0f, 0.0f});
}

void Texture2D::Release() {
    glDeleteTextures(1, &m_Handle);
    m_Handle = 0;
}
} // namespace Graphics
} // namespace Neptus

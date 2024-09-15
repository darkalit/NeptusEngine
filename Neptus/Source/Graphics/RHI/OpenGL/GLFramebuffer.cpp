#include "Graphics/RHI/Framebuffer.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"
#include "Graphics/RHI/Texture.hpp"

#include <glad/gl.h>
#include <imgui.h>

#include <iostream>

namespace Neptus {
namespace Graphics {
GLenum GetAttachmentPoint(RHIFormat format, u32 colorCount) {
    if (IsDepthStencilFormat(format)) {
        return GL_DEPTH_STENCIL_ATTACHMENT;
    }
    if (IsStencilFormat(format)) {
        return GL_STENCIL_ATTACHMENT;
    }
    if (IsDepthFormat(format)) {
        return GL_DEPTH_ATTACHMENT;
    }

    GLenum value = GL_COLOR_ATTACHMENT0 + colorCount;
    return value;
}

std::vector<GLenum> GetGLColorAttachments(const std::vector<Texture2D>& attachments) {
    std::vector<GLenum> glAttachments;
    glAttachments.reserve(attachments.size());

    for (size_t i = 0; i < attachments.size(); ++i) {
        glAttachments.push_back(GetAttachmentPoint(attachments[i].GetFormat(), i));
    }

    return glAttachments;
}

Framebuffer::Framebuffer() {}

Framebuffer::Framebuffer(const FramebufferProps& props)
    : m_Handle(0)
    , m_Width(props.Width)
    , m_Height(props.Height)
    , m_mipLevel(props.mipLevel) {
    glGenFramebuffers(1, &m_Handle);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

    for (auto [type, format] : props.Attachments) {
        switch (type) {
        case TextureType::COLOR:
            AddTextureAttachment(format, props.mipLevel);
            break;
        case TextureType::DEPTH:
            AddTextureAttachment(RHIFormat::D16_UNORM, props.mipLevel);
            break;
        case TextureType::DEPTH_STENCIL:
            AddTextureAttachment(RHIFormat::D24_UNORM_S8_U, props.mipLevel);
            break;
        }
    }

    auto glAttachments = GetGLColorAttachments(m_ColorAttachments);
    // glDrawBuffers(glAttachments.size(), glAttachments.data());

    if (auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::GRAPHICS::RHI::FRAMEBUFFER:" << status << '\n';
    }

    Unbind();
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_Width(other.m_Width)
    , m_Height(other.m_Height)
    , m_mipLevel(other.m_mipLevel)
    , m_ColorAttachments(std::move(other.m_ColorAttachments))
    , m_DepthAttachments(std::move(other.m_DepthAttachments))
    , m_DepthStencilAttachments(std::move(other.m_DepthStencilAttachments))
{
    other.m_Handle = 0;
}

Framebuffer::~Framebuffer() {
    Release();
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        m_mipLevel = other.m_mipLevel;
        m_ColorAttachments = std::move(other.m_ColorAttachments);
        m_DepthAttachments = std::move(other.m_DepthAttachments);
        m_DepthStencilAttachments = std::move(other.m_DepthStencilAttachments);
    }

    return *this;
}

// void Framebuffer::Bind() const {
//     glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
//     glViewport(0, 0, m_Width, m_Height);
//
//     auto glAttachments = GetGLColorAttachments(m_ColorAttachments);
//     // glDrawBuffers(glAttachments.size(), glAttachments.data());
// }

void Framebuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
}

void Framebuffer::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindColorAttachment(u32 index, u32 slot) {
    m_ColorAttachments[index].Bind(slot);
}

void Framebuffer::AddTextureAttachment(RHIFormat format, u32 mipLevel) {
    GLenum attachment = GetAttachmentPoint(format, m_ColorAttachments.size());

    TextureProps textureProps = {};
    textureProps.Format = format;
    Texture2D texture2D(m_Width, m_Height, textureProps);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D,
                           texture2D.m_Handle, mipLevel);

    switch (attachment) {
    case GL_DEPTH_ATTACHMENT:
        m_DepthAttachments.emplace_back(std::move(texture2D));
        break;
    case GL_STENCIL_ATTACHMENT:
        break;
    case GL_DEPTH_STENCIL_ATTACHMENT:
        m_DepthStencilAttachments.emplace_back(std::move(texture2D));
        break;
    default:
        m_ColorAttachments.emplace_back(std::move(texture2D));
        break;
    }
}

void Framebuffer::Resize(u32 width, u32 height) {
    m_Width = width;
    m_Height = height;

    Bind();
    for (size_t i = 0; i < m_ColorAttachments.size(); ++i) {
        Resize(width, height, m_ColorAttachments[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, m_ColorAttachments[i].m_Handle,
                               m_mipLevel);
    }

    for (auto& attachment : m_DepthAttachments) {
        Resize(width, height, attachment);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_2D, attachment.m_Handle, m_mipLevel);
    }

    for (auto& attachment : m_DepthStencilAttachments) {
        Resize(width, height, attachment);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D, attachment.m_Handle, m_mipLevel);
    }
    Unbind();
}

void Framebuffer::ImGuiImage(Framebuffer& framebuffer) {
    Texture2D::ImGuiImage(framebuffer.m_ColorAttachments[0]);
}

void Framebuffer::Resize(u32 width, u32 height, Texture2D& attachment) {
    glBindTexture(GL_TEXTURE_2D, attachment.m_Handle);
    const i32 minFilter =
        attachment.m_Properties.MinFilter == TextureFilter::LINEAR &&
                attachment.m_Properties.Flags &
                    TextureFlags::TEXTURE_CREATE_MIPS
            ? GL_LINEAR_MIPMAP_LINEAR
            : GL_NEAREST;
    const i32 magFilter =
        attachment.m_Properties.MagFilter == TextureFilter::LINEAR ? GL_LINEAR
                                                                   : GL_NEAREST;
    const i32 wrapST = TextureWrapToGL(attachment.m_Properties.Wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapST);

    i32 internalFormat = RHIFormatToBaseGL(attachment.m_Properties.Format,
                                           attachment.m_Properties.Srgb);
    i32 dataFormat = GLFormatToBase(internalFormat);

    attachment.m_Width = width;
    attachment.m_Height = height;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat,
                 GLTypeFromFormat(attachment.m_Properties.Format), nullptr);
}

void Framebuffer::Release() {
    glDeleteFramebuffers(1, &m_Handle);
    m_Handle = 0;
}
} // namespace Graphics
} // namespace Neptus

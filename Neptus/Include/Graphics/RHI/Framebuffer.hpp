#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Texture.hpp"

#include <map>
#include <vector>

namespace Neptus {
namespace Graphics {
struct FramebufferProps {
    std::vector<std::pair<TextureType, RHIFormat>> Attachments;
    u32 Width = 0;
    u32 Height = 0;
    u32 mipLevel = 0;
};

class NP_API Framebuffer {
public:
    Framebuffer();
    Framebuffer(const FramebufferProps& props);
    Framebuffer(const Framebuffer&) = delete;
    Framebuffer(Framebuffer&& other) noexcept;
    ~Framebuffer();

    Framebuffer& operator=(const Framebuffer&) = delete;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void BindColorAttachment(u32 index, u32 slot);

    void AddTextureAttachment(RHIFormat format, u32 mipLevel = 0);
    void AddShadowAttachment();

    void Resize(u32 width, u32 height);

    std::vector<Texture2D>& GetColorAttachments();
    std::vector<Texture2D>& GetDepthAttachments();
    std::vector<Texture2D>& GetDepthStencilAttachments();

    u32 GetWidth() const {
        return m_Width;
    }

    u32 GetHeight() const {
        return m_Height;
    }

    static void ImGuiImage(Framebuffer& framebuffer);

private:
    void Resize(u32 width, u32 height, Texture2D& attachment);
    void Release();

    union {
        u32 m_Handle;
    };

    u32 m_Width = 0;
    u32 m_Height = 0;
    u32 m_mipLevel = 0;
    std::vector<Texture2D> m_ColorAttachments = {};
    std::vector<Texture2D> m_DepthAttachments = {};
    std::vector<Texture2D> m_DepthStencilAttachments = {};

};
} // namespace Graphics
} // namespace Neptus

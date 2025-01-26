#pragma once

#include "Core/API.hpp"
#include "Graphics/RHI/Renderer.hpp"
#include "Graphics/RHI/Shader.hpp"
#include "Graphics/RHI/Framebuffer.hpp"
#include "Graphics/ScreenSurface.hpp"

#include "Scene/Scene.hpp"

#include "glm/glm.hpp"

namespace Neptus {
namespace Graphics {
class NP_API RenderPasses {
public:
    RenderPasses(u32 width, u32 height);

    void InitResources();
    void Resize(u32 width, u32 height);

    void BeginScene(Scene& scene);
    void OnRender(const glm::mat4& proj, const glm::mat4& view);

    std::map<std::string, Framebuffer>& GetFramebuffers();

    void ImGuiFrameImage();
    void ImGuiBegin() const;
    void ImGuiEnd() const;

    void ColorPass(const glm::mat4& proj, const glm::mat4& view);
    void ShadowPass();
    void SkyboxPass();
    void FinalPass();

protected:
    u32 m_Width, m_Height;

    Renderer m_Renderer;
    Scene* m_CurrentScene = nullptr;

    ScreenSurface m_ScreenSurface;

    std::map<std::string, Framebuffer> m_Framebuffers;
    Shader m_ScreenShader;
    Shader m_ModelColorShader;
};
} // namespace Graphics
} // namespace Neptus

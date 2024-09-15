#include "Graphics/RenderPasses.hpp"

#include "Scene/Components/ModelComponent.hpp"
#include "Scene/Components/TransformComponent.hpp"
#include "Scene/Scene.hpp"

#include <imgui.h>
#include <iostream>

namespace Neptus {
namespace Graphics {
RenderPasses::RenderPasses(u32 width, u32 height)
    : m_Width(width)
    , m_Height(height)
    , m_Framebuffer({{{TextureType::COLOR, RHIFormat::R8G8B8_UNORM},
                      {TextureType::DEPTH, RHIFormat::D16_UNORM}},
                     width,
                     height})
    , m_PostEffectsFramebuffer({{{TextureType::COLOR, RHIFormat::R8G8B8_UNORM},
                                 {TextureType::DEPTH, RHIFormat::D16_UNORM}},
                                width,
                                height}) {
    InitResources();
}

void RenderPasses::InitResources() {
    m_ScreenShader = Shader("Neptus/Assets/Shaders/screen.glsl");
    m_ModelColorShader = Shader("Neptus/Assets/Shaders/model.glsl");
}

void RenderPasses::Resize(u32 width, u32 height) {
    m_Framebuffer.Resize(width, height);
    m_PostEffectsFramebuffer.Resize(width, height);
    m_Renderer.Resize(width, height);
}

void RenderPasses::BeginScene(Scene& scene) {
    if (m_CurrentScene == &scene) {
        return;
    }

    m_CurrentScene = &scene;
}

void RenderPasses::OnRender(const glm::mat4& proj, const glm::mat4& view) {
    m_Framebuffer.Bind();
    ColorPass(proj, view);
    m_Framebuffer.Unbind();
    m_PostEffectsFramebuffer.Bind();
    Renderer::Clear({1.0f, 1.0f, 1.0f, 1.0f}, ClearFlags::COLOR);
    Renderer::Cull(CullMode::BOTH);
    Renderer::DepthTest(false);

    m_ScreenShader.Bind();
    m_ScreenShader.SetUniform1i("screenTexture", 0);
    m_Framebuffer.BindColorAttachment(0, 0);
    m_Renderer.DrawIndexed(m_ScreenSurface.VAO, m_ScreenSurface.EBO, DrawType::TRIANGLE);
    m_ScreenShader.Unbind();
    m_PostEffectsFramebuffer.Unbind();
    Renderer::Clear({1.0f, 1.0f, 1.0f, 1.0f}, ClearFlags::COLOR);
}

void RenderPasses::ImGuiFrameImage() {
    Framebuffer::ImGuiImage(m_PostEffectsFramebuffer);
}

void RenderPasses::ImGuiBegin() const {
    m_Renderer.ImGuiBegin();
    ImGui::NewFrame();
}

void RenderPasses::ImGuiEnd() const {
    ImGui::Render();
    m_Renderer.ImGuiEnd();
}

void RenderPasses::ColorPass(const glm::mat4& proj, const glm::mat4& view) {
    Renderer::Clear();
    Renderer::Cull(CullMode::FRONT);
    Renderer::DepthTest(true);

    m_Renderer.Begin();

    m_CurrentScene
        ->GetAllEntitiesWith<Components::TransformComponent,
                             Components::ModelComponent>()
        .each([this, proj, view](Components::TransformComponent& transformComp,
                        Components::ModelComponent& modelComp) {
            m_ModelColorShader.Bind();
            m_ModelColorShader.SetUniformMat4("model",
                                              transformComp.GetTransform());
            m_ModelColorShader.SetUniformMat4("view", view);
            m_ModelColorShader.SetUniformMat4("proj", proj);

            for (auto& mesh : modelComp.Model->GetMeshes()) {
                m_ModelColorShader.SetUniform1i("textureDiffuse", 0);
                if (mesh.Texture.second) {
                    mesh.Texture.second->Bind(0);
                }
                m_Renderer.DrawIndexed(mesh.VAO, mesh.EBO, DrawType::TRIANGLE);
            }

            m_ModelColorShader.Unbind();
        });

    m_Renderer.End();
}
} // namespace Graphics
} // namespace Neptus

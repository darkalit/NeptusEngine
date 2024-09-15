#include "Graphics/RHI/Renderer.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"

#include <SDL.h>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <iostream>

namespace Neptus {
namespace Graphics {
void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, u32 id,
                              GLenum severity, GLsizei length,
                              const char* message, const void* userParam) {
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    std::cout << id << ": " << message << '\n';
}

Renderer::Renderer() {
    ImGui_ImplOpenGL3_Init();

    int version =
        gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));
    std::cout << "Loaded Glad v" << GLAD_VERSION_MAJOR(version) << '.'
              << GLAD_VERSION_MINOR(version) << '\n';

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                          GL_TRUE);

    // glEnable(GL_STENCIL_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glBlendEquation(GL_FUNC_ADD);
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
}

void Renderer::ImGuiBegin() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
}

void Renderer::ImGuiEnd() const {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::Begin() {
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Renderer::End() {
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Draw(const VertexArrayBuffer& vao, DrawType drawType, u32 count,
                    DataType datatype, void* indices) {
    vao.Bind();

    glDrawArrays(DrawTypeToGL(drawType), 0, count);

    vao.Unbind();
}

void Renderer::DrawIndexed(const VertexArrayBuffer& vao, const IndexBuffer& ebo,
                           DrawType drawType, u32 count, u32 start) {
    vao.Bind();
    ebo.Bind();

    u32 internalCount = count != 0 ? count : ebo.GetCount();
    glDrawElements(DrawTypeToGL(drawType), internalCount,
                   DataTypeToGL(DataType::UNSIGNED_INT), nullptr);

    ebo.Unbind();
    vao.Unbind();
}

void Renderer::Resize(u32 width, u32 height) {
    glViewport(0, 0, width, height);
}

void Renderer::Cull(CullMode cullMode) {
    switch (cullMode) {
    case CullMode::BOTH:
        glDisable(GL_CULL_FACE);
        break;
    case CullMode::BACK:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        break;
    case CullMode::FRONT:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        break;
    }
}

void Renderer::DepthTest(bool depthTest) {
    if (depthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::Blend(BlendType blendType) {}

void Renderer::Clear(glm::vec4 clearColor, u32 clearFlags) {
    glClearColor(clearColor.r, clearColor.g,
                 clearColor.b, clearColor.a);

    GLbitfield glClearFlags = 0;
    if (clearFlags & ClearFlags::COLOR) {
        glClearFlags |= GL_COLOR_BUFFER_BIT;
    }
    if (clearFlags & ClearFlags::DEPTH) {
        glClearFlags |= GL_DEPTH_BUFFER_BIT;
    }
    if (clearFlags & ClearFlags::STENCIL) {
        glClearFlags |= GL_STENCIL_BUFFER_BIT;
    }

    glClear(glClearFlags);
}
} // namespace Graphics
} // namespace Neptus

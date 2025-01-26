#include "ImGui.hpp"

#include "Core/OS/Window.hpp"
#include "Graphics/RHI/Texture.hpp"

#include <SDL.h>
#include <imgui_impl_sdl2.h>

#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    #include <imgui_impl_opengl3.h>
#endif

namespace Neptus {
void ImGuiInit(const Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    SDL_GLContext glContext = SDL_GL_GetCurrentContext();
    ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(window.GetHandle()),
                                 glContext);
    ImGui_ImplOpenGL3_Init();
#endif
}

void ImGuiBegin() {
#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    ImGui_ImplOpenGL3_NewFrame();
#endif

    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
}

void ImGuiEnd() {
    ImGui::Render();

#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void ImGuiDestroy() {
#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    ImGui_ImplOpenGL3_Shutdown();
#endif

    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiImage(const Graphics::Texture2D& texture) {
    ImGui::Image(texture.GetHandle(), ImGui::GetContentRegionAvail(),
                 {0.0f, 1.0f}, {1.0f, 0.0f});
}

void ImGuiProcessEvent(const ::SDL_Event& event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
}
} // namespace Neptus
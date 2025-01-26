#include "Core/OS/Window.hpp"

#include "Graphics/GraphicsContext.hpp"

#include <SDL.h>
#include <imgui_impl_sdl2.h>

namespace Neptus {
Window::Window(const WindowProps& props) {
    Init(props);
}

Window::~Window() {
    SDL_DestroyWindow(m_Handle);
    SDL_Quit();
}

bool Window::Init(const WindowProps& props) {
    SDL_Init(SDL_INIT_VIDEO);
    u32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        flags |= SDL_WINDOW_OPENGL;
#endif

    m_Handle = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, props.Width,
                                props.Height, flags);

#ifdef NEPTUS_BUILD_RENDERSYSTEM_GL
    SDL_GLContext glContext = SDL_GL_CreateContext(m_Handle);
#endif

    if (!m_Handle) {
        return false;
    }

    return true;
}

void Window::OnUpdate() {
    SDL_GL_SwapWindow(m_Handle);
}

void Window::ProcessInput() {}

std::string Window::GetTitle() const {
    return SDL_GetWindowTitle(m_Handle);
}

f32 Window::GetAspectRatio() const {
    return static_cast<f32>(GetWidth()) / static_cast<f32>(GetHeight());
}

u32 Window::GetWidth() const {
    i32 w = 0;
    SDL_GetWindowSize(m_Handle, &w, nullptr);
    return static_cast<u32>(w);
}

u32 Window::GetHeight() const {
    i32 h = 0;
    SDL_GetWindowSize(m_Handle, nullptr, &h);
    return static_cast<u32>(h);
}

void Window::SetTitle(const std::string& title) {
    SDL_SetWindowTitle(m_Handle, title.c_str());
}

void Window::RequestResolution(u32 width, u32 height) {
    SDL_SetWindowSize(m_Handle, static_cast<i32>(width),
                      static_cast<i32>(height));
}

void Window::HideMouse(bool hide) {
    SDL_ShowCursor(hide ? SDL_DISABLE : SDL_ENABLE);
}

void Window::Minimize() {
    SDL_MaximizeWindow(m_Handle);
}

void Window::Maximize() {
    SDL_MinimizeWindow(m_Handle);
}

WindowHandle Window::GetHandle() const {
    return m_Handle;
}
} // namespace Neptus

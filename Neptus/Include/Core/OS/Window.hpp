#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "string"

struct SDL_Window;
namespace Neptus {
using WindowHandle = void*;

struct NP_API WindowProps {
    WindowProps(const std::string& title = "Neptus", u32 width = 1280,
                u32 height = 720, bool fullscreen = false,
                bool borderless = false)
        : Title(title), Width(width), Height(height), Fullscreen(fullscreen),
          Borderless(borderless) {}

    std::string Title;
    u32 Width, Height;
    bool Fullscreen;
    bool Borderless;
};

class NP_API Window {
public:
    Window(const WindowProps& props = {});
    ~Window();

    bool Init(const WindowProps& props);
    void OnUpdate();
    void ProcessInput();

    void SetTitle(const std::string& title);
    void RequestResolution(u32 width, u32 height);

    [[nodiscard]] std::string GetTitle() const;
    [[nodiscard]] f32 GetAspectRatio() const;
    [[nodiscard]] u32 GetWidth() const;
    [[nodiscard]] u32 GetHeight() const;

    void HideMouse(bool hide);
    void Minimize();
    void Maximize();

    [[nodiscard]] WindowHandle GetHandle() const;
    // [[nodiscard]] void* GetProcAdress() const;

private:
    SDL_Window* m_Handle = nullptr;
};
} // namespace Neptus

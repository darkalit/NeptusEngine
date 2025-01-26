#pragma once

#include "Core/API.hpp"

#include <imgui.h>

union SDL_Event;

namespace Neptus {
class Window;

namespace Graphics {
class Texture2D;
}

void ImGuiInit(const Window& window);
void ImGuiBegin();
void ImGuiEnd();
void ImGuiDestroy();
void ImGuiImage(const Graphics::Texture2D& texture);

void ImGuiProcessEvent(const ::SDL_Event& event);
} // namespace Neptus
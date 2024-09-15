#pragma once

#include <imgui.h>
#include <imgui_stdlib.h>

#include <string>

namespace Neptus::Graphics {
class Framebuffer;
} // Neptus::Graphics

struct ImRect;
namespace ImGui {
    bool TempInputText(const ImRect& bb, ImGuiID id, const char* label, std::string* str, ImGuiInputTextFlags flags = 0);
    bool SelectableInput(const char* str_id, bool selected, std::string* str, ImGuiSelectableFlags flags = 0);
} // namespace ImGui
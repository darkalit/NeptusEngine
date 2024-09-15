#include "Widgets.hpp"

#include <imgui_internal.h>
#include <imgui_stdlib.h>

namespace ImGui {
bool SelectableInput(const char* str_id, bool selected,
                     std::string* str, ImGuiSelectableFlags flags) {
    static ImGuiID activeId = 0;

    ImGuiContext& g = *GImGui;
    ImVec2 pos = GetCursorPos();

    PushID(str_id);

    PushStyleVar(ImGuiStyleVar_ItemSpacing, {g.Style.ItemSpacing.x, g.Style.FramePadding.y * 3.0f});
    const bool ret = Selectable("##Selectable", selected, flags | ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_AllowOverlap);
    PopStyleVar();

    if (ret && IsMouseDoubleClicked(0)) {
        activeId = GetID(str_id);
    }

    SetItemAllowOverlap();
    SameLine();
    if (activeId == GetID(str_id)) {
        SetCursorPosY(pos.y);
        PushStyleVar(ImGuiStyleVar_FramePadding, {0.0f, g.Style.FramePadding.y});
        if (InputText("##Input", str, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
            activeId = 0;
        }
        PopStyleVar();
        if (!IsItemHovered() && IsMouseClicked(0)) {
            activeId = 0;
        }
    } else {
        AlignTextToFramePadding();
        Text(str->c_str());
    }

    PopID();

    return ret;
}
} // namespace ImGui
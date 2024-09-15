#pragma once

#include "Core/Engine.hpp"
#include "Scene/Entity.hpp"
#include "EditorCamera.hpp"

namespace Neptus {
class Editor final : public Engine {
public:
    void Run() override;

private:
    EditorCamera m_Camera;
    Entity m_ChosenEntity;
    bool m_CameraMove = false;
};
} // namespace Neptus
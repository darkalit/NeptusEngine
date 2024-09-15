#pragma once

#include "Core/Base.hpp"

#include <glm/glm.hpp>

namespace Neptus {
struct EditorCamera {
    enum class ProjectionType : u8 {
        Perspective,
        Orthographic,
    };

    glm::mat4 GetProj(float aspectRatio) const;
    glm::mat4 GetView() const;
    void UpdateBaseVecs();

    ProjectionType ProjectionType = ProjectionType::Perspective;

    glm::vec3 Forward = {};
    glm::vec3 Up = {};
    glm::vec3 Right = {};
    glm::vec3 WorldUp = {0.0f, 1.0f, 0.0f};

    glm::vec3 Position = glm::vec3{0.0f};
    f32 Yaw = 90.0f;
    f32 Pitch = 0.0f;

    f32 Speed = 100.0f;
    f32 Sensitivity = 0.2f;

    f32 Fov = 45.0f;
    f32 NearBound = 0.001f;
    f32 FarBound = 100.0f;
};
} // namespace Neptus
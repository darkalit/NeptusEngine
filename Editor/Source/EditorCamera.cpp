#include "EditorCamera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Neptus {
glm::mat4 EditorCamera::GetProj(float aspectRatio) const {
    switch (ProjectionType) {
    case ProjectionType::Perspective:
        return glm::perspective(glm::radians(Fov), aspectRatio, NearBound, FarBound);
    case ProjectionType::Orthographic:
        return glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, NearBound, FarBound);
    }

    return {1.0f};
}

glm::mat4 EditorCamera::GetView() const {
    return glm::lookAt(Position, Position + Forward, Up);
}

void EditorCamera::UpdateBaseVecs() {
    Forward = glm::vec3{
        glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch)),
        glm::sin(glm::radians(Pitch)),
        glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch)),
    };
    Forward = glm::normalize(Forward);

    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Right, Forward));
}
} // namespace Neptus
#pragma once

#include "Scene/Components/BaseComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Neptus {
namespace Components {
class NP_API TransformComponent : public BaseComponent {
    COMPONENT(TransformComponent)
public:
    [[nodiscard]] glm::mat4 GetTransform() const {
        const glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

        return glm::translate(glm::mat4(1.0f), Translation)
            * rotation
            * glm::scale(glm::mat4(1.0f), Scale);
    }

    glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Scale = {1.0f, 1.0f, 1.0f};
};
} // namespace Components
} // namespace Neptus

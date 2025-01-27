#pragma once

#include "Graphics/Model.hpp"
#include "Scene/Components/BaseComponent.hpp"

#include <glm/glm.hpp>

namespace Neptus {
namespace Components {
class NP_API ModelComponent : public BaseComponent {
    COMPONENT(ModelComponent)
public:
    ModelComponent(const SharedPtr<Graphics::Model>& model) {
        Model = model;
    }

    SharedPtr<Graphics::Model> Model;
};
} // namespace Components
} // namespace Neptus
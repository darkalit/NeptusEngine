#pragma once

#include "Scene/Components/BaseComponent.hpp"

namespace Neptus {
namespace Components {
class NP_API IDComponent : public BaseComponent {
    COMPONENT(IDComponent)
public:
    IDComponent(const UUID& id)
        : ID(id) {}

    UUID ID;
};
} // namespace Components
} // namespace Neptus

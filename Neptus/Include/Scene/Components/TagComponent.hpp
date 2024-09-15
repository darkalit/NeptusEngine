#pragma once

#include "Scene/Components/BaseComponent.hpp"

#include <string>

namespace Neptus {
namespace Components {
class NP_API TagComponent : public BaseComponent {
    COMPONENT(TagComponent)
public:
    TagComponent(const std::string& tag)
        : Tag(tag) {}

    std::string Tag;
};
} // namespace Components
} // namespace Neptus

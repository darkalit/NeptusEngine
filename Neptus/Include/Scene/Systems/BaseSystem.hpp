#pragma once

#include "Core/Asset.hpp"

namespace Neptus {
class Scene;
class Timestep;

namespace Systems {
class NP_API BaseSystem : public Asset {
    ASSET(System)
public:
    virtual void OnReady(const Scene* scene) = 0;

    virtual void OnUpdate(const Timestep& dt, const Scene* scene) = 0;
};
} // namespace Systems
} // namespace Neptus

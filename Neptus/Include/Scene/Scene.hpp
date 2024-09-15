#pragma once

#include "Core/Asset.hpp"

#include <entt/entt.hpp>
#include <string>

namespace Neptus {
class Entity;

class NP_API Scene : public Asset {
    ASSET(Scene)
public:
    Scene() = default;
    Scene(const std::string& name);
    Scene(const Scene&) = delete;
    Scene(Scene&& other) noexcept;
    ~Scene() override;

    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&& other) noexcept;

    Entity CreateEntity(const std::string& name = "");
    Entity GetEntityByHandle(const entt::entity& enttId);
    Entity GetEntityByUUID(const UUID& uuid);

    template <typename... Components>
    auto GetAllEntitiesWith() {
        return m_Registry.view<Components...>();
    }

    void DestroyEntity(const Entity& entity);

    std::string Name;
private:
    entt::registry m_Registry;

    friend class Entity;
};
} // namespace Neptus

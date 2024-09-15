#include "Scene/Scene.hpp"

#include "Scene/Components/IDComponent.hpp"
#include "Scene/Entity.hpp"

namespace Neptus {
Scene::Scene(const std::string& name)
    : Name(name) {}

Scene::Scene(Scene&& other) noexcept
    : Name(std::move(other.Name))
    , m_Registry(std::move(other.m_Registry)) {}

Scene::~Scene() {
    for (const auto& [entity] : m_Registry.storage<entt::entity>().each()) {
        m_Registry.destroy(entity);
    }
    m_Registry.clear();
}

Scene& Scene::operator=(Scene&& other) noexcept {
    if (this != &other) {
        Name = std::move(other.Name);
        m_Registry = std::move(other.m_Registry);
    }

    return *this;
}

Entity Scene::CreateEntity(const std::string& name) {
    Entity entity(m_Registry.create(), this);

    UUID uuid;
    entity.AddComponent<Components::IDComponent>(uuid);
    entity.AddComponent<Components::TagComponent>(name.empty() ? "Entity"
                                                               : name);
    return entity;
}

Entity Scene::GetEntityByHandle(const entt::entity& enttId) {
    return {enttId, this};
}

Entity Scene::GetEntityByUUID(const UUID& uuid) {
    auto view = GetAllEntitiesWith<Components::IDComponent>();

    for (auto entity : view) {
        auto& idComponent = m_Registry.get<Components::IDComponent>(entity);

        if (idComponent.ID == uuid) {
            return {entity, this};
        }
    }

    return {};
}

void Scene::DestroyEntity(const Entity& entity) {
    m_Registry.destroy(entity);
}
} // namespace Neptus

#pragma once

#include "Scene/Components/TagComponent.hpp"
#include "Scene/Scene.hpp"

#include <entt/entt.hpp>

namespace Neptus {
class NP_API Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene)
        : m_Handle(handle)
        , m_Scene(scene) {}

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        return m_Scene->m_Registry.emplace<T>(m_Handle,
                                              std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent() {
        return m_Scene->m_Registry.get<T>(m_Handle);
    }

    std::vector<entt::type_info> GetComponentsType() const {
        std::vector<entt::type_info> componentsType = {};

        for (auto&& curr : m_Scene->m_Registry.storage()) {
            if (auto& storage = curr.second; storage.contains(m_Handle)) {
                entt::type_info ctype = storage.type();
                componentsType.push_back(ctype);
            }
        }

        return componentsType;
    }

    template <typename T>
    void RemoveComponent() {
        m_Scene->m_Registry.remove<T>(m_Handle);
    }

    template <typename T>
    bool HasComponent() const {
        return m_Scene->m_Registry.all_of<T>(m_Handle);
    }

    const std::string& GetName() {
        return GetComponent<Components::TagComponent>().Tag;
    }

    operator bool() const { return m_Handle != entt::null && m_Scene; }
    operator entt::entity() const { return m_Handle; }

    template <typename T>
    static std::string GetComponentName() {
        return std::string(entt::type_id<T>().name());
    }

private:
    entt::entity m_Handle = entt::null;
    Scene* m_Scene = nullptr;
};
} // namespace Neptus

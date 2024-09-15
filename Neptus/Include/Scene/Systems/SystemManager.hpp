#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

#include "Scene/Systems/BaseSystem.hpp"

#include <unordered_map>

namespace Neptus {
namespace Systems {
class NP_API SystemManager {
public:
    ~SystemManager() {
        for (auto& [_, system] : m_Systems) {
            delete system;
        }
    }

    template <typename T>
    void Register() {
        size_t hash = typeid(T).hash_code();

        m_Systems.emplace(hash, new T);
    }

    template <typename T>
    void Remove() {
        size_t hash = typeid(T).hash_code();

        const auto pair = m_Systems.find(hash);
        delete pair->second;
        pair->second = nullptr;
        m_Systems.erase(hash);
    }

    template <typename T>
    bool HasSystem() {
        size_t hash = typeid(T).hash_code();

        return m_Systems.find(hash) != m_Systems.end();
    }

    void OnReady(const Scene* scene) {
        for (auto& [hash, system] : m_Systems) {
            system->OnReady(scene);
        }
    }
    void OnUpdate(const Timestep& dt, const Scene* scene) {
        for (auto& [hash, system] : m_Systems) {
            system->OnUpdate(dt, scene);
        }
    }

private:
    std::unordered_map<size_t, BaseSystem*> m_Systems;
};
} // namespace Systems
} // namespace Neptus

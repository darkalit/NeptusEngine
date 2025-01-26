#pragma once

#include "Core/API.hpp"
#include "Core/UUID.hpp"

#include <string>
#include <vector>

namespace Neptus {
class Scene;

class NP_API SceneManager {
public:
    SceneManager() = default;
    ~SceneManager() = default;

    [[nodiscard]] SharedPtr<Scene> GetCurrentScene() const;
    [[nodiscard]] size_t GetCurrentSceneIndex() const;
    SharedPtr<Scene> CreateScene(const std::string& name);
    void RemoveScene(const UUID& id);
    void RemoveScene(size_t index);
    void AddScene(const SharedPtr<Scene>& scene);
    void SwitchScene(const UUID& id);
    void SwitchScene(size_t index);

private:
    SharedPtr<Scene> m_CurrentScene = nullptr;
    size_t m_CurrentSceneIndex = 0;
    std::vector<SharedPtr<Scene>> m_Scenes = {};
};
} // namespace Neptus
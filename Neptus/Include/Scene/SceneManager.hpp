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

    [[nodiscard]] Scene& GetCurrentScene() const;
    [[nodiscard]] size_t GetCurrentSceneIndex() const;
    Scene& CreateScene(const std::string& name);
    void RemoveScene(const UUID& id);
    void RemoveScene(size_t index);
    void AddScene(Scene&& scene);
    void SwitchScene(const UUID& id);
    void SwitchScene(size_t index);

private:
    Scene* m_CurrentScene = nullptr;
    size_t m_CurrentSceneIndex = 0;
    std::vector<Scene> m_Scenes = {};
};
} // namespace Neptus
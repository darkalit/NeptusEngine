#include "Scene/SceneManager.hpp"

#include "Scene/Scene.hpp"

namespace Neptus {
Scene& SceneManager::GetCurrentScene() const {
    return *m_CurrentScene;
}

size_t SceneManager::GetCurrentSceneIndex() const {
    return m_CurrentSceneIndex;
}

Scene& SceneManager::CreateScene(const std::string& name) {
    return m_Scenes.emplace_back(name);
}

void SceneManager::RemoveScene(const UUID& id) {
    m_Scenes.erase(std::remove_if(m_Scenes.begin(), m_Scenes.end(), [&id](const Scene& val) {
        return val.GetID() == id;
    }), m_Scenes.end());
}

void SceneManager::RemoveScene(size_t index) {
    m_Scenes.erase(m_Scenes.begin() + index);
}

void SceneManager::AddScene(Scene&& scene) {
    m_Scenes.push_back(std::move(scene));
}

void SceneManager::SwitchScene(const UUID& id) {
    const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&id](const Scene& val) {
        return val.GetID() == id;
    });
    if (it == m_Scenes.end()) {
        // Error
        return;
    }

    m_CurrentScene = &*it;
    m_CurrentSceneIndex = std::distance(m_Scenes.begin(), it);
}

void SceneManager::SwitchScene(size_t index) {
    m_CurrentScene = &m_Scenes.at(index);
    m_CurrentSceneIndex = index;
}

} // namespace Neptus
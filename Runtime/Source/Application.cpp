#include "Application.hpp"

#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Components/TransformComponent.hpp"
#include "Scene/Components/ModelComponent.hpp"
#include "Utils/Clock.hpp"

#include <SDL.h>

namespace Neptus {
void Application::Run() {
    auto scene = m_SceneManager.CreateScene("main");
    auto _ = scene->CreateEntity("gordon");
    _.AddComponent<Components::TransformComponent>();
    _.GetComponent<Components::TransformComponent>().Translation.y += 60.0f;
    m_ResourceManager.AddModel("Neptus/Assets/Models/hl2gordon_freeman/gordon.obj");
    _.AddComponent<Components::ModelComponent>(&m_ResourceManager.GetModel("Neptus/Assets/Models/hl2gordon_freeman/gordon.obj"));
    m_SceneManager.SwitchScene(scene->GetID());

    glm::mat4 proj =
        glm::perspective(glm::radians(45.0f),
                         static_cast<f32>(m_Window.GetWidth()) /
                             static_cast<f32>(m_Window.GetHeight()),
                         0.001f, 200.0f);
    glm::mat4 view = glm::mat4{1.0f};
    view = glm::translate(view, {0.0f, 0.0f, -80.0f});

    SDL_Event event;

    while (m_Running) {
        EngineClock::Update();

        m_Frames++;
        m_Updates++;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_Running = false;
            }
        }

        _.GetComponent<Components::TransformComponent>().Rotation = {0.0f, EngineClock::GetTime().Seconds(), 0.0f};

        m_RenderPasses.BeginScene(m_SceneManager.GetCurrentScene());
        m_RenderPasses.OnRender(proj, view);

        m_Window.OnUpdate();
    }
}
} // namespace Neptus
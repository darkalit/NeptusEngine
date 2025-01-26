#include "Editor.hpp"

#include "Core/UUID.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Components/IDComponent.hpp"
#include "Scene/Components/TagComponent.hpp"
#include "Scene/Components/TransformComponent.hpp"
#include "Scene/Components/ModelComponent.hpp"
#include "Utils/Clock.hpp"
#include "Widgets.hpp"
#include "ImGui.hpp"

#include <glm/gtc/type_ptr.inl>

#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace Neptus {
void Editor::Run() {
    ImGuiInit(m_Window);

    m_ResourceManager.AddModel("Neptus/Assets/Models/hl2gordon_freeman/gordon.obj");
    m_ResourceManager.AddModel("Neptus/Assets/Models/backpack/backpack.obj");

    auto& scene = m_SceneManager.CreateScene("main");
    auto _ = scene->CreateEntity("gordon");
    _.AddComponent<Components::TransformComponent>();
    _.GetComponent<Components::TransformComponent>().Translation.y += 60.0f;
    _.AddComponent<Components::ModelComponent>(m_ResourceManager.GetModel("Neptus/Assets/Models/hl2gordon_freeman/gordon.obj"));

    _ = scene->CreateEntity("backpack");
    _.AddComponent<Components::TransformComponent>();
    _.GetComponent<Components::TransformComponent>().Scale *= 6.0f;
    _.AddComponent<Components::ModelComponent>(m_ResourceManager.GetModel("Neptus/Assets/Models/backpack/backpack.obj"));

    m_SceneManager.SwitchScene(scene->GetID());

    f32 width = m_Window.GetWidth(), height = m_Window.GetHeight();

    SDL_Event event;

    m_Camera.Position.z = -80.0f;
    m_Camera.FarBound = 200.0f;

    while (m_Running) {
        EngineClock::Update();
        m_Camera.UpdateBaseVecs();

        m_Frames++;
        m_Updates++;

        while (SDL_PollEvent(&event)) {
            ImGuiProcessEvent(event);
            switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    m_RenderPasses.Resize(m_Window.GetWidth(), m_Window.GetHeight());
                }
                break;
            case SDL_QUIT:
                m_Running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    m_CameraMove = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    m_CameraMove = false;
                }
                break;
            case SDL_MOUSEMOTION:
                if (m_CameraMove) {
                    f32 xoffset = event.motion.xrel * m_Camera.Sensitivity;
                    f32 yoffset = event.motion.yrel * m_Camera.Sensitivity;

                    m_Camera.Yaw += xoffset;
                    m_Camera.Pitch -= yoffset;

                    m_Camera.Pitch = glm::clamp(m_Camera.Pitch, -89.0f, 89.0f);
                }
                break;
            default:
                break;
            }
        }

        const u8* keyboardState = SDL_GetKeyboardState(nullptr);
        if (keyboardState[SDL_SCANCODE_W]) {
            m_Camera.Position += m_Camera.Forward * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_S]) {
            m_Camera.Position -= m_Camera.Forward * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_E]) {
            m_Camera.Position += glm::cross(m_Camera.WorldUp, m_Camera.Right) * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_Q]) {
            m_Camera.Position -= glm::cross(m_Camera.WorldUp, m_Camera.Right) * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_D]) {
            m_Camera.Position += m_Camera.Right * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_A]) {
            m_Camera.Position -= m_Camera.Right * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_SPACE]) {
            m_Camera.Position += m_Camera.WorldUp * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }
        if (keyboardState[SDL_SCANCODE_LSHIFT]) {
            m_Camera.Position -= m_Camera.WorldUp * (m_Camera.Speed * static_cast<f32>(EngineClock::GetDelta().Seconds()));
        }

        m_Window.HideMouse(m_CameraMove);
        m_RenderPasses.BeginScene(*m_SceneManager.GetCurrentScene());
        m_RenderPasses.OnRender(m_Camera.GetProj(width / height),  m_Camera.GetView());

        ImGuiBegin();

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        if (ImGui::Begin("Viewport")) {
            width = ImGui::GetContentRegionAvail().x;
            height = ImGui::GetContentRegionAvail().y;
            ImGuiImage(m_RenderPasses.GetFramebuffers()["PostEffects"]
                           .GetColorAttachments()[0]);

            // TODO: fix Window cannot be moved
            m_CameraMove = ImGui::IsWindowFocused() && ImGui::IsMouseDown(0);
        }
        ImGui::End();

        if (ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse)) {
            ImGui::Text("Frames count: %llu, Updates count: %llu", m_Frames, m_Updates);
        }
        ImGui::End();

        if (ImGui::Begin("Camera Panel")) {
            ImGui::SeparatorText("Feel");
            ImGui::DragFloat("Fov", &m_Camera.Fov, 1.0f, 1.0f, 170.0f);
            ImGui::DragFloat("Speed", &m_Camera.Speed, 0.2f, 0.0f);
            ImGui::DragFloat("Sensitivity", &m_Camera.Sensitivity, 0.01f, 0.0f, 2.0f);

            ImGui::SeparatorText("Transformations");
            ImGui::DragFloatRange2("Clip Bounds", &m_Camera.NearBound, &m_Camera.FarBound, 0.1f, 0.001f, 2000.0f);
            ImGui::DragFloat3("Position", glm::value_ptr(m_Camera.Position), 0.1f);
        }
        ImGui::End();

        if (ImGui::Begin("Scene Explorer")) {
            m_SceneManager.GetCurrentScene()
                ->GetAllEntitiesWith<Components::IDComponent,
                                     Components::TagComponent>()
                .each([this](const auto entity, auto& idComponent, auto& tagComponent) {
                    if (ImGui::SelectableInput(std::to_string(static_cast<u64>(idComponent.ID)).c_str(), m_ChosenEntity == entity, &tagComponent.Tag)) {
                        m_ChosenEntity =
                            m_SceneManager.GetCurrentScene()->GetEntityByHandle(
                                entity);
                    }
                });
        }
        ImGui::End();

        if (ImGui::Begin("Components Explorer")) {
            if (m_ChosenEntity) {
                for (auto& type : m_ChosenEntity.GetComponentsType()) {
                    if (Entity::GetComponentName<Components::IDComponent>() == type.name() && ImGui::TreeNodeEx("ID Component", ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        ImGui::Text("%llu", static_cast<u64>(m_ChosenEntity.GetComponent<Components::IDComponent>().ID));
                        ImGui::TreePop();
                    }
                    if (Entity::GetComponentName<Components::TagComponent>() == type.name() && ImGui::TreeNodeEx("Tag Component", ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        ImGui::Text("%s", m_ChosenEntity.GetComponent<Components::TagComponent>().Tag.c_str());
                        ImGui::TreePop();
                    }
                    if (Entity::GetComponentName<Components::TransformComponent>() == type.name() && ImGui::TreeNodeEx("Transform Component", ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        auto& transformComponent = m_ChosenEntity.GetComponent<Components::TransformComponent>();
                        ImGui::DragFloat3("Position", glm::value_ptr(transformComponent.Translation), 0.1f);
                        ImGui::DragFloat3("Rotation", glm::value_ptr(transformComponent.Rotation), 0.1f);
                        ImGui::DragFloat3("Scale", glm::value_ptr(transformComponent.Scale), 0.1f);
                        ImGui::TreePop();
                    }
                    if (Entity::GetComponentName<Components::ModelComponent>() == type.name() && ImGui::TreeNodeEx("Model Component", ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        auto& modelComponent = m_ChosenEntity.GetComponent<Components::ModelComponent>();
                        ImGui::Text("Filepath: %s", modelComponent.Model->GetAssetPath().c_str());
                        ImGui::TreePop();
                    }
                }
            }
        }
        ImGui::End();
        ImGuiEnd();

        m_Window.OnUpdate();
    }

    ImGuiDestroy();
}
} // namespace Neptus

int main() {
    Neptus::Editor editor;
    editor.Run();

    return 0;
}
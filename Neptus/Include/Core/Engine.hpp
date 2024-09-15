#pragma once

#include "Core/Base.hpp"
#include "Core/OS/Window.hpp"
#include "Graphics/RenderPasses.hpp"
#include "Scene/SceneManager.hpp"
#include "Utils/ResourceManager.hpp"

namespace Neptus {
class Engine {
public:
    Engine();
    virtual ~Engine() = default;

    virtual void Run() = 0;

protected:
    Window m_Window;
    Graphics::RenderPasses m_RenderPasses;
    ResourceManager m_ResourceManager;
    SceneManager m_SceneManager;

    u64 m_Frames = 0;
    u64 m_Updates = 0;
    bool m_Running = true;
};
} // namespace Neptus
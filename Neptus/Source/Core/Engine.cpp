#include "Core/Engine.hpp"

namespace Neptus {
Engine::Engine()
    : m_RenderPasses(m_Window.GetWidth(), m_Window.GetHeight())
{}
} // namespace Neptus
#include "Graphics/GraphicsContext.hpp"

namespace Neptus {
namespace Graphics {
RenderAPI GraphicsContext::s_RenderAPI = RenderAPI::OpenGL;

void GraphicsContext::SwitchAPI(const RenderAPI renderApi) {
    s_RenderAPI = renderApi;
}
RenderAPI GraphicsContext::GetAPI() {
    return s_RenderAPI;
}
} // namespace Graphics
} // namespace Neptus
#pragma once

namespace Neptus {
namespace Graphics {
enum class RenderAPI {
    OpenGL,
};

class GraphicsContext {
public:
    static void SwitchAPI(RenderAPI renderApi);
    static RenderAPI GetAPI();

private:
    static RenderAPI s_RenderAPI;
};
} // namespace Graphics
} // namespace Neptus
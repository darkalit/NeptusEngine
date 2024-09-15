#pragma once
#include "RHI/IndexBuffer.hpp"
#include "RHI/VertexArrayBuffer.hpp"

namespace Neptus {
namespace Graphics {
class ScreenSurface {
public:
    ScreenSurface();
    ScreenSurface(const ScreenSurface&) = delete;
    ScreenSurface(ScreenSurface&& other) noexcept;
    ~ScreenSurface() = default;

    ScreenSurface& operator=(const ScreenSurface&) = delete;
    ScreenSurface& operator=(ScreenSurface&& other) noexcept;

    VertexArrayBuffer VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;
};
} // namespace Graphics
} // namespace Neptus
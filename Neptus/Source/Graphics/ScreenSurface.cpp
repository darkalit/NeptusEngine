#include "Graphics/ScreenSurface.hpp"

#include "Graphics/RHI/BufferLayout.hpp"

namespace Neptus {
namespace Graphics {
static f32 sVertices[] {
    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
};

static u32 sIndices[] {
    0, 1, 3,
    0, 3, 2,
};

ScreenSurface::ScreenSurface() {
    VBO = VertexBuffer(sVertices, sizeof(sVertices), BufferUsage::STATIC);
    EBO = IndexBuffer(sIndices, std::size(sIndices), BufferUsage::STATIC);

    BufferLayout layout;
    layout.Push<f32>(2);
    layout.Push<f32>(2);

    VAO = VertexArrayBuffer(VBO, layout);

    VAO.Bind();
    EBO.Bind();
}

ScreenSurface::ScreenSurface(ScreenSurface&& other) noexcept
    : VAO(std::move(other.VAO))
    , VBO(std::move(other.VBO))
    , EBO(std::move(other.EBO)) {}

ScreenSurface& ScreenSurface::operator=(ScreenSurface&& other) noexcept {
    if (this != &other) {
        VAO = std::move(other.VAO);
        VBO = std::move(other.VBO);
        EBO = std::move(other.EBO);
    }

    return *this;
}
} // namespace Graphics
} // namespace Neptus
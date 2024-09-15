#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Definitions.hpp"
#include "Graphics/RHI/VertexArrayBuffer.hpp"
#include "Graphics/RHI/IndexBuffer.hpp"

#include <glm/glm.hpp>

namespace Neptus {
namespace Graphics {
enum ClearFlags : u32 {
    COLOR = BIT(0),
    DEPTH = BIT(1),
    STENCIL = BIT(2),
};

class NP_API Renderer {
public:
    Renderer();
    ~Renderer();

    void ImGuiBegin() const;
    void ImGuiEnd() const;

    void Begin();
    void End();
    void Draw(const VertexArrayBuffer& vao,
              DrawType drawType = DrawType::TRIANGLE, u32 count = 0,
              DataType datatype = DataType::UNSIGNED_INT,
              void* indices = nullptr);
    void DrawIndexed(const VertexArrayBuffer& vao, const IndexBuffer& ebo,
                     DrawType drawType = DrawType::TRIANGLE, u32 count = 0,
                     u32 start = 0);
    void Resize(u32 width, u32 height);

    static void Cull(CullMode cullMode = CullMode::BOTH);
    static void DepthTest(bool depthTest);
    static void Blend(BlendType blendType = BlendType::NONE);
    static void Clear(glm::vec4 clearColor = {0.1f, 0.1f, 0.1f, 1.0f},
                      u32 clearFlags = ClearFlags::COLOR | ClearFlags::DEPTH);
};
} // namespace Graphics
} // namespace Neptus

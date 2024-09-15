#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/VertexBuffer.hpp"

namespace Neptus {
namespace Graphics {
class BufferLayout;

class NP_API VertexArrayBuffer {
public:
    VertexArrayBuffer() = default;
    VertexArrayBuffer(const VertexBuffer& vb, const BufferLayout& layout);
    VertexArrayBuffer(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer(VertexArrayBuffer&& other) noexcept;
    ~VertexArrayBuffer();

    VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer& operator=(VertexArrayBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

private:
    void Release();

    union {
        // OpenGl handle
        u32 m_Handle;
    };
};
} // namespace Graphics
} // namespace Neptus

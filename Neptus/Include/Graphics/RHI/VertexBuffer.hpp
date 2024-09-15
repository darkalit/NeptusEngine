#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Definitions.hpp"

namespace Neptus {
namespace Graphics {
class NP_API VertexBuffer {
public:
    VertexBuffer() = default;
    VertexBuffer(BufferUsage usage);
    VertexBuffer(const void* data, u32 size, BufferUsage usage);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& other) noexcept;
    ~VertexBuffer();

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void SetData(const void* data, u32 size);
    u32 GetSize() const;
    void Bind() const;
    void Unbind() const;

private:
    void Release();

    union {
        // OpenGl handle
        u32 m_Handle;
    };
    u32 m_Size = 0;
    BufferUsage m_Usage = BufferUsage::STATIC;
};
} // namespace Graphics
} // namespace Neptus

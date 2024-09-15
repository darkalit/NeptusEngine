#include "Graphics/RHI/VertexBuffer.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"

#include "glad/gl.h"

namespace Neptus {
namespace Graphics {
VertexBuffer::VertexBuffer(const BufferUsage usage)
    : m_Handle(0)
    , m_Usage(usage) {
    glGenBuffers(1, &m_Handle);
}

VertexBuffer::VertexBuffer(const void* data, u32 size,
                               const BufferUsage usage)
    : m_Handle(0)
    , m_Usage(usage) {
    glGenBuffers(1, &m_Handle);
    SetData(data, size);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_Size(other.m_Size)
    , m_Usage(other.m_Usage) {
    other.m_Handle = 0;
}

VertexBuffer::~VertexBuffer() {
    Release();
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
        m_Size = other.m_Size;
        m_Usage = other.m_Usage;
    }

    return *this;
}

void VertexBuffer::SetData(const void* data, u32 size) {
    m_Size = size;

    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToGL(m_Usage));
}

u32 VertexBuffer::GetSize() const {
    return m_Size;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Release() {
    glDeleteBuffers(1, &m_Handle);
    m_Handle = 0;
}

} // namespace Graphics
} // namespace Neptus

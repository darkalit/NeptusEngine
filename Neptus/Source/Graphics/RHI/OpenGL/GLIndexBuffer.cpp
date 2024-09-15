#include "Graphics/RHI/IndexBuffer.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"
#include "glad/gl.h"

namespace Neptus {
namespace Graphics {
IndexBuffer::IndexBuffer(const BufferUsage usage)
    : m_Handle(0)
    , m_Usage(usage) {
    glGenBuffers(1, &m_Handle);
}

IndexBuffer::IndexBuffer(const void* data, u32 count, const BufferUsage usage)
    : m_Handle(0)
    , m_Usage(usage) {
    glGenBuffers(1, &m_Handle);
    SetData(data, count);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_Count(other.m_Count)
    , m_Usage(other.m_Usage) {
    other.m_Handle = 0;
}

IndexBuffer::~IndexBuffer() {
    Release();
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
        m_Count = other.m_Count;
        m_Usage = other.m_Usage;
    }

    return *this;
}

void IndexBuffer::SetData(const void* data, u32 count) {
    m_Count = count;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data,
                 BufferUsageToGL(m_Usage));
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u32 IndexBuffer::GetCount() const {
    return m_Count;
}

void IndexBuffer::Release() {
    glDeleteBuffers(1, &m_Handle);
    m_Handle = 0;
}
} // namespace Graphics
} // namespace Neptus

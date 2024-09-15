#include "Graphics/RHI/VertexArrayBuffer.hpp"

#include "Graphics/RHI/GLDefinitions.hpp"
#include "Graphics/RHI/BufferLayout.hpp"

#include <glad/gl.h>

namespace Neptus {
namespace Graphics {
VertexArrayBuffer::VertexArrayBuffer(const VertexBuffer& vb,
                                     const BufferLayout& layout)
    : m_Handle(0) {
    glGenVertexArrays(1, &m_Handle);
    Bind();
    vb.Bind();

    const auto& elements = layout.GetElements();
    const u32 stride = layout.GetStride();
    u32 offset = 0;
    for (u32 i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        glVertexAttribPointer(
            i, element.Count, GLTypeFromFormat(element.Format),
            element.Normalized, stride, reinterpret_cast<const void*>(offset));
        glEnableVertexAttribArray(i);
        offset += element.Count * GetFormatByteSize(element.Format);
    }

    vb.Unbind();
    Unbind();
}

VertexArrayBuffer::VertexArrayBuffer(VertexArrayBuffer&& other) noexcept
    : m_Handle(other.m_Handle) {
    other.m_Handle = 0;
}

VertexArrayBuffer::~VertexArrayBuffer() {
    Release();
}

VertexArrayBuffer&
VertexArrayBuffer::operator=(VertexArrayBuffer&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
    }

    return *this;
}

void VertexArrayBuffer::Bind() const {
    glBindVertexArray(m_Handle);
}

void VertexArrayBuffer::Unbind() const {
    glBindVertexArray(0);
}

void VertexArrayBuffer::Release() {
    glDeleteVertexArrays(1, &m_Handle);
    m_Handle = 0;
}
} // namespace Graphics
} // namespace Neptus

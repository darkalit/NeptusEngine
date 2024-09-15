#include "Graphics/RHI/BufferLayout.hpp"

namespace Neptus {
namespace Graphics {
BufferLayout::BufferLayout()
    : m_Stride(0) {}

void BufferLayout::Push(RHIFormat format, u32 count, bool normalized) {
    m_Elements.push_back({count, normalized, format});
}

template <>
void BufferLayout::Push<u32>(u32 count, bool normalized) {
    Push(RHIFormat::R32_U, count, normalized);
    m_Stride += count * GetFormatByteSize(RHIFormat::R32_U);
}

template <>
void BufferLayout::Push<f32>(u32 count, bool normalized) {
    Push(RHIFormat::R32_F, count, normalized);
    m_Stride += count * GetFormatByteSize(RHIFormat::R32_F);
}

template <>
void BufferLayout::Push<u8>(u32 count, bool normalized) {
    Push(RHIFormat::R8_U, count, normalized);
    m_Stride += count * GetFormatByteSize(RHIFormat::R8_U);
}
} // namespace Graphics
} // namespace Neptus

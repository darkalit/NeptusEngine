#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Definitions.hpp"

#include <vector>

namespace Neptus {
namespace Graphics {
struct NP_API BufferElement {
    u32 Count;
    bool Normalized;
    RHIFormat Format;
};

class NP_API BufferLayout {
public:
    BufferLayout();

    template <typename T>
    void Push(u32 count, bool normalized = false) {}

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    u32 GetStride() const { return m_Stride; }

private:
    void Push(RHIFormat format, u32 count, bool normalized);

    std::vector<BufferElement> m_Elements = {};
    u32 m_Stride = 0;
};

template <>
void BufferLayout::Push<u32>(u32 count, bool normalized);

template <>
void BufferLayout::Push<f32>(u32 count, bool normalized);

template <>
void BufferLayout::Push<u8>(u32 count, bool normalized);

} // namespace Graphics
} // namespace Neptus

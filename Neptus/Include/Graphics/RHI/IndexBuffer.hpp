#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Graphics/RHI/Definitions.hpp"

namespace Neptus {
namespace Graphics {
class NP_API IndexBuffer {
public:
    IndexBuffer() = default;
    IndexBuffer(BufferUsage usage);
    IndexBuffer(const void* data, u32 count, BufferUsage usage);
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&& other) noexcept;
    ~IndexBuffer();

    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void SetData(const void* data, u32 count);
    void Bind() const;
    void Unbind() const;
    u32 GetCount() const;

private:
    void Release();

    union {
        u32 m_Handle;
    };
    u32 m_Count = 0;
    BufferUsage m_Usage = BufferUsage::STATIC;
};
} // namespace Graphics
} // namespace Neptus

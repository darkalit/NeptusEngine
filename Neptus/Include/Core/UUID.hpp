#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

namespace Neptus {
class NP_API UUID {
public:
    UUID();
    UUID(u64 uuid);
    UUID(const UUID& other);
    UUID(UUID&& other);

    ~UUID() = default;

    operator u64() const;
    operator const u64() const;
    operator u64&();
    operator const u64&() const;

    UUID& operator=(const UUID& other);
    UUID& operator=(UUID&& other) noexcept;
    bool operator==(const UUID& other) const;
    bool operator!=(const UUID& other) const;

private:
    u64 m_UUID;
};
} // namespace Neptus

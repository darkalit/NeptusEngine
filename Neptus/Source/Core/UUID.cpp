#include "Core/UUID.hpp"

#include <random>

namespace Neptus {
static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<u64> s_UniformDistribution;

UUID::UUID() : m_UUID(s_UniformDistribution(s_Engine)) {}

UUID::UUID(u64 uuid) : m_UUID(uuid) {}

UUID::UUID(const UUID& other)
    : m_UUID(other.m_UUID) {}

UUID::UUID(UUID&& other)
    : m_UUID(other.m_UUID) {
    other.m_UUID = 0;
}

UUID::operator u64() const {
    return m_UUID;
}

UUID::operator const u64() const {
    return m_UUID;
}
UUID::operator u64&() {
    return m_UUID;
}
UUID::operator const u64&() const {
    return m_UUID;
}

UUID& UUID::operator=(const UUID& other) {
    if (this != &other) {
        m_UUID = other.m_UUID;
    }

    return *this;
}

UUID& UUID::operator=(UUID&& other) noexcept {
    if (this != &other) {
        m_UUID = 0;
        std::swap(m_UUID, other.m_UUID);
    }

    return *this;
}

bool UUID::operator==(const UUID& other) const {
    return m_UUID == other.m_UUID;
}

bool UUID::operator!=(const UUID& other) const {
    return !(*this == other);
}
} // namespace Neptus

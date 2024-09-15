#include "Utils/Timestep.hpp"

namespace Neptus {
Timestep::Timestep(const TimePoint& time) : m_Time(time) {}

TimePoint const& Timestep::GetRaw() const {
    return m_Time;
}

f64 Timestep::Seconds() const {
    return static_cast<f64>(
        std::chrono::duration_cast<std::chrono::duration<double>>(
            m_Time.time_since_epoch())
            .count());
}

f64 Timestep::Millis() const {
    return static_cast<f64>(
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
            m_Time.time_since_epoch())
            .count());
}

f64 Timestep::Nanos() const {
    return static_cast<f64>(
        std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(
            m_Time.time_since_epoch())
            .count());
}
} // namespace Neptus

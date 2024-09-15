#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

#include <chrono>
using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace Neptus {
class NP_API Timestep {
public:
    Timestep(const TimePoint& time = {});

    TimePoint const& GetRaw() const;
    f64 Seconds() const;
    f64 Millis() const;
    f64 Nanos() const;

private:
    TimePoint m_Time;
};
} // namespace Neptus

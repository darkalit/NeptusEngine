#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

#include <chrono>
using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace Neptus {
class NP_API Timer {
public:
    Timer() = default;

    void Start();
    void Reset();

    static TimeStamp Now();
};
} // namespace Neptus

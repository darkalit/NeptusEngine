#include "Utils/Clock.hpp"

namespace Neptus {
Timestep EngineClock::s_CurrentTime = {};
Timestep EngineClock::s_DeltaTime = {};

void EngineClock::Update() {
    auto now = std::chrono::high_resolution_clock::now();
    s_DeltaTime = TimePoint(now - s_CurrentTime.GetRaw());
    s_CurrentTime = now;
}

Timestep EngineClock::GetTime() {
    return s_CurrentTime;
}

Timestep EngineClock::GetDelta() {
    return s_DeltaTime;
}
} // namespace Neptus

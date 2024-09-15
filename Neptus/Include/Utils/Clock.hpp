#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"
#include "Utils/Timestep.hpp"

namespace Neptus {
class NP_API EngineClock {
public:
    static void Update();
    static Timestep GetTime();
    static Timestep GetDelta();

private:
    static Timestep s_CurrentTime;
    static Timestep s_DeltaTime;
};
} // namespace Neptus

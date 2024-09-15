#pragma once

#include "Core/Engine.hpp"

namespace Neptus {
class Application final : public Engine {
public:
    void Run() override;
};
} // namespace Neptus
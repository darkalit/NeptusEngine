#pragma once

#include "Core/API.hpp"

#include <string>

namespace Neptus {
class NP_API Filesystem {
public:
    static std::string ReadTextFile(const std::string& filepath);
};
} // namespace Neptus

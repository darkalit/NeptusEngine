#pragma once

#include <string>

namespace Neptus {
inline const std::string DEFAULT_TRIM_CHARACTERS = " \t\n\r\f\v";

std::string& rtrim(std::string& str, const std::string& chars = DEFAULT_TRIM_CHARACTERS);

std::string& ltrim(std::string& str, const std::string& chars = DEFAULT_TRIM_CHARACTERS);

std::string& trim(std::string& str, const std::string& chars = DEFAULT_TRIM_CHARACTERS);
} // namespace Neptus

#include "Core/OS/Filesystem.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Neptus {
std::string Filesystem::ReadTextFile(const std::string& filepath) {\
    if (!std::filesystem::exists(filepath)) {\
        return "";
    }

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(filepath);
        std::cout << "Opened file: " << filepath << '\n';

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content(buffer.str());
        file.close();

        return content;
    } catch (std::ifstream::failure& e) {
        std::cout << e.what() << '\n';
        return "";
    }
}
} // namespace Neptus

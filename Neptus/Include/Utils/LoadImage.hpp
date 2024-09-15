#pragma once

#include "Core/API.hpp"
#include "Core/Base.hpp"

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#include <string>

namespace Neptus {
struct Image {
    u8* Data = nullptr;
    u32 Width = 0;
    u32 Height = 0;
    u32 Bits = 0;
    bool IsHDR = false;
};

NP_API Image LoadImageFromFile(const std::string& filepath, bool flipY = false);
} // namespace Neptus

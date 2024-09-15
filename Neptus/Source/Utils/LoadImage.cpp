#include "Utils/LoadImage.hpp"

#include <stb_image.h>

#include <filesystem>

namespace Neptus {
Image LoadImageFromFile(const std::string& filepath, bool flipY) {
    if (!std::filesystem::exists(filepath)) {
        return {};
    }

    bool isHDR = false;
    i32 texWidth = 0, texHeight = 0, texChannels = 0, sizeOfChannel = 8;
    u8* data = nullptr;

    stbi_set_flip_vertically_on_load(flipY);
    if (stbi_is_hdr(filepath.c_str())) {
        sizeOfChannel = 32;
        data = reinterpret_cast<u8*>(stbi_loadf(filepath.c_str(), &texWidth,
                                                &texHeight, &texChannels, 0));
    } else {
        data =
            stbi_load(filepath.c_str(), &texWidth, &texHeight, &texChannels, 0);
        isHDR = false;
    }

    if (!data) {
        return {};
    }

    const size_t size = static_cast<size_t>(texWidth) *
                        static_cast<size_t>(texHeight) *
                        static_cast<size_t>(texChannels) *
                        static_cast<size_t>(sizeOfChannel / 8U);
    Image res = {};
    res.Data = new u8[size];
    std::memcpy(res.Data, data, size);

    res.Width = texWidth;
    res.Height = texHeight;
    res.IsHDR = isHDR;
    res.Bits = texChannels * sizeOfChannel;

    stbi_image_free(data);
    return res;
}
} // namespace Neptus

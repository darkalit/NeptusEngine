#pragma once

#include "Core/Base.hpp"
#include "Graphics/RHI/Shader.hpp"
#include "Graphics/RHI/Texture.hpp"
#include "Graphics/Model.hpp"

#include <string>
#include <map>
#include <vector>

namespace Neptus {
class NP_API ResourceManager {
public:
    SharedPtr<Graphics::Shader> AddShader(const std::string& filepath);
    SharedPtr<Graphics::Shader> GetShader(const std::string& name);

    SharedPtr<Graphics::Texture2D>
    AddTexture2D(const std::string& filepath,
                 Graphics::TextureProps props = Graphics::TextureProps(),
                 Graphics::TextureLoadOptions loadOptions =
                     Graphics::TextureLoadOptions());
    SharedPtr<Graphics::Texture2D> GetTexture2D(const std::string& name);

    SharedPtr<Graphics::Model> AddModel(const std::string& filepath);
    SharedPtr<Graphics::Model> GetModel(const std::string& name);

    [[nodiscard]] std::vector<SharedPtr<Graphics::Shader>> GetShadersList();
    [[nodiscard]] std::vector<SharedPtr<Graphics::Texture2D>> GetTextures2DList();
    [[nodiscard]] std::vector<SharedPtr<Graphics::Model>> GetModelsList();

private:
    std::map<std::string, SharedPtr<Graphics::Shader>> m_Shaders;
    std::map<std::string, SharedPtr<Graphics::Texture2D>> m_Textures2D;
    std::map<std::string, SharedPtr<Graphics::Model>> m_Models;
};
} // namespace Neptus
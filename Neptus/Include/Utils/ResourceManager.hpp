#pragma once

#include "Core/Base.hpp"
#include "Graphics/RHI/Shader.hpp"
#include "Graphics/RHI/Texture.hpp"
#include "Graphics/Model.hpp"

#include <string>
#include <map>
#include <vector>

namespace Neptus {
class ResourceManager {
public:
    Graphics::Shader& AddShader(const std::string& filepath);
    Graphics::Shader& GetShader(const std::string& name);

    Graphics::Texture2D&
    AddTexture2D(const std::string& filepath,
                 Graphics::TextureProps props = Graphics::TextureProps(),
                 Graphics::TextureLoadOptions loadOptions =
                     Graphics::TextureLoadOptions());
    Graphics::Texture2D& GetTexture2D(const std::string& name);

    Graphics::Model& AddModel(const std::string& filepath);
    Graphics::Model& GetModel(const std::string& name);

    [[nodiscard]] std::vector<Graphics::Shader&> GetShadersList();
    [[nodiscard]] std::vector<Graphics::Texture2D&> GetTextures2DList();
    [[nodiscard]] std::vector<Graphics::Model&> GetModelsList();

private:
    std::map<std::string, Graphics::Shader> m_Shaders {};
    std::map<std::string, Graphics::Texture2D> m_Textures2D {};
    std::map<std::string, Graphics::Model> m_Models {};
};
} // namespace Neptus
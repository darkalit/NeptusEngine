#include "Utils/ResourceManager.hpp"

namespace Neptus {
Graphics::Shader& ResourceManager::AddShader(const std::string& filepath) {
    auto shader = Graphics::Shader(filepath);
    m_Shaders.emplace(filepath, std::move(shader));

    return m_Shaders[filepath];
}

Graphics::Shader& ResourceManager::GetShader(const std::string& name) {
    return m_Shaders.at(name);
}

Graphics::Texture2D&
ResourceManager::AddTexture2D(const std::string& filepath,
                              Graphics::TextureProps props,
                              Graphics::TextureLoadOptions loadOptions) {
    if (auto pair = m_Textures2D.find(filepath); pair != m_Textures2D.end()) {
        return pair->second;
    }

    auto texture2d = Graphics::Texture2D(filepath, props, loadOptions);
    m_Textures2D.emplace(filepath, std::move(texture2d));

    return m_Textures2D[filepath];
}

Graphics::Texture2D& ResourceManager::GetTexture2D(const std::string& name) {
    return m_Textures2D.at(name);
}

Graphics::Model& ResourceManager::AddModel(const std::string& filepath) {
    auto model = Graphics::Model(*this, filepath);
    m_Models.emplace(filepath, std::move(model));

    return m_Models[filepath];
}

Graphics::Model& ResourceManager::GetModel(const std::string& name) {
    return m_Models.at(name);
}

// std::vector<Graphics::Shader&> ResourceManager::GetShadersList() {
//     std::vector<Graphics::Shader&> shaders;
//     shaders.reserve(m_Shaders.size());
//
//     for (auto& shader : m_Shaders) {
//         shaders.push_back(shader.second);
//     }
//
//     return shaders;
// }
//
// std::vector<Graphics::Texture2D&> ResourceManager::GetTextures2DList() {
//     std::vector<Graphics::Texture2D&> textures;
//     textures.reserve(m_Textures2D.size());
//
//     for (auto& texture : m_Textures2D) {
//         textures.push_back(texture.second);
//     }
//
//     return textures;
// }
//
// std::vector<Graphics::Model&> ResourceManager::GetModelsList() {
//     std::vector<Graphics::Model&> models;
//     models.reserve(m_Models.size());
//
//     for (auto& model : m_Models) {
//         models.push_back(model.second);
//     }
//
//     return models;
// }
} // namespace Neptus
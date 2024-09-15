#pragma once

#include "Core/API.hpp"
#include "Core/Asset.hpp"
#include "Core/Base.hpp"

#include "Graphics/RHI/IndexBuffer.hpp"
#include "Graphics/RHI/VertexBuffer.hpp"
#include "Graphics/RHI/VertexArrayBuffer.hpp"
#include "Graphics/RHI/Texture.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Neptus {
class ResourceManager;

namespace Graphics {
struct NP_API Vertex {
    glm::vec3 Position = {};
    glm::vec3 Normal = {};
    glm::vec2 TexCoords = {};
    glm::vec4 Colors = {};

    bool operator==(const Vertex& other) const;
};

class NP_API Mesh {
public:
    Mesh(const std::vector<u32>& indices, const std::vector<Vertex>& vertices);
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&& other) noexcept;

    std::string Name = {};
    std::pair<std::string, Texture*> Texture = {{}, nullptr};
    VertexArrayBuffer VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;
};

enum class PrimitiveType {
    None,
    Cube,
};

class NP_API Model : public Asset {
    ASSET(Model)
public:
    Model() = default;
    Model(ResourceManager& resourceManager);
    Model(ResourceManager& resourceManager, const std::string& filepath);
    Model(ResourceManager& resourceManager, PrimitiveType primitiveType);
    Model(Model&& other) noexcept;

    Model& operator=(Model&& other) noexcept;

    void Load(ResourceManager& resourceManager, const std::string& filepath);

    [[nodiscard]] const std::vector<Mesh>& GetMeshes() const;
    void AddMesh(Mesh&& mesh);

private:
    std::vector<Mesh> m_Meshes = {};
};
} // namespace Graphics
} // namespace Neptus
#include "Graphics/Model.hpp"

#include "Graphics/RHI/BufferLayout.hpp"
#include "Graphics/RHI/VertexArrayBuffer.hpp"
#include "Utils/ResourceManager.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <functional>
#include <filesystem>
#include <iostream>
#include <unordered_map>

namespace std {
template <>
struct hash<Neptus::Graphics::Vertex> {
    size_t operator()(const Neptus::Graphics::Vertex& vertex) const noexcept {
        const size_t h1 = std::hash<glm::vec3>{}(vertex.Position);
        const size_t h2 = std::hash<glm::vec3>{}(vertex.Normal);
        const size_t h3 = std::hash<glm::vec2>{}(vertex.TexCoords);
        const size_t h4 = std::hash<glm::vec4>{}(vertex.Colors);

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};
} // namespace std

namespace Neptus {
namespace Graphics {
bool Vertex::operator==(const Vertex& other) const {
    return Position == other.Position && Normal == other.Normal &&
           TexCoords == other.TexCoords && Colors == other.Colors;
}

Mesh::Mesh(const std::vector<u32>& indices,
           const std::vector<Vertex>& vertices) {
    VBO = VertexBuffer(vertices.data(), static_cast<u32>(vertices.size()) * sizeof(Vertex), BufferUsage::STATIC);
    EBO = IndexBuffer(indices.data(), static_cast<u32>(indices.size()), BufferUsage::STATIC);

    BufferLayout layout;
    layout.Push<f32>(3);
    layout.Push<f32>(3);
    layout.Push<f32>(2);
    layout.Push<f32>(4);

    VAO = VertexArrayBuffer(VBO, layout);

    VAO.Bind();
    EBO.Bind();
}

Mesh::Mesh(Mesh&& other) noexcept
    : Name(std::move(other.Name))
    , Texture({std::move(other.Texture.first), other.Texture.second})
    , VAO(std::move(other.VAO))
    , VBO(std::move(other.VBO))
    , EBO(std::move(other.EBO)) {}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        Name = std::move(other.Name);
        Texture = {std::move(other.Texture.first), other.Texture.second};

        VAO = std::move(other.VAO);
        VBO = std::move(other.VBO);
        EBO = std::move(other.EBO);
    }

    return *this;
}

Model::Model(ResourceManager& resourceManager) {}

Model::Model(ResourceManager& resourceManager,
             const std::string& filepath) {
    Load(resourceManager, filepath);
}

Model::Model(ResourceManager& resourceManager,
             PrimitiveType primitiveType) {}

Model::Model(Model&& other) noexcept
    : m_Meshes(std::move(other.m_Meshes)) {
    m_Id = std::move(other.m_Id);
    m_Filepath = std::move(other.m_Filepath);
    m_Status = other.m_Status;
    other.m_Status = AssetFlag::INVALID;
}

Model& Model::operator=(Model&& other) noexcept {
    if (this != &other) {
        m_Meshes = std::move(other.m_Meshes);
        m_Id = std::move(other.m_Id);
        m_Filepath = std::move(other.m_Filepath);
        m_Status = other.m_Status;
        other.m_Status = AssetFlag::INVALID;
    }

    return *this;
}

void Model::Load(ResourceManager& resourceManager, const std::string& filepath) {
    std::filesystem::path path = filepath;

    if (!exists(path)) {
        std::cout << "ERROR::GRAPHICS::MODEL::PATH_DO_NOT_EXISTS\n";
        return;
    }

    if (path.extension() != ".obj") {
        std::cout << "ERROR::GRAPHICS::MODEL::WRONG_FILE_FORMAT\n.obj extension supported";
        return;
    }

    tinyobj::ObjReaderConfig readerConfig;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filepath, readerConfig)) {
        if (!reader.Error().empty()) {
            std::cout << "ERROR::GRAPHICS::MODEL::PARSE_ERROR\n" << reader.Error() << '\n';
        }
        return;
    }

    if (!reader.Warning().empty()) {
        std::cout << "WARNING::GRAPHICS::MODEL\n" << reader.Warning() << '\n';
    }

    m_Filepath = path.string();

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    for (const auto& shape : shapes) {
        std::vector<Vertex> vertices;
        std::vector<u32> indices;
        std::unordered_map<Vertex, u32> uniqueVertices;

        i32 materialId = -1;
        size_t indexOffset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            auto fv = static_cast<size_t>(shape.mesh.num_face_vertices[f]);

            for (size_t v = 0; v < fv; ++v) {
                tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];

                Vertex vertex;

                vertex.Position.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.Position.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.Position.z = attrib.vertices[3 * idx.vertex_index + 2];

                if (idx.normal_index >= 0) {
                    vertex.Normal.x = attrib.normals[3 * idx.normal_index + 0];
                    vertex.Normal.y = attrib.normals[3 * idx.normal_index + 1];
                    vertex.Normal.z = attrib.normals[3 * idx.normal_index + 2];
                }

                if (idx.texcoord_index >= 0) {
                    vertex.TexCoords.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.TexCoords.y = attrib.texcoords[2 * idx.texcoord_index + 1];
                }

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<u32>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }

            indexOffset += fv;
            materialId = shape.mesh.material_ids[f];
        }

        auto& mesh = m_Meshes.emplace_back(indices, vertices);
        mesh.Name = shape.name;

        if (materialId >= 0) {
            const auto& material = materials.at(materialId);

            if (!material.diffuse_texname.empty()) {
                TextureLoadOptions options = {};
                options.FlipY = true;
                std::string textureFilepath =
                    (path.parent_path() / material.diffuse_texname).string();
                auto texture2d = resourceManager.AddTexture2D(textureFilepath, {}, options);
                mesh.Texture = std::make_pair("textureDiffuse", texture2d);
            }
        }
    }
}

const std::vector<Mesh>& Model::GetMeshes() const {
    return m_Meshes;
}

void Model::AddMesh(Mesh&& mesh) {
    m_Meshes.push_back(std::move(mesh));
}
} // namespace Graphics
} // namespace Neptus
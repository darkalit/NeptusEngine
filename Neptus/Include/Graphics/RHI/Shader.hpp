#pragma once

#include "Core/API.hpp"
#include "Core/Asset.hpp"
#include "Core/Base.hpp"

#include <glm/glm.hpp>

#include <map>
#include <string>
#include <vector>

namespace Neptus {
namespace Graphics {
enum class ShaderType : u16 {
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE,
    UNKNOWN,
};

class NP_API Shader : public Asset {
    ASSET(Shader)
public:
    Shader() = default;
    Shader(const std::string& filepath);
    Shader(Shader&& other) noexcept;
    ~Shader();

    Shader& operator=(Shader&& other) noexcept;

    static ShaderType ShaderTypeFromString(const std::string& type);
    static std::map<ShaderType, std::string>
    PreProcess(std::string_view source);

    void Bind();
    void Unbind();

    void SetUniform1f(const std::string& name, f32 value);
    void SetUniform1fv(const std::string& name, f32* value, i32 count);
    void SetUniform1i(const std::string& name, i32 value);
    void SetUniform1ui(const std::string& name, u32 value);
    void SetUniform1iv(const std::string& name, i32* value, i32 count);
    void SetUniform1uiv(const std::string& name, u32* value, i32 count);
    void SetUniform2f(const std::string& name, const glm::vec2& vector);
    void SetUniform3f(const std::string& name, const glm::vec3& vector);
    void SetUniform4f(const std::string& name, const glm::vec4& vector);
    void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    void Release();

    union {
        u32 m_Handle;
    };
    std::vector<ShaderType> m_ShaderTypes = {};
};
} // namespace Graphics
} // namespace Neptus

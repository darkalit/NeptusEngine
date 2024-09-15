#include "Graphics/RHI/Shader.hpp"

#include "Core/OS/Filesystem.hpp"
#include "Utils/StringProcessing.hpp"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Neptus {
namespace Graphics {
GLenum TypeToGl(ShaderType type) {
    switch (type) {
    case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    case ShaderType::GEOMETRY:
        return GL_GEOMETRY_SHADER;
    case ShaderType::COMPUTE:
        return GL_COMPUTE_SHADER;
    default:
        return GL_VERTEX_SHADER;
    }
}

std::string TypeToString(ShaderType type) {
    switch (type) {
    case ShaderType::VERTEX:
        return "GL_VERTEX_SHADER";
    case ShaderType::FRAGMENT:
        return "GL_FRAGMENT_SHADER";
    case ShaderType::GEOMETRY:
        return "GL_GEOMETRY_SHADER";
    case ShaderType::COMPUTE:
        return "GL_COMPUTE_SHADER";
    case ShaderType::UNKNOWN:
        return "UNKNOWN_SHADER";
    }
    return "N/A";
}

u32 CompileShader(ShaderType type, std::string_view source) {
    const char* cstr = source.data();

    u32 shader = glCreateShader(TypeToGl(type));
    glShaderSource(shader, 1, &cstr, NULL);
    glCompileShader(shader);

    i32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        i32 length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> infoLog(length);
        glGetShaderInfoLog(shader, length, &length, infoLog.data());

        glDeleteShader(shader);

        std::string message;
        message += "ERROR::GRAPHICS::SHADER::" + TypeToString(type) +
                   "::COMPILATION_FAILED\n";
        message += infoLog.data();
        std::cout << message << '\n';

        return 0;
    }

    return shader;
}

u32 Compile(const std::map<ShaderType, std::string>& sources) {
    u32 program = glCreateProgram();
    std::vector<u32> shaders(sources.size());

    for (auto& [type, source] : sources) {
        shaders.push_back(CompileShader(type, source));
    }
    for (auto shader : shaders) {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);

    i32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        i32 length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> infoLog(length);
        glGetProgramInfoLog(program, length, &length, infoLog.data());

        std::string message;
        message += "ERROR::GRAPHICS::SHADER::PROGRAM::LINK_FAILED\n";
        message += infoLog.data();
        std::cout << message << '\n';

        return 0;
    }

    glValidateProgram(program);

    for (auto shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    return program;
}

Shader::Shader(const std::string& filepath) {
    const std::string source = Filesystem::ReadTextFile(filepath);
    const auto preProcessedSources = PreProcess(source);
    m_Handle = Compile(preProcessedSources);
}

Shader::Shader(Shader&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_ShaderTypes(std::move(other.m_ShaderTypes)) {
    other.m_Handle = 0;
    m_Id = std::move(other.m_Id);
    m_Status = other.m_Status;
    other.m_Status = AssetFlag::INVALID;
}

Shader::~Shader() {
    Release();
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        Release();
        std::swap(m_Handle, other.m_Handle);
        m_ShaderTypes = std::move(other.m_ShaderTypes);
        m_Id = std::move(other.m_Id);
        m_Status = other.m_Status;
        other.m_Status = AssetFlag::INVALID;
    }

    return *this;
}

ShaderType Shader::ShaderTypeFromString(const std::string& type) {
    if (type == "vertex") {
        return ShaderType::VERTEX;
    }
    if (type == "fragment") {
        return ShaderType::FRAGMENT;
    }

    return ShaderType::UNKNOWN;
}

std::map<ShaderType, std::string> Shader::PreProcess(std::string_view source) {
    std::map<ShaderType, std::string> shaderSources;
    const std::string token = "#shader";

    // TODO: Create version string based on used opengl version
    const std::string version = "#version 450 core\n";

    size_t pos = source.find(token);
    while (pos != std::string_view::npos) {
        const size_t eol = source.find_first_of("\r\n", pos);
        const size_t nextLine = source.find_first_not_of("\r\n", eol);

        const size_t shaderTypePos = pos + token.size() + 1;
        auto shaderType = static_cast<std::string>(
            source.substr(shaderTypePos, eol - shaderTypePos));
        shaderType = trim(shaderType);

        pos = source.find(token, nextLine);
        shaderSources[ShaderTypeFromString(shaderType)] =
            version + static_cast<std::string>(source.substr(
                          nextLine, pos - (nextLine == std::string_view::npos
                                               ? source.size() - 1
                                               : nextLine)));
    }

    return shaderSources;
}

void Shader::Bind() {
    glUseProgram(m_Handle);
}

void Shader::Unbind() {
    glUseProgram(0);
}

i32 GetUniformLocation(u32 handle, const std::string& name) {
    return glGetUniformLocation(handle, name.c_str());
}

void Shader::SetUniform1f(const std::string& name, f32 value) {
    glUniform1f(GetUniformLocation(m_Handle, name), value);
}

void Shader::SetUniform1fv(const std::string& name, f32* value, i32 count) {
    glUniform1fv(GetUniformLocation(m_Handle, name), count, value);
}

void Shader::SetUniform1i(const std::string& name, i32 value) {
    glUniform1i(GetUniformLocation(m_Handle, name), value);
}

void Shader::SetUniform1ui(const std::string& name, u32 value) {
    glUniform1ui(GetUniformLocation(m_Handle, name), value);
}

void Shader::SetUniform1iv(const std::string& name, i32* value, i32 count) {
    glUniform1iv(GetUniformLocation(m_Handle, name), count, value);
}

void Shader::SetUniform1uiv(const std::string& name, u32* value, i32 count) {
    glUniform1uiv(GetUniformLocation(m_Handle, name), count, value);
}

void Shader::SetUniform2f(const std::string& name, const glm::vec2& vector) {
    glUniform2f(GetUniformLocation(m_Handle, name), vector.x, vector.y);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& vector) {
    glUniform3f(GetUniformLocation(m_Handle, name), vector.x, vector.y,
                vector.z);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& vector) {
    glUniform4f(GetUniformLocation(m_Handle, name), vector.x, vector.y,
                vector.z, vector.w);
}

void Shader::SetUniformMat3(const std::string& name, const glm::mat3& matrix) {
    glUniformMatrix3fv(GetUniformLocation(m_Handle, name), 1, false,
                       glm::value_ptr(matrix));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(m_Handle, name), 1, false,
                       glm::value_ptr(matrix));
}

void Shader::Release() {
    glDeleteProgram(m_Handle);
    m_Handle = 0;
}
} // namespace Graphics
} // namespace Neptus

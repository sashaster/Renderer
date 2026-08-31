#include <glad/gl.h>
#include <fstream>

#include "Core/Renderer/Shader.hpp"
#include "Core/Config.hpp"
#include "Core/ContentLoader.hpp"

namespace Core {

    Shader::Shader(const std::string_view shaderName): m_Name(shaderName) {
        const auto sources = Parse(ContentLoader::GetShaderPath(shaderName));
        Link(sources);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ID);
        LOG_TRACE("Deleted shader {0}{1}", m_Name, Config::ShaderExtension);
    }

    void Shader::Bind() const {
        glUseProgram(m_ID);
    }

    void Shader::Link(const std::unordered_map<ShaderType, std::string>& sources){
        LOG_TRACE("Linking shader {0}{1}", m_Name, Config::ShaderExtension);
        m_ID = glCreateProgram();
        std::vector<std::uint32_t> shaderIDs;
        for (const auto& [type, source] : sources) {
            const auto shader = Compile(source, type);
            glAttachShader(m_ID, shader);
            shaderIDs.push_back(shader);
        }
        glLinkProgram(m_ID);
        for (const auto id : shaderIDs) {
            glDeleteShader(id);
        }
        Validate(m_ID, ShaderType::None);
    }

    std::uint32_t Shader::Compile(const std::string_view source, const ShaderType type) const {
        LOG_TRACE("Compiling {0} shader from {1}{2}", ShaderTypeName(type), m_Name, Config::ShaderExtension);
        const auto shader = glCreateShader(ToGLShaderType(type));
        const auto src = source.data();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        Validate(shader, type);
        return shader;
    }

    void Shader::Validate(const std::uint32_t id, const ShaderType type) const {
        GLint success;
        GLint length;
        if (type != ShaderType::None) {
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                std::string message(length, '\0');
                glGetShaderInfoLog(id, length, &length, message.data());
                LOG_ERROR("Failed to compile {0} shader from {1}{2}: {3}",
                    ShaderTypeName(type),
                    m_Name,
                    Config::ShaderExtension, message);
            }
        }else {
            glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &length);
                std::string message(length, '\0');
                glGetProgramInfoLog(m_ID, length, &length, message.data());
                LOG_ERROR("Failed to link {0}{1}: {2}",
                    m_Name,
                    Config::ShaderExtension,
                    message);
            }
        }
    }

    std::unordered_map<Shader::ShaderType, std::string> Shader::Parse(const fs::path& sourcePath) {
        std::ifstream file(sourcePath);
        VERIFY(file, "Failed to open {0}", sourcePath.filename().string());
        std::stringstream ss;
        ss << file.rdbuf();
        const std::string code = ss.str();
        std::unordered_map<ShaderType, std::string> sources;
        constexpr std::string_view token = "#shader";
        auto pos = code.find(token);
        while (pos != std::string::npos) {
            auto eol = code.find_first_of('\n', pos);
            auto typeStart = pos + token.length() + 1;
            auto type = code.substr(typeStart, eol - typeStart);

            auto newLine = code.find_first_not_of('\n', eol);
            pos = code.find(token, newLine);
            if (type == "vertex") {
                sources[ShaderType::Vertex] = code.substr(newLine, pos - newLine);
            }
            else if (type == "fragment") {
                sources[ShaderType::Fragment] = code.substr(newLine, pos - newLine);
            }
            else {
                VERIFY(false,
                    "Unknown shader type in {0}: {1}",
                    sourcePath.filename().string(),
                    type);
            }
        }
        VERIFY(sources.size() == 2, "Failed to parse shader: {0}", sourcePath.filename().string());
        return sources;
    }

}

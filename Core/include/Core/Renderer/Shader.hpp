#pragma once
#include <filesystem>
#include <cstdint>
#include <unordered_map>

#include "Core/Config.hpp"


namespace Core {
    namespace fs = std::filesystem;

    class Shader final{
    public:
        explicit Shader(std::string_view shaderName);
        ~Shader();
        void Bind() const;

        DELETE_COPY_MOVE(Shader);

    private:
        enum class ShaderType {
            None,
            Vertex,
            Fragment
        };

        static constexpr std::string_view ShaderTypeName(const ShaderType type) noexcept {
            switch (type) {
                case ShaderType::Vertex: return "Vertex";
                case ShaderType::Fragment: return "Fragment";
                default: return "None";
            }
        }

        [[nodiscard]] static constexpr GLenum ToGLShaderType(const ShaderType type) noexcept {
            switch (type) {
                case ShaderType::Vertex: return GL_VERTEX_SHADER;
                case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
                default: return GL_NONE;
            }
        }

        [[nodiscard]] std::uint32_t Compile(std::string_view source, ShaderType type) const;
        [[nodiscard]] static std::unordered_map<ShaderType, std::string> Parse(const fs::path& sourcePath) ;
        void Link(const std::unordered_map<ShaderType, std::string> &sources);
        void Validate(std::uint32_t id, ShaderType type) const;


        std::uint32_t m_ID;
        std::string m_Name;
    };
}

#pragma once

#include <filesystem>

#include "Core/Config.hpp"

namespace Core {
    namespace fs = std::filesystem;

    class ContentLoader final {
    public:

        enum class ShaderType {
            None,
            Vertex,
            Fragment
        };

        static fs::path GetShaderPath(std::string_view name);
        DELETE_COPY_MOVE(ContentLoader)

    private:
        inline static fs::path s_ResourcesPath = "Resources";
    };
}
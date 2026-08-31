#include "Core/ContentLoader.hpp"

namespace Core {

    fs::path ContentLoader::GetShaderPath(const std::string_view name) {
        auto path =  s_ResourcesPath / "Shaders" / name;
        path += Config::ShaderExtension;
        return path;
    }
}
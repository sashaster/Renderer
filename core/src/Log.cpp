#include <spdlog/sinks/stdout_color_sinks-inl.h>

#include "Core/Log.hpp"

namespace Renderer {

    void Log::Init() {
        m_Logger = spdlog::stdout_color_mt("RENDERER");
        m_Logger->set_level(spdlog::level::debug);
        m_Logger->set_pattern("%^%Y-%m-%d %T [%l] %n: %v%$");
    }
}


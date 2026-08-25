#include <spdlog/sinks/stdout_color_sinks-inl.h>

#include "Core/Log.hpp"
#include "Core/Config.hpp"

namespace Renderer {

    void Log::Init() {
        m_Logger = spdlog::stdout_color_mt("RENDERER");
        m_Logger->set_level(Config::LogLevel);
        m_Logger->set_pattern("%^%Y-%m-%d %T [%l] %n: %v%$");
        LOG_DEBUG("Logger initialized!");
    }
}


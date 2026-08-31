#include <spdlog/sinks/stdout_color_sinks-inl.h>

#include "Core/Log.hpp"
#include "Core/Config.hpp"

namespace Core {

    void Log::Init() {
        s_Logger = spdlog::stdout_color_mt("RENDERER");
        s_Logger->set_level(Config::LogLevel);
        s_Logger->set_pattern("%^%Y-%m-%d %T [%l] %n: %v%$");
        LOG_DEBUG("Logger initialized!");
    }
}


#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Renderer {

    class Log {
    public:
        Log() = delete;
        static void Init();
        [[nodiscard]] static std::shared_ptr<spdlog::logger>& GetLogger() noexcept {
            return s_Logger;
        }
    private:
        static inline std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#define LOG_TRACE(...) Renderer::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Renderer::Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Renderer::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Renderer::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Renderer::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) Renderer::Log::GetLogger()->critical(__VA_ARGS__)
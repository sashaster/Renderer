#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Core {

    class Log final{
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

#define LOG_TRACE(...)  Core::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)  Core::Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)   Core::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)   Core::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  Core::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)  Core::Log::GetLogger()->critical(__VA_ARGS__)
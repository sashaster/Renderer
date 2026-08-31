#pragma once

#include <string_view>
#include <csignal>
#include <glad/gl.h>

#include "Core/Log.hpp"

namespace Core::Config {

    constexpr std::string_view WindowTitle = "Renderer";
    constexpr int WindowWidth = 1920;
    constexpr int WindowHeight = 1080;
    constexpr spdlog::level::level_enum LogLevel = spdlog::level::trace;
    constexpr std::string_view ShaderExtension = ".glsl";

}

#ifndef NDEBUG
    #ifdef _MSC_VER
        #define BREAKPOINT() __debugbreak()
    #elif __clang__
        #define BREAKPOINT() __builtin_debugtrap()
    #elif __GNUC__
        #define BREAKPOINT() raise(SIGTRAP)
    #else
        #error "Unsupported compiler"
    #endif
#else
    #define BREAKPOINT()
#endif


#define DELETE_COPY_MOVE(type) \
    type(const type&) = delete; \
    type& operator=(const type&) = delete; \
    type(type&&) = delete; \
    type& operator=(type&&) = delete;

#ifndef NDEBUG
    #define ASSERT(condition, ...) { if (!(condition)) { LOG_FATAL(__VA_ARGS__); BREAKPOINT(); } }
#else
    #define ASSERT(condition, ...)
#endif

#define VERIFY(condition, ...) { if (!(condition)) { LOG_FATAL(__VA_ARGS__); throw std::runtime_error("Fatal error. Check logs for more info.");} }

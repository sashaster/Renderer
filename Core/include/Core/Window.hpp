#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string_view>

#include "Core/Config.hpp"

namespace Renderer {

    class Window {
    public:
        explicit Window(std::string_view title = Config::WindowTitle,
                int width = Config::WindowWidth,
                int height = Config::WindowHeight);

        ~Window();

        [[nodiscard]] int GetWidth() const noexcept {
            return m_Data.width;
        }

        [[nodiscard]] int GetHeight() const noexcept {
            return m_Data.height;
        }

        [[nodiscard]] bool IsVsync() const noexcept {
            return m_Data.vsync;
        }

        void SetVsync(bool enabled);
        void OnUpdate() const;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

    private:
        void Init();

        struct WindowData {
            std::string title;
            int width;
            int height;
            bool vsync;
        } m_Data;

        GLFWwindow* m_Window;
    };
}
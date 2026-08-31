#pragma once

#include <GLFW/glfw3.h>
#include <string_view>

#include "Core/Config.hpp"
#include "Core/Events/Event.hpp"
#include "Core/OpenGLContext.hpp"

namespace Core {

    class Window final{
        using EventCallbackFn = std::function<void(Event&)>;
        using WindowHandle = std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* window) {
            if (window) {
                glfwDestroyWindow(window);
                window = nullptr;
                LOG_INFO("Window destroyed!");
            }
        })>;
    public:

        explicit Window(std::string_view title = Config::WindowTitle,
                int width = Config::WindowWidth,
                int height = Config::WindowHeight);

        [[nodiscard]] int GetWidth() const noexcept {
            return m_Data.width;
        }

        void SetEventCallback(const EventCallbackFn& callback) noexcept {
            m_Data.eventCallback = callback;
        }

        [[nodiscard]] int GetHeight() const noexcept {
            return m_Data.height;
        }

        [[nodiscard]] bool IsVsync() const noexcept {
            return m_Data.vsync;
        }

        [[nodiscard]] GLFWwindow* GetHandle() const noexcept {
            return m_Handle.get();
        }

        void SetVsync(bool enabled);
        void OnUpdate() const;

        DELETE_COPY_MOVE(Window)

    private:
        void Init();

        struct WindowData {
            std::string title;
            int width;
            int height;
            bool vsync;

            EventCallbackFn eventCallback;
        } m_Data;

        WindowHandle m_Handle;
        std::unique_ptr<OpenGLContext> m_Context;
    };
}

#include "Core/Window.hpp"
#include "Core/Log.hpp"
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/MouseEvent.hpp"

namespace Renderer {

    Window::Window(const std::string_view title,
        const int width,
        const int height) {
        m_Data.title = title;
        m_Data.width = width;
        m_Data.height = height;
        Init();
    }

    void Window::OnUpdate() const {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void Window::SetVsync(const bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_Data.vsync = enabled;
    }

    void Window::Init() {
        LOG_INFO("Creating window: {0} {1}x{2}", m_Data.title, m_Data.width, m_Data.height);
        OpenGLContext::SetWindowHints();
        m_Handle.reset(glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.data(), nullptr, nullptr));
        ASSERT(m_Handle, "Failed to create GLFW window!");
        m_Context = std::make_unique<OpenGLContext>(m_Handle.get());
        m_Context->Init();
        glfwSetWindowUserPointer(m_Handle.get(), &m_Data);
        SetVsync(true);

        glfwSetWindowSizeCallback(m_Handle.get(), [](GLFWwindow* window, const int width, const int height) {
            auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Handle.get(), [](GLFWwindow* window) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_Handle.get(), [](GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
            const auto &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, false);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.eventCallback(event);
                    break;
                }
                default: break;
            }
        });

        glfwSetMouseButtonCallback(m_Handle.get(), [](GLFWwindow* window, const int button, const int action, const int mods) {
            const auto &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                default: break;
            }
        });

        glfwSetScrollCallback(m_Handle.get(), [](GLFWwindow* window, const double xoffset, const double yoffset) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_Handle.get(), [](GLFWwindow* window, const double xpos, const double ypos) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
            data.eventCallback(event);
        });
    }

}

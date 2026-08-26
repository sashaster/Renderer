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
        glfwPollEvents();
        glfwSwapBuffers(m_Window.get());
    }

    void Window::SetVsync(const bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_Data.vsync = enabled;
    }

    void Window::Init() {
        LOG_INFO("Creating window: {0} {1}x{2}", m_Data.title, m_Data.width, m_Data.height);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        m_Window.reset(glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.data(), nullptr, nullptr));
        glfwMakeContextCurrent(m_Window.get());
        LOG_DEBUG("Loading GLAD...");
        ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to load GLAD!");
        LOG_DEBUG("GLAD initialized!");
        glfwSetWindowUserPointer(m_Window.get(), &m_Data);
        SetVsync(true);

        glfwSetWindowSizeCallback(m_Window.get(), [](GLFWwindow* window, const int width, const int height) {
            auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window.get(), [](GLFWwindow* window) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_Window.get(), [](GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
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

        glfwSetMouseButtonCallback(m_Window.get(), [](GLFWwindow* window, const int button, const int action, const int mods) {
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

        glfwSetScrollCallback(m_Window.get(), [](GLFWwindow* window, const double xoffset, const double yoffset) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window.get(), [](GLFWwindow* window, const double xpos, const double ypos) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
            data.eventCallback(event);
        });
    }

}

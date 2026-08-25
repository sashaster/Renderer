
#include "Core/Window.hpp"
#include "Core/Log.hpp"

namespace Renderer {

    static bool s_GLFWInit = false;

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
        glfwSwapBuffers(m_Window);
    }

    void Window::SetVsync(const bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_Data.vsync = enabled;
    }

    void Window::Init() {
        LOG_INFO("Creating window: {0} {1}x{2}", m_Data.title, m_Data.width, m_Data.height);
        if (!s_GLFWInit) {
            LOG_DEBUG("Initializing GLFW...");
            const int status = glfwInit();
            ASSERT(status, "Failed to initialize GLFW!");
            if (!status) {
                throw std::runtime_error("Failed to initialize GLFW!");
            }
            s_GLFWInit = true;
            LOG_DEBUG("GLFW initialized!");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.data(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        LOG_DEBUG("Loading GLAD...");
        const int status = gladLoadGL(glfwGetProcAddress);
        ASSERT(status, "Failed to load GLAD!");
        if (!status) {
            throw std::runtime_error("Failed to initialize GLAD!");
        }
        LOG_DEBUG("GLAD initialized!");
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVsync(true);

        glfwSetErrorCallback([](int error, const char* description) {
            LOG_ERROR("GLFW error ({0}): {1}", error, description);
        });
    }

    Window::~Window() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            LOG_INFO("Window destroyed!");
        }

    }

}
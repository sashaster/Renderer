#include "Core/Application.hpp"

namespace Renderer {

    Application::Application() {
        LOG_INFO("Application started");
        m_Window = std::make_unique<Window>();
        m_Window->SetEventCallback([this](Event& event) {
            OnEvent(event);
        });
    }

    Application::GLFWContext::GLFWContext() {
        glfwSetErrorCallback([](int error, const char* description) {
            LOG_ERROR("GLFW error ({0}): {1}", error, description);
        });
        LOG_DEBUG("Initializing GLFW...");
        ASSERT(glfwInit(), "Failed to initialize GLFW!");
        LOG_DEBUG("GLFW initialized!");
    }

    Application::GLFWContext::~GLFWContext() {
        glfwTerminate();
        LOG_INFO("Application closed");
    }


    void Application::Run() {
        while (m_Running) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event) {
        m_Running = false;
        return true;
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            return OnWindowClose(e);
        });
        LOG_TRACE("{0}", event.ToString());
    }
}
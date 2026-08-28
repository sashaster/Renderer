#include "Core/Application.hpp"


namespace Renderer {

    Application::Application() {
        ASSERT(!s_Instance, "Application already initialized!")
        LOG_INFO("Application started");
        m_Window = std::make_unique<Window>();
        m_Window->SetEventCallback([this](Event& event) {
            OnEvent(event);
        });
        s_Instance = this;
    }

    Application::~Application() {
        LOG_INFO("Application stopped");
        s_Instance = nullptr;
    }

    Application& Application::Get() noexcept{
        return *s_Instance;
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
        LOG_DEBUG("Shutting down GLFW");
    }

    void Application::Run() {
        while (m_Running) {
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
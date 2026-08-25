#include "Core/Application.hpp"

namespace Renderer {

    Application::Application() {
        Log::Init();
        LOG_INFO("Application started");
        m_Window = std::make_unique<Window>();
    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();
        }
    }

    Application::~Application() {
        glfwTerminate();
        LOG_INFO("Application closed");
    }
}
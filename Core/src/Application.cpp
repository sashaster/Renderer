#include "Core/Application.hpp"

#include "Core/Events/MouseEvent.hpp"
#include "Core/Renderer/Shader.hpp"


namespace Core {

    Application::Application() {
        ASSERT(!s_Instance, "Application already initialized!")
        LOG_INFO("Application started");
        m_Window = std::make_unique<Window>();
        m_Window->SetEventCallback([this](Event& event) {
            OnEvent(event);
        });
        s_Instance = this;
    }

    Application& Application::Get() noexcept{
        return *s_Instance;
    }

    Application::GLFWContext::GLFWContext() {
        glfwSetErrorCallback([](int error, const char* description) {
            LOG_ERROR("GLFW error ({0}): {1}", error, description);
        });
        LOG_DEBUG("Initializing GLFW...");
        VERIFY(glfwInit(), "Failed to initialize GLFW!");
        LOG_DEBUG("GLFW initialized!");
    }

    Application::GLFWContext::~GLFWContext() {
        glfwTerminate();
        LOG_DEBUG("Shutting down GLFW");
    }

    void Application::Run() {
        constexpr std::array vertices = {
            -0.5f, 0.0f, 0.0f,
             0.0f, 0.5f, 0.0f,
             0.5f, 0.0f, 0.0f
        };

        constexpr std::array<std::uint32_t, 3> indices = {
            0, 1, 2
        };
        std::uint32_t VBO, VAO, IBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        const Shader shader("Basic");

        while (m_Running) {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.Bind();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event) {
        m_Running = false;
        LOG_INFO("Stopping application...");
        return true;
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            return OnWindowClose(e);
        });
        if (event.GetType() != MouseMovedEvent::GetEventType()) {
            LOG_TRACE("{0}", event.ToString());
        }
    }
}
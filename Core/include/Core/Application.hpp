#pragma once
#include <memory>

#include "Core/Window.hpp"
#include "Core/Events/ApplicationEvent.hpp"


namespace Renderer {

    class Application {
    public:
        Application();
        ~Application();

        [[nodiscard]] static Application& Get() noexcept;

        [[nodiscard]] Window& GetWindow() const noexcept {
            return *m_Window;
        }

        void Run();

        DELETE_COPY_MOVE(Application)

    private:
        void OnEvent(Event& event);
        bool OnWindowClose(WindowCloseEvent& event);

        struct GLFWContext {
            GLFWContext();
            ~GLFWContext();
            DELETE_COPY_MOVE(GLFWContext)
        } m_GLFWContext;
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
        static inline Application* s_Instance = nullptr;

    };
}

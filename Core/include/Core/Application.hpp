#pragma once
#include <memory>

#include "Window.hpp"


namespace Renderer {

    class Application {
    public:
        Application();
        ~Application();

        void Run();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

    private:
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
    };
}

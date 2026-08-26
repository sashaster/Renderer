#include "Core/Application.hpp"


int main() {
    try {
        Renderer::Log::Init();
        Renderer::Application app;
        app.Run();

    }catch (...) {
        return -1;
    }

    return 0;
}


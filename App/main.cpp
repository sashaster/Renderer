#include "Core/Application.hpp"


int main() {
    try {
        Core::Log::Init();
        Core::Application app;
        app.Run();
    }catch (...) {
        return -1;
    }
    return 0;
}


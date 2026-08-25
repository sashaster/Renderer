#include "Core/Log.hpp"


int main() {
    Renderer::Log::Init();
    LOG_TRACE("Hello, Sashaster");
    LOG_DEBUG("Hello, Sashaster");
    LOG_INFO("Hello, Sashaster");
    LOG_WARN("Hello, Sashaster");
    LOG_ERROR("Hello, Sashaster");
    LOG_FATAL("Hello, Sashaster");

    return 0;
}



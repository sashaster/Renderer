#include <GLFW/glfw3.h>
#include "Core/Events/MouseEvent.hpp"

namespace Renderer {

    std::string_view MouseButtonEvent::ButtonName(const int button) noexcept{
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: return "Left";
            case GLFW_MOUSE_BUTTON_RIGHT: return "Right";
            case GLFW_MOUSE_BUTTON_MIDDLE: return "Middle";
            default: return "Unknown";
        }
    }
}
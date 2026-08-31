#include <GLFW/glfw3.h>

#include "Core/Events/KeyEvent.hpp"

namespace Core {

    std::string_view KeyEvent::KeyName(const int key) noexcept{
        switch (key) {
            case GLFW_KEY_ESCAPE:        return "Escape";
            case GLFW_KEY_ENTER:         return "Enter";
            case GLFW_KEY_TAB:           return "Tab";
            case GLFW_KEY_BACKSPACE:     return "Backspace";
            case GLFW_KEY_SPACE:         return "Space";
            case GLFW_KEY_INSERT:        return "Insert";
            case GLFW_KEY_DELETE:        return "Delete";
            case GLFW_KEY_RIGHT:         return "Right";
            case GLFW_KEY_LEFT:          return "Left";
            case GLFW_KEY_DOWN:          return "Down";
            case GLFW_KEY_UP:            return "Up";
            case GLFW_KEY_PAGE_UP:       return "PageUp";
            case GLFW_KEY_PAGE_DOWN:     return "PageDown";
            case GLFW_KEY_HOME:          return "Home";
            case GLFW_KEY_END:           return "End";
            case GLFW_KEY_CAPS_LOCK:     return "CapsLock";
            case GLFW_KEY_SCROLL_LOCK:   return "ScrollLock";
            case GLFW_KEY_NUM_LOCK:      return "NumLock";
            case GLFW_KEY_PRINT_SCREEN:  return "PrintScreen";
            case GLFW_KEY_PAUSE:         return "Pause";
            case GLFW_KEY_KP_ENTER:      return "KeypadEnter";
            case GLFW_KEY_LEFT_SHIFT:    return "LeftShift";
            case GLFW_KEY_LEFT_CONTROL:  return "LeftCtrl";
            case GLFW_KEY_LEFT_ALT:      return "LeftAlt";
            case GLFW_KEY_LEFT_SUPER:    return "LeftSuper";
            case GLFW_KEY_RIGHT_SHIFT:   return "RightShift";
            case GLFW_KEY_RIGHT_CONTROL: return "RightCtrl";
            case GLFW_KEY_RIGHT_ALT:     return "RightAlt";
            case GLFW_KEY_RIGHT_SUPER:   return "RightSuper";
            case GLFW_KEY_MENU:          return "Menu";
            default: break;
        }
        if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F25) {
            static constexpr std::string_view kF[] = {
                "F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13",
                "F14","F15","F16","F17","F18","F19","F20","F21","F22","F23","F24","F25"
            };
            return kF[key - GLFW_KEY_F1];
        }
        const auto keyName = glfwGetKeyName(key, 0);
        return keyName ? keyName : "Unknown";
    }
}
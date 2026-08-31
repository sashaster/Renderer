#include <GLFW/glfw3.h>

#include "Core/Input.hpp"
#include "Core/Application.hpp"

namespace Core {

    bool Input::IsKeyPressed(const int keycode) {
        const auto state = glfwGetKey(Application::Get().GetWindow().GetHandle(), keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(const int button) {
        const auto state = glfwGetMouseButton(Application::Get().GetWindow().GetHandle(), button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition() {
        double xpos, ypos;
        glfwGetCursorPos(Application::Get().GetWindow().GetHandle(), &xpos, &ypos);
        return {static_cast<float>(xpos), static_cast<float>(ypos)};
    }

}

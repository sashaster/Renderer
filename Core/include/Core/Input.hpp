#pragma once
#include <utility>


namespace Core::Input {

    [[nodiscard]] bool IsKeyPressed(int keycode);
    [[nodiscard]] bool IsMouseButtonPressed(int button);
    [[nodiscard]] std::pair<float, float> GetMousePosition();

}

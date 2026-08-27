#pragma once
#include <utility>


namespace Renderer::Input {

    bool IsKeyPressed(int keycode);
    bool IsMouseButtonPressed(int button);
    std::pair<float, float> GetMousePosition();

}

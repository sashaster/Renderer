#pragma once
#include "Core/Events/Event.hpp"

namespace Core {
    class WindowResizeEvent final: public Event {
    public:
        WindowResizeEvent(const int width, const int height) : m_Width(width), m_Height(height) {
        }

        [[nodiscard]] int GetWidth() const noexcept {
            return m_Width;
        }

        [[nodiscard]] int GetHeight() const noexcept {
            return m_Height;
        }

        [[nodiscard]] std::string ToString() const override {
            return std::format("{0}: {1}x{2}", GetName(), m_Width, m_Height);
        }

        EVENT_TYPE(WindowResize)

    private:
        int m_Width, m_Height;
    };

    class WindowCloseEvent final: public Event {
    public:
        EVENT_TYPE(WindowClose)

    };
}

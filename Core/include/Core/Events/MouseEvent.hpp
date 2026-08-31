#pragma once
#include "Core/Events/Event.hpp"

namespace Core {

    class MouseMovedEvent: public Event {
    public:
        MouseMovedEvent(const float x, const float y) : m_X(x), m_Y(y) {}

        [[nodiscard]] float GetX() const noexcept {
            return m_X;
        }

        [[nodiscard]] float GetY() const noexcept {
            return m_Y;
        }

        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} ({1}, {2})", GetName(), m_X, m_Y);
        }

        EVENT_TYPE(MouseMoved)
    private:
        float m_X, m_Y;
    };

    class MouseButtonEvent: public Event {
    public:
        [[nodiscard]] int GetButton() const noexcept {
            return m_Button;
        }
        static std::string_view ButtonName(int button) noexcept;

    protected:
        explicit MouseButtonEvent(const int button) : m_Button(button) {}

        int m_Button;
    };

    class MouseButtonPressedEvent final: public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}
        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} ({1})", GetName(), ButtonName(m_Button));
        }

        EVENT_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent final: public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}
        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} ({1})", GetName(), ButtonName(m_Button));
        }

        EVENT_TYPE(MouseButtonReleased)
    };

    class MouseScrolledEvent final: public Event {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset) : m_Xoffset(xOffset), m_Yoffset(yOffset) {}

        [[nodiscard]] float GetXOffset() const noexcept {
            return m_Xoffset;
        }

        [[nodiscard]] float GetYOffset() const noexcept {
            return m_Yoffset;
        }

        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} ({1}, {2})", GetName(), m_Xoffset, m_Yoffset);
        }

        EVENT_TYPE(MouseScrolled)
    private:
        float m_Xoffset, m_Yoffset;
    };

}

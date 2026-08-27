#pragma once

#include "Core/Events/Event.hpp"


namespace Renderer {

    class KeyEvent: public Event {
    public:

        [[nodiscard]] static std::string_view KeyName(int key) noexcept;

        [[nodiscard]] int GetKey() const noexcept {
            return m_Keycode;
        }

    protected:
        explicit KeyEvent(const int keycode) : m_Keycode(keycode) {}
        int m_Keycode;
    };

    class KeyPressedEvent final: public KeyEvent {
    public:
        KeyPressedEvent(const int keycode, const bool repeated) : KeyEvent(keycode), m_Repeated(repeated) {}

        [[nodiscard]] bool IsRepeated() const noexcept {
            return m_Repeated;
        }

        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} [{1}] ({2})", GetName(), KeyName(m_Keycode), m_Repeated ? "repeated" : "not repeated");
        }

        EVENT_TYPE(KeyPressed)
    private:
        bool m_Repeated;
    };

    class KeyReleasedEvent final: public KeyEvent {
    public:
        explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}
        EVENT_TYPE(KeyReleased)
    };
}

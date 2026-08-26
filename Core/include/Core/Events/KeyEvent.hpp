#pragma once

#include "Core/Events/Event.hpp"


namespace Renderer {

    class KeyEvent: public Event {
    public:

        [[nodiscard]] static std::string_view KeyName(int key) noexcept;

        [[nodiscard]] int GetKey() const noexcept {
            return m_Key;
        }

    protected:
        explicit KeyEvent(const int key) : m_Key(key) {}
        int m_Key;
    };

    class KeyPressedEvent final: public KeyEvent {
    public:
        KeyPressedEvent(const int key, const bool repeated) : KeyEvent(key), m_Repeated(repeated) {}

        [[nodiscard]] bool IsRepeated() const noexcept {
            return m_Repeated;
        }

        [[nodiscard]] std::string ToString() const override {
            return std::format("{0} [{1}] ({2})", GetName(), KeyName(m_Key), m_Repeated ? "repeated" : "not repeated");
        }

        EVENT_TYPE(KeyPressed)
    private:
        bool m_Repeated;
    };

    class KeyReleasedEvent final: public KeyEvent {
    public:
        explicit KeyReleasedEvent(const int key) : KeyEvent(key) {}
        EVENT_TYPE(KeyReleased)
    };
}

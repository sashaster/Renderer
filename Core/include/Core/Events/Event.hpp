#pragma once
#include <string>
#include <concepts>

#include "Core/Config.hpp"


namespace Renderer {

    enum class EventType {
        None,
        WindowClose,
        WindowResize,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    class Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual EventType GetType() const noexcept = 0;
        [[nodiscard]] virtual std::string_view GetName() const noexcept = 0;
        [[nodiscard]] virtual std::string ToString() const {
            return std::string(GetName());
        }

        [[nodiscard]] bool IsHandled() const noexcept {
            return m_Handled;
        }

        DELETE_COPY_MOVE(Event)
    protected:
        Event() = default;
        bool m_Handled = false;
    };

#define EVENT_TYPE(type) \
    static EventType GetEventType() noexcept { return EventType::type; } \
    EventType GetType() const noexcept override { return GetEventType(); } \
    std::string_view GetName() const noexcept override { return #type; }

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        explicit EventDispatcher(Event &event) : m_Event(event) {}

        template<typename T>
            requires std::derived_from<T, Event>
        bool Dispatch(const EventFn<T>& callback) {
            if (m_Event.GetType() == T::GetEventType()) {
                m_Event.m_Handled = callback(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

        DELETE_COPY_MOVE(EventDispatcher)
    private:
        Event &m_Event;
    };

}

/* *****************************************************************************
PioneerEngine, a test game engine
Copyright (C) 2026  Chumakov Anton

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************** */

#ifndef PIONEER_EVENT_HPP
#define PIONEER_EVENT_HPP

#include <pioneer/Support.hpp>

namespace Pioneer
{

/**
* @brief Event type
*/
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased,
    MouseMoved,
    WheelScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryWindow      = BIT(1),
    EventCategoryInput       = BIT(2),
    EventCategoryKeyboard    = BIT(3),
    EventCategoryMouse       = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType staticType() { return EventType::##type; }           \
                               virtual EventType eventType() const override { return staticType(); } \
                               virtual const char *name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int categoryFlags() const override { return category; }

class PIONEER_API Event
{
    friend class EventDispatcher;
public:
    virtual ~Event() = default;
    virtual EventType eventType() const = 0;
    virtual const char *name() const = 0;
    virtual int categoryFlags() const = 0;
    [[nodiscard]] virtual std::string toString() const { return name(); }
    inline bool isHandled() const { return m_handled; }

    inline bool isInCategory(EventCategory category) const { return categoryFlags(); }

protected:
    bool m_handled = false;
};

class EventDispatcher
{
    template<typename T>
    using EventFcn = std::function<bool(T &)>;
public:
    EventDispatcher(Event &event) : m_event{ event } {}

    template<typename T>
    bool dispatch(EventFcn<T> func)
    {
        if (m_event.eventType() == T::staticType())
        {
            m_event.m_handled = func(*static_cast<T *>(&m_event));
            return true;
        }
        return false;
    }

private:
    Event &m_event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.toString();
}

}

#endif // !PIONEER_EVENT_HPP

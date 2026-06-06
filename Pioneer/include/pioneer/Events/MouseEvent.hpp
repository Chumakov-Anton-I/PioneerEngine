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

#ifndef PIONEER_MOUSE_EVENT_HPP
#define PIONEER_MOUSE_EVENT_HPP

#include "Event.hpp"

namespace Pioneer
{

class PIONEER_API MouseMovedEvent final : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_mouseX{ x }, m_mouseY{ y } { }

    inline float x() const { return m_mouseX; }
    inline float y() const { return m_mouseY; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_mouseX;
    float m_mouseY;
};

class PIONEER_API MouseButtonEvent : public Event
{
public:
    inline int mouseButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
    MouseButtonEvent(int button) : m_button{ button } {}

    int m_button;
};

class PIONEER_API MouseButtonPressedEvent final : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class PIONEER_API MouseButtonReleasedEvent final : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

class PIONEER_API WheelScrolledEvent final : public Event
{
public:
    WheelScrolledEvent(float xOffset, float yOffset)
        : m_xOffset{ xOffset }, m_yOffset{ yOffset } {}

    inline float xOffset() const { return m_xOffset; }
    inline float yOffset() const { return m_yOffset; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "WheelScrolledEvent: " << m_xOffset << ", " << m_yOffset;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WheelScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_xOffset;
    float m_yOffset;
};

}

#endif // !PIONEER_MOUSE_EVENT_HPP

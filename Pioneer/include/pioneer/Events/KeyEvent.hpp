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

#ifndef PIONEER_KEY_EVENT_HPP
#define PIONEER_KEY_EVENT_HPP

#include "Event.hpp"

namespace Pioneer
{

class PIONEER_API KeyEvent : public Event
{
public:
    inline int keyCode() const { return m_keycode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(int keycode) : m_keycode{ keycode } {}

    int m_keycode;
};

class PIONEER_API KeyPressedEvent final : public KeyEvent
{
public:
    KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_repeatCount{ repeatCount } { }

    inline int repeatCount() const { return m_repeatCount; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keycode << "(" << m_repeatCount << " times)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_repeatCount;
};

class PIONEER_API KeyReleasedEvent final : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class PIONEER_API KeyTypedEvent final : public KeyEvent
{
public:
    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

}

#endif // !PIONEER_KEY_EVENT_HPP

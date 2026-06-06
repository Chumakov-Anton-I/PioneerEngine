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

#ifndef PIONEER_APPLICATION_EVENT_HPP
#define PIONEER_APPLICATION_EVENT_HPP

#include "Event.hpp"

namespace Pioneer
{

class PIONEER_API WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class PIONEER_API WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width{ width }, m_height{ height } { }

    inline unsigned int width() const { return m_width; }
    inline unsigned int height() const { return m_height; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "Window resize event: " << m_width << ", " << m_height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    unsigned int m_width;
    unsigned int m_height;
};

class PIONEER_API AppTickEvent : public Event
{
public:
    AppTickEvent() {}

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class PIONEER_API AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() {}

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class PIONEER_API AppRenderEvent : public Event
{
public:
    AppRenderEvent() {}

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}

#endif // !PIONEER_APPLICATION_EVENT_HPP

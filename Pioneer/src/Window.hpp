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

struct GLFWwindow;

#include <pioneer/Support.hpp>

#include <string>

namespace Pioneer
{

class Window
{
public:
    Window(unsigned int width, unsigned int height, const std::string &title);
    ~Window();

    void onUpdate();
    unsigned int width() const { return m_data.width; }
    unsigned int height() const { return m_data.height; }

private:
    struct WindowData
    {
        unsigned int width;
        unsigned int height;
        std::string title;
        // TODO: Event cb
    };

    int init();

    GLFWwindow *m_windowID;
    WindowData m_data;

private:
    Window(const Window &) = delete;
    Window(Window &&) = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = delete;
};

}

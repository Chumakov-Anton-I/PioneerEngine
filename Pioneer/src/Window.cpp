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

#include <Window.hpp>
#include <pioneer/Logger.hpp>

#include <GLFW/glfw3.h>

namespace Pioneer
{

Window::Window(unsigned int width, unsigned int height, const std::string &title)
    : m_windowID{nullptr}, m_data{width, height, title}
{
    int rv = init();
}

Window::~Window()
{
    glfwDestroyWindow(m_windowID);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwSwapBuffers(m_windowID);
    glfwPollEvents();
}

int Window::init()
{
    glfwSetErrorCallback([](int error_code, const char *description)
        {
            PNR_FATAL("GLFW error {0}: {1}", error_code, description);
        });

    if (!glfwInit())
    {
        PNR_FATAL("Failed to initialize GLFW");
        return -1;  // TODO: create error codes (enum)
    }

    m_windowID = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    if (!m_windowID)
    {
        PNR_FATAL("Failed to create GLFW window '{0}' size {1}x{2}", m_data.title, m_data.width, m_data.height);
        glfwTerminate();
        return -2;
    }
    // TODO: glad
    glfwMakeContextCurrent(m_windowID);

    return 0;
}

}

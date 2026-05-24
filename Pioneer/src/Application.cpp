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

#include <pioneer/Application.hpp>
#include <pioneer/Logger.hpp>
#include <Window.hpp>

#include <glad/glad.h>

namespace Pioneer
{

Application::Application()
{
    PNR_CORE_INFO("[Application] Starting");
    m_windowShouldClose = false;
}

Application::~Application()
{
    PNR_CORE_INFO("[Application] Closing");
}

int Application::exec()
{
    p_window = std::make_unique<Window>(1280, 720, "Hello");    // TODO

    // connections
    p_window->signalResizeWindow.connect([&](GLFWwindow *wnd, int width, int height)
        {
            PNR_CORE_TRACE("[Resized] Size has been changed to {0}x{1}", width, height);
        });

    p_window->signalCloseWindow.connect([&](GLFWwindow *wnd)
        {
            m_windowShouldClose = true;
        });
    p_window->signalKeyPress.connect([&](GLFWwindow *wnd, int key, int mods)
        {
            PNR_CORE_TRACE("[Key pressed] Key {0}, mods {1}", key, mods);
        });
    p_window->signalKeyRelease.connect([&](GLFWwindow *wnd, int key, int mods)
        {
            PNR_CORE_TRACE("[Key released] Key {0}, mods {1}", key, mods);
        });
    p_window->signalKeyRepeat.connect([&](GLFWwindow *wnd, int key, int mods)
        {
            PNR_CORE_TRACE("[Key repeated] Key {0}, mods {1}", key, mods);
        });
    p_window->signalMouseButtonPress.connect([&](GLFWwindow *wnd, int button, int mods)
        {
            PNR_CORE_TRACE("[Mouse button pressed] Button {0}", button);
        });
    p_window->signalMouseButtonRelease.connect([&](GLFWwindow *wnd, int button, int mods)
        {
            PNR_CORE_TRACE("[Mouse button released] Button {0}", button);
        });
    p_window->signalMouseMove.connect([&](GLFWwindow *wnd, double x, double y)
        {
            //PNR_CORE_TRACE("[Mouse move] ({0}, {1})", x, y);
        });
    p_window->signalWheelScroll.connect([&](GLFWwindow *wnd, double xOffset, double yOffset)
        {
            //PNR_CORE_TRACE("[Wheel scrolled] deltaY = {0}", yOffset);
        });

    while (!m_windowShouldClose)
    {
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        p_window->onUpdate();
        onUpdate();
    }

    p_window = nullptr;
    return 0;
}

}

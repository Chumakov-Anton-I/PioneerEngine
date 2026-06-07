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

#include <pioneer/Input.hpp>
#include <pioneer/Application.hpp>
#include <pioneer/Window.hpp>

#include <GLFW/glfw3.h>

namespace Pioneer
{

Input *Input::s_instance = new Input{};

bool Input::isKeyPressedImpl(int keycode)
{
    auto *window = Application::instance().window().nativeWindow();
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMouseButtonPressedImpl(int button)
{
    auto *window = Application::instance().window().nativeWindow();
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::mousePosImpl()
{
    auto *window = Application::instance().window().nativeWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}

float Input::mousePosXImpl()
{
    auto [x, y] = mousePosImpl();
    return x;
}

float Input::mousePosYImpl()
{
    auto [x, y] = mousePosImpl();
    return y;
}

}

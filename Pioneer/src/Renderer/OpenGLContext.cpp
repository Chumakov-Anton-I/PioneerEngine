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

#include <pioneer/Renderer/OpenGLContext.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pioneer
{

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_windowHandle{windowHandle}
{
    PNR_CORE_ASSERT(m_windowHandle, "Window handle is null!");
}

void OpenGLContext::init()
{
    glfwMakeContextCurrent(m_windowHandle);
    [[maybe_unused]] int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    PNR_CORE_ASSERT(status, "Failed to initialize GLAD");
}

void OpenGLContext::swapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}

}

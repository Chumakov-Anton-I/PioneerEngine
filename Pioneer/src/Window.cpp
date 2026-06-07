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

#include <pioneer/Window.hpp>
#include <pioneer/Events/ApplicationEvent.hpp>
#include <pioneer/Events/MouseEvent.hpp>
#include <pioneer/Events/KeyEvent.hpp>
#include <pioneer/Renderer/OpenGLContext.hpp>

#include <GLFW/glfw3.h>

namespace Pioneer
{

template<typename T>
constexpr auto WINDOW_PTR(T ptr) { return static_cast<Window *>(glfwGetWindowUserPointer(ptr)); }

#define WINDOW_DATA_PTR(ptr) *static_cast<WindowData *>(glfwGetWindowUserPointer(ptr))

Window *Window::create(const WindowProps &props)
{
    return new Window(props);
}

Window::Window(const WindowProps &props)
    : m_windowID{nullptr}
{
    m_data.title = props.Title;
    m_data.width = props.Width;
    m_data.height = props.Height;
    m_errorCode = init();
}

Window::~Window()
{
    delete m_context;
    glfwDestroyWindow(m_windowID);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwPollEvents();
    m_context->swapBuffers();
}

void Window::setEventCallback(const EventCallbackFcn &callback)
{
    m_data.eventCallback = callback;
}

void Window::setVSync(bool enable)
{
    if (enable)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_data.vsync = enable;
}

bool Window::isVSync() const
{
    return m_data.vsync;
}

int Window::init()
{
    glfwSetErrorCallback([](int error_code, const char *description)
        {
            PNR_CORE_FATAL("GLFW error {0}: {1}", error_code, description);
        });

    [[maybe_unused]] int initStatus = glfwInit();
    PNR_CORE_ASSERT(initStatus, "Failed to initialize GLFW");

    m_windowID = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    PNR_CORE_ASSERT(m_windowID, "Failed to create GLFW window '{0}' size {1}x{2}", m_data.title, m_data.width, m_data.height);

    m_context = new OpenGLContext(m_windowID);
    m_context->init();
    setVSync(true);

    // event processing
    glfwSetWindowUserPointer(m_windowID, &m_data);

    glfwSetWindowSizeCallback(m_windowID,
        [](GLFWwindow *pwnd, int width, int height)
        {
            //PNR_INFO("New window size {0}x{1}", width, height);
            WindowResizeEvent event(width, height);

            auto &data = WINDOW_DATA_PTR(pwnd);
            data.width = width;
            data.height = height;
            data.eventCallback(event);
        });

    glfwSetFramebufferSizeCallback(m_windowID,
        [](GLFWwindow *pwnd, int width, int height)
        {
            (void)pwnd;
            glViewport(0, 0, width, height);
        });

    glfwSetKeyCallback(m_windowID,
        [](GLFWwindow *pwnd, int key, int scancode, int action, int mods)
        {
            (void)scancode; (void)mods;
            auto &data = WINDOW_DATA_PTR(pwnd);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    break;
                }
                default:
                    break;
            }
        });

    glfwSetCharCallback(m_windowID,
        [](GLFWwindow *pwnd, unsigned int keycode)
        {
            auto &data = WINDOW_DATA_PTR(pwnd);

            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

    glfwSetMouseButtonCallback(m_windowID,
        [](GLFWwindow *pwnd, int button, int action, int mode)
        {
            (void)mode;
            auto &data = WINDOW_DATA_PTR(pwnd);
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

    glfwSetCursorPosCallback(m_windowID,
        [](GLFWwindow *pwnd, double x, double y)
        {
            auto &data = WINDOW_DATA_PTR(pwnd);

            MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));
            data.eventCallback(event);
        });

    glfwSetScrollCallback(m_windowID,
        [](GLFWwindow *pwnd, double xOffset, double yOffset)
        {
            auto &data = WINDOW_DATA_PTR(pwnd);

            WheelScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.eventCallback(event);
        });

    glfwSetWindowCloseCallback(m_windowID,
        [](GLFWwindow *pwnd)
        {
            PNR_CORE_INFO("Window should close");
            auto &data = WINDOW_DATA_PTR(pwnd);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

    return 0;
}

}

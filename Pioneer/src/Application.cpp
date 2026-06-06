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
#include <pioneer/Layer.hpp>
#include <pioneer/Window.hpp>
#include <pioneer/Events/ApplicationEvent.hpp>
#include <pioneer/Events/KeyEvent.hpp>
#include <pioneer/Events/MouseEvent.hpp>
#include <pioneer/Input.hpp>

#include <glad/glad.h>  // TODO: move out rendering system from Application class

namespace Pioneer
{

Application *Application::s_instance = nullptr;

Application::Application()
    : m_windowShouldClose{false}
{
    PNR_CORE_INFO("[Application] Creating");
    PNR_CORE_ASSERT(!s_instance, "Application already exists!")
    s_instance = this;

    p_window = std::unique_ptr<Window>(Window::create());
    p_window->setEventCallback(PNR_BIND_EVENT_FCN(Application::onEvent));
}

Application::~Application()
{
    PNR_CORE_INFO("[Application] Closing");
}

int Application::exec()
{
    while (!m_windowShouldClose)
    {
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer *layer : m_layerStack)
            layer->onUpdate();

        auto [x, y] = Input::mousePos();
        PNR_CORE_TRACE("{0}, {1}", x, y);

        p_window->onUpdate();
    }

    p_window = nullptr;
    return 0;
}

void Application::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(PNR_BIND_EVENT_FCN(Application::onWindowClose));

    PNR_CORE_TRACE("{0}", e.toString());

    for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
    {
        (*--it)->onEvent(e);
        if (e.isHandled())
            break;
    }
}

void Application::pushLayer(Layer *layer)
{
    m_layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *overlay)
{
    m_layerStack.pushOverlay(overlay);
    overlay->onAttach();
}

bool Application::onWindowClose(WindowCloseEvent &e)
{
    m_windowShouldClose = true;
    return true;
}

}

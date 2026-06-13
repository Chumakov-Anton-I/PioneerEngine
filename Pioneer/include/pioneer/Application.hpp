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

#ifndef PIONEER_APPLICATION_HPP
#define PIONEER_APPLICATION_HPP

#include <pioneer/Support.hpp>
#include <pioneer/LayerStack.hpp>
#include <memory>

namespace Pioneer
{

class Window;
class Event;
class WindowCloseEvent;
class LayerUI;
class Shader;
class VertexBufferObject;
class IndexBufferObject;
class VertexArrayObject;

/// The Application class, an engine application object.
/// It is a singleton
class PIONEER_API Application
{
public:
    Application(int &argc, char *argv[]);
    virtual ~Application();

    virtual int exec();

    void onEvent(Event &e);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    inline Window &window() { return *p_window; }

    inline static Application &instance() { return *s_instance; }

private:
    bool onWindowClose(WindowCloseEvent &e);

    std::unique_ptr<Window> p_window;
    bool m_windowShouldClose;
    LayerStack m_layerStack;
    LayerUI *m_layerUI;

    static Application *s_instance;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<VertexArrayObject> m_VAO;

private:
    Application(const Application&) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;
};

}

#endif // !PIONEER_APPLICATION_HPP

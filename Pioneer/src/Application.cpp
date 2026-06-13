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
#include <pioneer/UI/LayerUI.hpp>
#include <pioneer/Window.hpp>
#include <pioneer/Events/ApplicationEvent.hpp>
#include <pioneer/Events/KeyEvent.hpp>
#include <pioneer/Events/MouseEvent.hpp>
#include <pioneer/Input.hpp>

#include <Renderer/Shader.hpp>
#include <Renderer/Buffer.hpp>
#include <Renderer/VertexArrayObject.hpp>

#include <Renderer/Renderer.hpp>

namespace Pioneer
{

Application *Application::s_instance = nullptr;

Application::Application(int &argc, char *argv[])
    : m_windowShouldClose{false}
{
    (void)argc; (void)argv;
    PNR_CORE_INFO("[Application] Creating");
    PNR_CORE_ASSERT(!s_instance, "Application already exists!")
    s_instance = this;

    p_window = std::unique_ptr<Window>(Window::create());
    p_window->setEventCallback(PNR_BIND_EVENT_FCN(Application::onEvent));

    m_layerUI = new LayerUI;
    pushOverlay(m_layerUI);

    m_VAO.reset(new VertexArrayObject);

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f
    };
    auto vbo = std::make_shared<VertexBufferObject>(vertices, sizeof(vertices));
    vbo->bind();
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_position" },
        { ShaderDataType::Float4, "a_color" }
    };
    vbo->setLayout(layout);
    m_VAO->addVertexBuffer(vbo);

    uint32_t indices[] = { 0, 1, 2 };
    auto ebo = std::make_shared<IndexBufferObject>(indices, sizeof(indices) / sizeof(uint32_t));
    ebo->bind();
    m_VAO->setIndexBuffer(ebo);

    std::string vshaderSrc = R"(
        #version 400 core
        layout (location = 0) in vec3 a_position;
        layout (location = 1) in vec4 a_color;
        out vec3 v_position;
        out vec4 v_color;
        void main()
        {
            v_color = a_color;
            v_position = a_position;
            gl_Position = vec4(a_position, 1.0);
        }
    )";
    std::string fshaderSrc = R"(
        #version 400 core
        layout (location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;
        void main()
        {
            color = vec4(v_position * 0.5 + 0.5, 1.0);
            color = v_color;
        }
    )";
    m_shader.reset(new Shader(vshaderSrc, fshaderSrc));
}

Application::~Application()
{
    PNR_CORE_INFO("[Application] Closing");
}

int Application::exec()
{
    while (!m_windowShouldClose)
    {
        RenderCommand::setClearColor({ 0.2f, 0.2f, 0.1f, 1.0f });
        RenderCommand::clear();

        Renderer::beginScene();

        m_shader->bind();
        Renderer::submit(m_VAO);

        Renderer::endScene();

        for (Layer *layer : m_layerStack)
            layer->onUpdate();

        m_layerUI->begin();
        for (auto *layer : m_layerStack)
            layer->onUIRender();
        m_layerUI->end();

        p_window->onUpdate();
    }

    p_window = nullptr;
    return 0;
}

void Application::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(PNR_BIND_EVENT_FCN(Application::onWindowClose));

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
}

void Application::pushOverlay(Layer *overlay)
{
    m_layerStack.pushOverlay(overlay);
}

bool Application::onWindowClose(WindowCloseEvent &)
{
    m_windowShouldClose = true;
    return true;
}

}

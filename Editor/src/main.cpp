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
#include <pioneer/Layer.hpp>
#include <pioneer/UI/LayerUI.hpp>
#include <pioneer/KeyCodes.hpp>
#include <pioneer/MouseButtonCodes.hpp>
#include <pioneer/Input.hpp>
#include <pioneer/Events/KeyEvent.hpp>

class EditorLayer final : public Pioneer::Layer
{
public:
    EditorLayer() : Layer("Example") {}
    ~EditorLayer() override {}

    void onUpdate() override
    {
        //PNR_INFO("EditorLayer::Update");
        if (Pioneer::Input::isKeyPressed(PNR_KEY_TAB))
            PNR_INFO("Tab key pressed (poll)!");
    }

    void onEvent(Pioneer::Event &event) override
    {
        if (event.eventType() == Pioneer::EventType::KeyPressed)
        {
            Pioneer::KeyPressedEvent &e = static_cast<Pioneer::KeyPressedEvent &>(event);
            if (e.keyCode() == PNR_KEY_TAB)
                PNR_TRACE("Tab key pressed (event)!");
            PNR_TRACE("{0}", e.keyCode());
        }
    }
};

class EditorApp final : public Pioneer::Application
{
public:
    EditorApp(int &argc, char *argv[]) : Application(argc, argv)
    {
        pushLayer(new EditorLayer());
        //pushOverlay(new Pioneer::LayerUI());
    }
    ~EditorApp() override {}
};

int main(int argc, char *argv[])
{
    Pioneer::Logger::init();
    PNR_CORE_WARN("Initialized LOG!");
    EditorApp app(argc, argv);
    app.exec();
    return 0;
}

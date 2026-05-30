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

#include <pioneer/UI/LayerUI.hpp>

#include <pnrpch.hpp>

#include <pioneer/Application.hpp>
//#include <pioneer/Logger.hpp>
#include <pioneer/Window.hpp>

#include <imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace Pioneer
{

LayerUI::LayerUI() : Layer{ "UI layer" }, m_time{ 0.0f }
{
}

LayerUI::~LayerUI()
{
}

void LayerUI::onAttach()
{
    IMGUI_CHECKVERSION();
    [[maybe_unused]] auto *ctx = ImGui::CreateContext();
    PNR_CORE_ASSERT(ctx, "Failed to create context");
    ImGui::StyleColorsLight();  // optional

    auto &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    [[maybe_unused]] auto initialized = ImGui_ImplOpenGL3_Init("#version 410 core");
    PNR_CORE_ASSERT(initialized, "Failed to init OpenGL for ImGui")
}

void LayerUI::onDetach()
{
}

void LayerUI::onUpdate()
{
    auto &io = ImGui::GetIO();
    auto &app = Application::instance();
    io.DisplaySize = ImVec2(app.window().width(), app.window().height());

    float time = static_cast<float>(glfwGetTime());
    io.DeltaTime = (m_time > 0.0f) ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}

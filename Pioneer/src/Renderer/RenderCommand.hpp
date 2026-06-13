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

#ifndef PIONEER_RENDER_COMMAND_HPP
#define PIONEER_RENDER_COMMAND_HPP

#include "RendererAPI.hpp"

namespace Pioneer
{

class RendererAPI;

class RenderCommand
{
public:
    inline static void setClearColor(const glm::vec4 &color)
    {
        s_rendererAPI->setClearColor(color);
    }

    inline static void clear()
    {
        s_rendererAPI->clear();
    }

    inline static void drawIndexed(const std::shared_ptr<VertexArrayObject> &vao)
    {
        s_rendererAPI->drawIndexed(vao);
    }

private:
    static RendererAPI *s_rendererAPI;
};

}

#endif // !PIONEER_RENDER_COMMAND_HPP

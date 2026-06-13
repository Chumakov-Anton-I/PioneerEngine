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

#include "RendererAPI.hpp"
#include "Buffer.hpp"
#include "VertexArrayObject.hpp"

#include <glad/glad.h>

namespace Pioneer
{

RendererAPI::RendererAPI()
{

}

RendererAPI::~RendererAPI()
{

}

void RendererAPI::setClearColor(const glm::vec4 & color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void RendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererAPI::drawIndexed(const std::shared_ptr<VertexArrayObject> &vao)
{
    vao->bind();
    glDrawElements(GL_TRIANGLES, vao->indexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

}

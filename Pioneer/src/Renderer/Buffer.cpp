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

#include <pioneer/Renderer/Buffer.hpp>
#include <glad/glad.h>

namespace Pioneer
{

VertexBufferObject::VertexBufferObject(float *vertices, uint32_t size)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &m_bufferID);
}

void VertexBufferObject::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void VertexBufferObject::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ====== Index Buffer Object ======

IndexBufferObject::IndexBufferObject(uint32_t *indices, uint32_t count)
    : m_count{ count }
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBufferObject::~IndexBufferObject()
{
    glDeleteBuffers(1, &m_bufferID);
}

void IndexBufferObject::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void IndexBufferObject::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}

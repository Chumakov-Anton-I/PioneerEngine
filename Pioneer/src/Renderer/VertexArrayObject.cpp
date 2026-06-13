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

#include "VertexArrayObject.hpp"
#include "Buffer.hpp"

#include <glad/glad.h>

namespace Pioneer
{

static GLenum shaderDataTypeToOGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Bool:   return GL_BOOL;
    case ShaderDataType::Int:    return GL_INT;
    case ShaderDataType::Int2:   return GL_INT;
    case ShaderDataType::Int3:   return GL_INT;
    case ShaderDataType::Int4:   return GL_INT;
    case ShaderDataType::Float:  return GL_FLOAT;
    case ShaderDataType::Float2: return GL_FLOAT;
    case ShaderDataType::Float3: return GL_FLOAT;
    case ShaderDataType::Float4: return GL_FLOAT;
    case ShaderDataType::Mat3:   return GL_FLOAT;
    case ShaderDataType::Mat4:   return GL_FLOAT;
    }
    PNR_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
}

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_arrayID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(m_arrayID);
}

void VertexArrayObject::unbind() const
{
    glBindVertexArray(0);
}

void VertexArrayObject::addVertexBuffer(const std::shared_ptr<VertexBufferObject> &buffer_p)
{
    PNR_CORE_ASSERT(buffer_p->layout().elements().size(), "Vertex Buffer has no layout");

    glBindVertexArray(m_arrayID);
    buffer_p->bind();

    uint32_t index = 0;
    const auto &layout = buffer_p->layout();
    for (const auto &element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
            element.getComponentCount(),
            shaderDataTypeToOGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.stride(),
            (const void *)element.Offset);
        index++;
    }
    m_vertexBuffers.push_back(buffer_p);
}

void VertexArrayObject::setIndexBuffer(const std::shared_ptr<IndexBufferObject> &buffer_p)
{
    glBindVertexArray(m_arrayID);
    buffer_p->bind();

    m_indexBuffer = buffer_p;
}

}

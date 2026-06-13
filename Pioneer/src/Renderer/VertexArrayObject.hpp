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

#ifndef PIONEER_VERTEX_ARRAY_OBJECT_HPP
#define PIONEER_VERTEX_ARRAY_OBJECT_HPP

#include <memory>

namespace Pioneer
{

class VertexBufferObject;
class IndexBufferObject;

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind() const;
    void unbind() const;

    void addVertexBuffer(const std::shared_ptr<VertexBufferObject> &buffer_p);
    void setIndexBuffer(const std::shared_ptr<IndexBufferObject> &buffer_p);

    const std::vector<std::shared_ptr<VertexBufferObject>> &vertexBuffers() const { return m_vertexBuffers; }
    const std::shared_ptr<IndexBufferObject> indexBuffer() const { return m_indexBuffer; }

private:
    uint32_t m_arrayID;

    std::vector<std::shared_ptr<VertexBufferObject>> m_vertexBuffers;
    std::shared_ptr<IndexBufferObject> m_indexBuffer;
};

}

#endif // !PIONEER_VERTEX_ARRAY_OBJECT_HPP

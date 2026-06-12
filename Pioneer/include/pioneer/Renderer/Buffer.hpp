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

#ifndef PIONEER_BUFFER_HPP
#define PIONEER_BUFFER_HPP

namespace Pioneer
{

class VertexBufferObject
{
public:
    VertexBufferObject(float *vertices, uint32_t size);
    ~VertexBufferObject();

    void bind() const;
    void unbind() const;

private:
    uint32_t m_bufferID = 0;
};

class IndexBufferObject
{
public:
    IndexBufferObject(uint32_t *indices, uint32_t count);
    ~IndexBufferObject();

    void bind() const;
    void unbind() const;

    uint32_t count() const { return m_count; }

private:
    uint32_t m_bufferID = 0;
    uint32_t m_count;
};

}

#endif // !PIONEER_BUFFER_HPP

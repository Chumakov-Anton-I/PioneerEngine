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

enum class ShaderDataType
{
    None = 0,
    Bool,
    Int, Int2, Int3, Int4,
    Float, Float2, Float3, Float4,
    Mat3, Mat4
};

static uint32_t shaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Bool:      return 1;
    case ShaderDataType::Int:       return 4;
    case ShaderDataType::Int2:      return 4 * 2;
    case ShaderDataType::Int3:      return 4 * 3;
    case ShaderDataType::Int4:      return 4 * 4;
    case ShaderDataType::Float:     return 4;
    case ShaderDataType::Float2:    return 4 * 2;
    case ShaderDataType::Float3:    return 4 * 3;
    case ShaderDataType::Float4:    return 4 * 4;
    case ShaderDataType::Mat3:      return 4 * 9;
    case ShaderDataType::Mat4:      return 4 * 16;
    }
    PNR_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
}

struct BufferElement
{
    ShaderDataType Type;
    std::string Name;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement() : Type{ ShaderDataType::None }, Name{}, Size{ 0 }, Offset{ 0 }, Normalized{ false } {}
    BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
        : Type{ type }, Name{ name }, Size{ shaderDataTypeSize(type) }, Offset{ 0 }, Normalized{ normalized }
    {
    }

    uint32_t getComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::Bool:      return 1;
        case ShaderDataType::Int:       return 1;
        case ShaderDataType::Int2:      return 2;
        case ShaderDataType::Int3:      return 3;
        case ShaderDataType::Int4:      return 4;
        case ShaderDataType::Float:     return 1;
        case ShaderDataType::Float2:    return 2;
        case ShaderDataType::Float3:    return 3;
        case ShaderDataType::Float4:    return 4;
        case ShaderDataType::Mat3:      return 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4;
        }
        PNR_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() : m_stride(0) {}
    BufferLayout(const std::initializer_list<BufferElement> &elements);

    inline const std::vector<BufferElement> &elements() const { return m_elements; }
    inline uint32_t stride() const { return m_stride; }

    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    std::vector<BufferElement>::const_iterator end()   const { return m_elements.end(); }

private:
    std::vector<BufferElement> m_elements;
    uint32_t m_stride;

    void calculateOffsetsAndStride();
};

class VertexBufferObject
{
public:
    VertexBufferObject(float *vertices, uint32_t size);
    ~VertexBufferObject();

    void bind() const;
    void unbind() const;

    void setLayout(const BufferLayout &layout);
    const BufferLayout &layout() const { return m_layout; }

private:
    uint32_t m_bufferID = 0;
    BufferLayout m_layout;
};

class IndexBufferObject
{
public:
    IndexBufferObject(uint32_t *indices, uint32_t count);
    ~IndexBufferObject();

    void bind() const;
    void unbind() const;

    void setLayout(const BufferLayout &layout);
    const BufferLayout &layout() const { return m_layout; }

    uint32_t count() const { return m_count; }

private:
    uint32_t m_bufferID = 0;
    uint32_t m_count;
    BufferLayout m_layout;
};

}

#endif // !PIONEER_BUFFER_HPP

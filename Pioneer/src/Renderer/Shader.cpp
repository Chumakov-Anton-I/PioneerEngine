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

#include <pioneer/Renderer/Shader.hpp>
#include <glad/glad.h>

namespace Pioneer
{

Shader::Shader(const std::string &vertexSrc, std::string &fragmentSrc)
{
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);
    GLint compiledStatus = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiledStatus);
    if (compiledStatus == GL_FALSE)
    {
        GLint maxLen = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLen);

        std::vector<GLchar> infoLog(maxLen);
        glGetShaderInfoLog(vertexShader, maxLen, &maxLen, &infoLog[0]);
        glDeleteShader(vertexShader);

        PNR_CORE_ERROR("{0}", infoLog.data());
        PNR_CORE_ASSERT(false, "Vertex shader compilation failure");
        return;
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiledStatus);
    if (compiledStatus == GL_FALSE)
    {
        GLint maxLen = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLen);

        std::vector<GLchar> infoLog(maxLen);
        glGetShaderInfoLog(fragmentShader, maxLen, &maxLen, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        PNR_CORE_ERROR("{0}", infoLog.data());
        PNR_CORE_ASSERT(false, "Fragment shader compilation failed");
        return;
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);

    glLinkProgram(m_programID);

    GLint linkedStatus = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &linkedStatus);
    if (linkedStatus == GL_FALSE)
    {
        GLint maxLen = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLen);

        std::vector<GLchar> infoLog(maxLen);
        glGetProgramInfoLog(m_programID, maxLen, &maxLen, &infoLog[0]);
        glDeleteProgram(m_programID);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        PNR_CORE_ERROR("{0}", infoLog.data());
        PNR_CORE_ASSERT(false, "Shader program linking failure");
        return;
    }
    glDetachShader(m_programID, vertexShader);
    glDetachShader(m_programID, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_programID);
}

void Shader::bind() const
{
    glUseProgram(m_programID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

}

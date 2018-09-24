#include "Shader_GL.hpp"

#include <stdio.h>

#include <iostream>

Shader_GL::Shader_GL() :  m_program(0), m_vertex_shader(0), m_fragment_shader(0) {}

Shader_GL::~Shader_GL() {}

void Shader_GL::bind() const
{
    if (m_program != 0)
    {
        glUseProgram(m_program);
        for (auto property : m_vertex_properties->getVertexProperties())
        {
            glEnableVertexAttribArray(glGetAttribLocation(m_program, property.name));
            GLenum type;
            switch (property.type)
            {
                default:
                    type = GL_FLOAT;
                    break;
            }
            switch(m_vertex_properties->getLayoutType())
            {
                default:
                    break;
                case LAYOUT_TYPE::INTERLEAVED:
                    glVertexAttribPointer(glGetAttribLocation(m_program, property.name), property.count, type, property.normalised, m_vertex_properties->getStride(), (GLvoid*)(uintptr_t)property.offset);
                    break;
                case LAYOUT_TYPE::GROUPED:
                    glVertexAttribPointer(glGetAttribLocation(m_program, property.name), property.count, type, property.normalised, property.size * property.count, (GLvoid*)(uintptr_t)property.offset);
                    break;
            }
        }
    }
}

bool Shader_GL::createFromFile(const char* filepath, SHADER_TYPE type)
{
    FILE* file = fopen(filepath, "r");
    fseek(file, 0, SEEK_END);
    unsigned int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* shader_source = new char[length + 1];
    if (!shader_source)
    {
        delete[] shader_source;
        fclose(file);
        return false;
    }
    fread(shader_source, sizeof(char), length, file);
    fclose(file);
    shader_source[length] = '\0';
    //printf("%s", shader_source);

    GLuint shader_id;
    switch(type)
    {
        default:
            delete[] shader_source;
            return false;
        case SHADER_TYPE::VERTEX:
            m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            shader_id = m_vertex_shader;
            break;
        case SHADER_TYPE::RASTER:
            m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            shader_id = m_fragment_shader;
            break;
    }

    glShaderSource(shader_id, 1, &shader_source, 0);

    glCompileShader(shader_id);

    GLint compile_ok = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_ok);

    if (compile_ok == GL_FALSE)
    {
        GLint log_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

        char* log = new char[log_length];

        glGetShaderInfoLog(shader_id, log_length, NULL, log);

        printf("%s", log);
        delete[] log;

        delete[] shader_source;
        glDeleteShader(shader_id);
        return false;
    }
    delete[] shader_source;

    if (m_vertex_shader != 0 && m_fragment_shader != 0)
    {
            m_program = glCreateProgram();
            glAttachShader(m_program, m_vertex_shader);
            glAttachShader(m_program, m_fragment_shader);
            glLinkProgram(m_program);
    }


    return true;
}

void Shader_GL::unbind() const
{
    glUseProgram(0);
}

void Shader_GL::updateShaderConstants()
{
    if (m_program == 0)
        return;

    glUseProgram(m_program);
    for (auto& constant : m_shader_constants.getShaderConstants())
    {
        const char* name = constant.name;
        unsigned int location = glGetUniformLocation(m_program, constant.name);
        m_shader_constants.setStorageLocation(name, location);
        switch (constant.type)
        {
            default:
                break;
            case MAT4:
                glUniformMatrix4fv(constant.storage_location, 1, false, (float*)constant.data);
                break;
        }
    }
}

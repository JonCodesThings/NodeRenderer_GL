#include "Buffer_GL.hpp"

#include <iostream>
Buffer_GL::~Buffer_GL()
{
    if (m_data)
        release();
}

void Buffer_GL::bind() const
{
    switch (m_type)
    {
        default:
            return;
        case BUFFER_TYPE::VERTEX:
            glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
            break;
        case BUFFER_TYPE::INDEX:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
            break;
        case BUFFER_TYPE::FIXED:
            glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
            break;
    };
}

void Buffer_GL::create(void* data, unsigned int data_element_count, unsigned int data_element_size, BUFFER_TYPE type, BUFFER_USAGE usage)
{
    m_data = data;
    m_data_element_count = data_element_count;
    m_data_element_size = data_element_size;
    m_type = type;
    m_usage = usage;

    glGenBuffers(1, &m_buffer_id);

    GLenum buffer_usage;
    switch (m_usage)
    {
        case BUFFER_USAGE::STATIC:
            buffer_usage = GL_STATIC_DRAW;
            break;
        case BUFFER_USAGE::DYNAMIC:
            buffer_usage = GL_DYNAMIC_DRAW;
            break;
    }

    switch (m_type)
    {
        default:
            return;
        case BUFFER_TYPE::VERTEX:
            glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
            glBufferData(GL_ARRAY_BUFFER, data_element_size * data_element_count, data, buffer_usage);
            unbind();
            break;
        case BUFFER_TYPE::INDEX:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_element_size * data_element_count, data, buffer_usage);
            unbind();
            break;
        case BUFFER_TYPE::FIXED:
            glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
            glBufferData(GL_UNIFORM_BUFFER, data_element_size * data_element_count, data, buffer_usage);
            unbind();
            break;
    };
}

void Buffer_GL::release()
{
}

void Buffer_GL::unbind() const
{
    switch (m_type)
    {
        default:
            return;
        case BUFFER_TYPE::VERTEX:
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            break;
        case BUFFER_TYPE::INDEX:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            break;
        case BUFFER_TYPE::FIXED:
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            break;
    };
}

void Buffer_GL::update(void* data)
{
    if (m_usage != BUFFER_USAGE::DYNAMIC)
        return;

    bind();

    switch (m_type)
    {
        default:
            unbind();
            return;
        case BUFFER_TYPE::VERTEX:
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_data_element_size * m_data_element_count, data);
            break;
        case BUFFER_TYPE::INDEX:
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_data_element_size * m_data_element_count, data);
            break;
        case BUFFER_TYPE::FIXED:
            glBufferSubData(GL_UNIFORM_BUFFER, 0, m_data_element_size * m_data_element_count, data);
            break;
    }

    unbind();

    m_data = data;
}

#include "Renderer_GL.hpp"

#include <iostream>

Renderer_GL::Renderer_GL()
{
}

Renderer_GL::~Renderer_GL()
{
}

void Renderer_GL::render()
{
    if (m_vertex_buffer)
        m_vertex_buffer->bind();

    if (m_shader)
        m_shader->bind();

    if (m_index_buffer)
        m_index_buffer->bind();

    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

void Renderer_GL::render(const Model& model)
{
    model.getVertexBuffer().bind();

    if (m_shader)
        m_shader->bind();

    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
}

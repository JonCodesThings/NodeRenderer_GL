#include "Texture_GL.hpp"
#include <iostream>
Texture_GL::Texture_GL(image* const image) : m_texture_id(-1)
{
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    switch (image->format)
    {
        default:
            return;
        case RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
            break;
        case RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
            break;
    }
}

Texture_GL::~Texture_GL()
{
    release();
}

void Texture_GL::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture_GL::release()
{
    glDeleteTextures(1, &m_texture_id);
    m_texture_id = -1;
}

void Texture_GL::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

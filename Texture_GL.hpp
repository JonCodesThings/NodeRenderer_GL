#ifndef TEXTURE_GL_H
#define TEXTURE_GL_H

#include <GL/glew.h>

extern "C"
{
#include <image.h>
}

#include <Texture.hpp>

class Texture_GL : public Texture
{
    public:
        Texture_GL(image* const image);
        ~Texture_GL();
        void bind();
        void release();
        void unbind();
    protected:
    private:
        GLuint m_texture_id;
};

#endif // TEXTURE_GL_H

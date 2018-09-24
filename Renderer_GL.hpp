#ifndef RENDERER_GL_HPP
#define RENDERER_GL_HPP

#include <GL/glew.h>

#include <Renderer.hpp>

class Renderer_GL : public Renderer
{
    public:
        Renderer_GL();
        ~Renderer_GL();
        void render();
        void render(const Model& model);
    protected:

    private:

};

#endif // RENDERER_GL_HPP

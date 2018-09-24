#ifndef SHADER_GL_HPP
#define SHADER_GL_HPP

#include <GL/glew.h>

#include <Shader.hpp>

class Shader_GL : public Shader
{
    public:
        Shader_GL();
        ~Shader_GL();
        void bind() const;
        bool createFromFile(const char* filepath, SHADER_TYPE);
        void unbind() const;
    private:
        virtual void updateShaderConstants();
        GLuint m_program, m_vertex_shader, m_fragment_shader;
};

#endif // SHADER_GL_HPP

#ifndef BUFFER_GL_HPP
#define BUFFER_GL_HPP

#include <GL/glew.h>

#include <Buffer.hpp>

class Buffer_GL : public Buffer
{
    public:
        ~Buffer_GL();
        void bind() const;
        void create(void* data, unsigned int data_element_count, unsigned int data_element_size, BUFFER_TYPE type, BUFFER_USAGE usage);
        void release();
        void unbind() const;
        void update(void* data);
    protected:

    private:
        GLuint m_buffer_id;
};

#endif // BUFFER_GL_HPP

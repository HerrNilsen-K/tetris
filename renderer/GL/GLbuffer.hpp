//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLBUFFER_HPP
#define TETRIS_GLBUFFER_HPP

#include <GL/glew.h>

class GLbuffer {
public:
    GLbuffer();

    void bindBuffer() const;

    void bindEbuffer() const;

private:
    uint32_t m_buffer = 0;
    uint32_t m_elementBuffer = 0;
};

GLbuffer::GLbuffer() {
    glGenBuffers(1, &m_buffer);
    glGenBuffers(1, &m_elementBuffer);

}

void GLbuffer::bindBuffer() const {
    glBindBuffer(GL_VERTEX_ARRAY, m_buffer);
}

void GLbuffer::bindEbuffer() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

#endif //TETRIS_GLBUFFER_HPP

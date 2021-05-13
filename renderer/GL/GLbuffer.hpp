//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLBUFFER_HPP
#define TETRIS_GLBUFFER_HPP

#include <GL/glew.h>
#include <vector>

class GLbuffer {
public:
    GLbuffer();

    void bindBuffer() const;

    void bindEbuffer() const;

    //Uses floats
    void data(std::vector<float> &data, std::vector<unsigned> &indicies);

    ~GLbuffer();

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

void GLbuffer::data(std::vector<float> &data, std::vector<unsigned> &indicies) {
    bindBuffer();
    glBufferData(GL_ARRAY_BUFFER, data.size(), data.data(), GL_STATIC_DRAW);
    bindEbuffer();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size(), indicies.data(), GL_STATIC_DRAW);
}

GLbuffer::~GLbuffer() {
    glDeleteBuffers(1, &m_buffer);
    glDeleteBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif //TETRIS_GLBUFFER_HPP

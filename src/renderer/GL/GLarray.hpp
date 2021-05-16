//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLARRAY_HPP
#define TETRIS_GLARRAY_HPP

#include <GL/glew.h>

class GLarray {
public:
    GLarray();

    void bind();

    //Uses float
    void data(uint32_t start, uint32_t end, uint32_t elements, void *offset);

    void enable(uint8_t index);

    ~GLarray();

private:
    uint32_t m_array = 0;
};

GLarray::GLarray() {
    glGenVertexArrays(1, &m_array);
}

void GLarray::bind() {
    glBindVertexArray(m_array);
}

void GLarray::data(uint32_t start, uint32_t end, uint32_t elements, void *offset) {
    bind();
    glVertexAttribPointer(start, end, GL_FLOAT, false, elements * sizeof(float), offset);
}

void GLarray::enable(uint8_t index) {
    glEnableVertexAttribArray(index);
}

GLarray::~GLarray() {
    glDeleteVertexArrays(1, &m_array);
    glBindVertexArray(0);
}

#endif //TETRIS_GLARRAY_HPP

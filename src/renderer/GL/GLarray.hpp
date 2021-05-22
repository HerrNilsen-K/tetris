//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLARRAY_HPP
#define TETRIS_GLARRAY_HPP

#include <GL/glew.h>
#include <stdexcept>

class GLarray {
public:
    GLarray();

    void bind();

    //Uses float
    void data(uint32_t start, uint32_t end, uint32_t elements, void *offset);

    void enable(uint8_t index);

    GLarray &operator=(const GLarray &arr);

    GLarray &operator=(GLarray &&arr);

    ~GLarray();

private:
    uint32_t m_array = 0;
};

inline GLarray::GLarray() {
    glGenVertexArrays(1, &m_array);
}

inline void GLarray::bind() {
    glBindVertexArray(m_array);
    if (!glIsVertexArray(m_array))
        throw std::runtime_error("VAO not valid!");
}

inline void GLarray::data(uint32_t start, uint32_t end, uint32_t elements, void *offset) {
    bind();
    glVertexAttribPointer(start, end, GL_FLOAT, false, elements * sizeof(float), offset);
}

inline void GLarray::enable(uint8_t index) {
    glEnableVertexAttribArray(index);
}

inline GLarray::~GLarray() {
    if (m_array != 0)
        glDeleteVertexArrays(1, &m_array);
    glBindVertexArray(0);
}

inline GLarray &GLarray::operator=(GLarray &&arr) {
    if (this != &arr) {
        this->m_array = arr.m_array;

        arr.m_array = 0;
    }
    return *this;
}

inline GLarray &GLarray::operator=(const GLarray &arr) {
    this->m_array = arr.m_array;
    return *this;
}

#endif //TETRIS_GLARRAY_HPP

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

    uint32_t getIndicies() const;

private:
    uint32_t m_buffer = 0;
    uint32_t m_elementBuffer = 0;

    uint32_t m_indicieCount = 0;
};

inline GLbuffer::GLbuffer() {
    glGenBuffers(1, &m_buffer);
    glGenBuffers(1, &m_elementBuffer);

}

inline void GLbuffer::bindBuffer() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

inline void GLbuffer::bindEbuffer() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

inline void GLbuffer::data(std::vector<float> &data, std::vector<unsigned> &indicies) {
    bindBuffer();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    bindEbuffer();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned), indicies.data(), GL_STATIC_DRAW);
    m_indicieCount = indicies.size();
}

inline uint32_t GLbuffer::getIndicies() const {
    return m_indicieCount;
}

inline GLbuffer::~GLbuffer() {
    glDeleteBuffers(1, &m_buffer);
    glDeleteBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif //TETRIS_GLBUFFER_HPP

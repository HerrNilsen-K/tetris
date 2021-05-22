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

    GLbuffer(const GLbuffer &buf);

    GLbuffer(GLbuffer &&buf);

    void bindBuffer() const;

    void bindEbuffer() const;

    //Uses floats
    void data(std::vector<float> &data, std::vector<unsigned> &indicies);

    GLbuffer &operator=(const GLbuffer &buf);

    GLbuffer &operator=(GLbuffer &&buf);

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
    if(!glIsBuffer(m_buffer))
        throw std::runtime_error("VBO not valid!");
}

inline void GLbuffer::bindEbuffer() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    if(!glIsBuffer(m_elementBuffer))
        throw std::runtime_error("EBO not valid!");
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
    if (m_buffer != 0)
        glDeleteBuffers(1, &m_buffer);
    if (m_elementBuffer != 0)
        glDeleteBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline GLbuffer::GLbuffer(const GLbuffer &buf) {
    m_elementBuffer = buf.m_elementBuffer;
    m_buffer = buf.m_buffer;
    m_indicieCount = buf.m_indicieCount;
}

inline GLbuffer &GLbuffer::operator=(const GLbuffer &buf) {
    m_elementBuffer = buf.m_elementBuffer;
    m_buffer = buf.m_buffer;
    m_indicieCount = buf.m_indicieCount;
    return *this;
}

inline GLbuffer::GLbuffer(GLbuffer &&buf) {
    if (this == &buf) {
        m_elementBuffer = buf.m_elementBuffer;
        m_buffer = buf.m_buffer;
        m_indicieCount = buf.m_indicieCount;
    }
}

inline GLbuffer &GLbuffer::operator=(GLbuffer &&buf) {
    if (this != &buf) {
        this->m_buffer = buf.m_buffer;
        this->m_elementBuffer = buf.m_elementBuffer;
        this->m_indicieCount = buf.m_indicieCount;

        buf.m_buffer = 0;
        buf.m_elementBuffer = 0;
        buf.m_indicieCount = 0;
    }
    return *this;
}

#endif //TETRIS_GLBUFFER_HPP

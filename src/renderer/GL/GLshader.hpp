//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLSHADER_HPP
#define TETRIS_GLSHADER_HPP

#include <GL/glew.h>
#include <string_view>
#include <glm/glm.hpp>

class field;

class GLshader {
public:
    GLshader();

    GLshader(const GLshader &pro);

    std::string shader(std::string_view &vert, std::string_view &frag);

    void bind();

    void uniform(std::string &pos, glm::mat4 &m);

    void uniform(std::string &pos, float p1, float p2, float p3);

    GLshader &operator=(const GLshader &pro);

    GLshader &operator=(GLshader &&pro);

    ~GLshader();

    friend field;

private:
    uint32_t m_program = 0;
};

inline GLshader::GLshader() {
    m_program = glCreateProgram();
}

inline std::string GLshader::shader(std::string_view &vert, std::string_view &frag) {
    size_t vertex = glCreateShader(GL_VERTEX_SHADER), fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLint success = 0;

    const char *temp = vert.data();
    glShaderSource(vertex, 1, &temp, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char stackInfo[512];
        glGetShaderInfoLog(vertex, 512, nullptr, stackInfo);
        return std::string(stackInfo);
    }

    temp = frag.data();
    glShaderSource(fragment, 1, &temp, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        //Delete shader before returning
        glDeleteShader(vertex);
        char stackInfo[512];
        glGetShaderInfoLog(fragment, 512, nullptr, stackInfo);
        return std::string(stackInfo);
    }

    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char stackInfo[512];
        glGetShaderInfoLog(m_program, 512, nullptr, stackInfo);
        return std::string(stackInfo);
    }

    return std::string();
}

inline void GLshader::bind() {
    glUseProgram(m_program);
    //if (glIsProgram(m_program))
    //    throw std::runtime_error("Program is not valid!");
}

inline GLshader::~GLshader() {
    if (m_program != 0)
        glDeleteProgram(m_program);
}

inline void GLshader::uniform(std::string &pos, glm::mat4 &m) {
    bind();
    glUniformMatrix4fv(glGetUniformLocation(m_program, pos.c_str()), 1, false, &m[0][0]);
}

inline GLshader::GLshader(const GLshader &pro) {
    m_program = pro.m_program;
}

inline GLshader &GLshader::operator=(const GLshader &pro) {
    this->m_program = pro.m_program;
    return *this;
}

inline GLshader &GLshader::operator=(GLshader &&pro) {
    if (this != &pro) {
        this->m_program = pro.m_program;

        pro.m_program = 0;
    }
    return *this;
}

inline void GLshader::uniform(std::string &pos, float p1, float p2, float p3) {
    bind();
    glUniform3f(glGetUniformLocation(m_program, pos.c_str()), p1, p2, p3);
}

#endif //TETRIS_GLSHADER_HPP

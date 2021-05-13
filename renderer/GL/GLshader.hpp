//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLSHADER_HPP
#define TETRIS_GLSHADER_HPP

#include <GL/glew.h>
#include <string_view>

class GLshader {
public:
    GLshader();

    std::string shader(std::string_view &vert, std::string_view &frag);

    void bind();

    ~GLshader();

private:
    uint32_t m_program = 0;
};

GLshader::GLshader() {
    m_program = glCreateProgram();
}

std::string GLshader::shader(std::string_view &vert, std::string_view &frag) {
    size_t vertex = glCreateShader(GL_VERTEX_SHADER), fragment = glCreateShader(GL_FRAGMENT_SHADER);
    size_t success = 0;

    glShaderSource(vertex, 1, &vert.data(), nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char stackInfo[512];
        glGetShaderInfoLog(vertex, 512, nullptr, stackInfo);
        return std::string(stackInfo);
    }

    glShaderSource(fragment, 1, &fragment.data(), nullptr);
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

void GLshader::bind() {
    glUseProgram(m_program);
}

GLshader::~GLshader() {
    glDeleteProgram(uint32_t);
}

#endif //TETRIS_GLSHADER_HPP

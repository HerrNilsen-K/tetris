//
// Created by karl on 18.05.21.
//

#ifndef TETRIS_FIELD_HPP
#define TETRIS_FIELD_HPP

#include "GL/GLrenderer.hpp"
#include <stdexcept>

class field {
public:
    field();

    field(const field &f);

    field(field &&f);

    void render();

    void uniform(std::string &pos, glm::mat4 &m);

    void uniform(std::string &pos, glm::vec3 vec);

    void uniform(std::string &pos, float p1, float p2, float p3);

    field &operator=(const field &f);

    field &operator=(field &&f);

private:
    GLbuffer m_buf;
    GLarray m_arr;
    GLshader m_pro;
};

inline field genField() {
    return field();
}

inline field::field() {
    std::vector<float> vertecies{
            -1, 1, //Bottom Left
            -1, -1, //Bottom Left
            1, 1, //Top Right
            1, -1 //Bottom Right
    };
    std::vector<unsigned> indicies{
            0, 1, 2,
            1, 2, 3
    };

    std::string_view
            fragment{
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n"
    };
    std::string_view vertex{
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 aMat;\n"
            "void main()\n"
            "{\n"
            "   gl_Position =  aMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\n"
    };
    m_buf.data(vertecies, indicies);
    m_arr.data(0, 2, 2, 0);
    m_arr.enable(0);

    std::string programResult = m_pro.shader(vertex, fragment);
    if (!programResult.empty())
        throw std::runtime_error(programResult);
    glm::mat4 mat(1.f);
    std::string pos = "aMat";
    m_pro.uniform(pos, mat);
}

inline void field::render() {
    GLrenderer::render2D(m_buf, m_arr, m_pro);
}

inline void field::uniform(std::string &pos, glm::mat4 &m) {
    m_pro.uniform(pos, m);
}

inline field &field::operator=(const field &f) {
    this->m_buf = f.m_buf;
    this->m_arr = f.m_arr;
    this->m_pro = f.m_pro;
    return *this;
}

inline field::field(const field &f) {
    this->m_buf = f.m_buf;
    this->m_arr = f.m_arr;
    this->m_pro = f.m_pro;
}

inline field::field(field &&f) {
    if (this != &f) {
        this->m_buf = std::move(f.m_buf);
        this->m_arr = std::move(f.m_arr);
        this->m_pro = std::move(f.m_pro);
    }
}

inline field &field::operator=(field &&f) {
    if (this != &f) {
        this->m_buf = std::move(f.m_buf);
        this->m_arr = std::move(f.m_arr);
        this->m_pro = std::move(f.m_pro);
    }
    return *this;
}

inline void field::uniform(std::string &pos, float p1, float p2, float p3) {
    m_pro.uniform(pos, p1, p2, p3);
}

inline void field::uniform(std::string &pos, glm::vec3 vec) {
    uniform(pos, vec[0], vec[1], vec[2]);
}


#endif //TETRIS_FIELD_HPP

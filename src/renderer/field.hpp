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

    void render();

    void uniform(std::string &pos, glm::mat4 &m);

private:
    GLbuffer m_buf;
    GLarray m_arr;
    GLshader m_pro;
};

field::field() {
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
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
}

void field::render() {
    GLrenderer::render2D(m_buf, m_arr, m_pro);
}

void field::uniform(std::string &pos, glm::mat4 &m) {
    m_pro.uniform(pos, m);
}


#endif //TETRIS_FIELD_HPP

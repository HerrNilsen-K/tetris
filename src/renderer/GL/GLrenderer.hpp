//
// Created by karl on 12.05.21.
//

#ifndef TETRIS_GLRENDERER_HPP
#define TETRIS_GLRENDERER_HPP

#include "GLarray.hpp"
#include "GLshader.hpp"
#include "GLbuffer.hpp"

namespace GLrenderer {
    void render2D(GLbuffer &buff, GLarray &arr, GLshader &shad) {
        buff.bindBuffer();
        buff.bindEbuffer();
        arr.bind();
        shad.bind();
        glDrawElements(GL_TRIANGLES, buff.getIndicies(), GL_UNSIGNED_INT, 0);
    }
};

#endif //TETRIS_GLRENDERER_HPP

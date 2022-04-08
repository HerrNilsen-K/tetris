//
// Created by karl on 08.04.22.
//

#ifndef TETRIS_PIECES_HPP
#define TETRIS_PIECES_HPP

#include <glm/glm.hpp>

//Create enum of all pieces
enum class pieceType {
    BEGIN = 0,
    I,
    J,
    L,
    O,
    S,
    T,
    Z,
    END
};

//Create enum of all rotations
enum class pieceRotation {
    R0,
    R90,
    R180,
    R270
};

//Create struct of all pieces
struct tetronomio {
    pieceType type;
    pieceRotation rotation;
    glm::vec2 position;

    //Constructor
    tetronomio(pieceType type, pieceRotation rotation, glm::vec2 position) : type(type), rotation(rotation), position(position) {}

};

#endif //TETRIS_PIECES_HPP

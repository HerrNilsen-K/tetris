//
// Created by karl on 18.05.21.
//

#include <iostream>
#include "board.hpp"
#include "../constants.hpp"
#include <glm/gtc/matrix_transform.hpp>

board::board() {
    glm::mat4 ort(1.f);
    ort = glm::ortho(0.f, (float) constants::WINDOW_WIDTH, 0.f, (float) constants::WINDOW_HEIGHT);
    for (float y = 0; auto &i: m_board) {
        for (float x = 0; auto &j: i) {
            static std::string col = "color", pos = "aMat";
            j.second.uniform(col, colorMap[color::NONE]);
            glm::mat4 trans(1.f), scale(1.f);

            trans = glm::translate(trans, glm::vec3(x + constants::FIELD_SIZE, y + constants::FIELD_SIZE, 1));
            scale = glm::scale(scale, glm::vec3(constants::FIELD_SIZE, constants::FIELD_SIZE, 1));

            glm::mat4 result = ort * trans * scale;
            j.second.uniform(pos, result);

            x += 40;
        }
        y += 40;
    }
};

void board::render() {
    for (auto &i: m_board) {
        for (auto &j: i) {
            std::string col = "color";
            if (j.first.c == color::NONE) {
                continue;
            }
            j.second.uniform(col, colorMap[j.first.c]);
            j.second.render();
        }
    }
}

[[maybe_unused]] void board::setColor(size_t x, size_t y, color c) {
    std::string col("color");
    m_board[x][y].second.uniform(col, colorMap[c]);
    m_board[x][y].first = c;
}

void board::addPieceToRenderer(const tetronomio &tetronomio) {
    //TODO: Change color according to tetronomio
    auto &b = m_board
    [static_cast<size_t>(tetronomio.position.y)]
    [static_cast<size_t>(tetronomio.position.x)];

    b.first = color::RED;
    std::string col("color");
    b.second.uniform(col, colorMap[color::RED]);
    b.second.render();
    b.first = color::NONE;
}

void board::addPieceStaticly(tetronomio &tetronomio) {
    //TODO: Change color according to tetronomio

    calculatePiecePositions(tetronomio);

    m_board
    [static_cast<size_t>(tetronomio.position.y)]
    [static_cast<size_t>(tetronomio.position.x)].first = color::RED;
}

std::vector<glm::vec4> RotateMatrix(std::vector<glm::vec4> matrix) {

    std::vector<glm::vec4> ret(4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret[i][j] = matrix[4 - j - 1][i];
        }
    }

    return ret;
}

std::vector<glm::vec4> board::calculatePiecePositions(tetronomio &tetronomio) {
    std::vector<glm::vec4> positions;

    //Create switch case for each piece type and add the positions to the vector, relative to the piece position
    //TODO: Switch case is probably wrong
    switch (tetronomio.type) {
        case pieceType::I:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 2, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 3, 0, 0));
            break;
        case pieceType::J:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 2, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y + 2, 0, 0));
            break;
        case pieceType::L:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 2, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x - 1, tetronomio.position.y + 2, 0, 0));
            break;
        case pieceType::O:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y + 1, 0, 0));
            break;
        case pieceType::S:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y + 1, 0, 0));
            break;
        case pieceType::T:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 2, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y + 1, 0, 0));
            break;
        case pieceType::Z:
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x, tetronomio.position.y + 1, 0, 0));
            positions.emplace_back(glm::vec4(tetronomio.position.x + 1, tetronomio.position.y + 1, 0, 0));
            break;
        default:
            break;
    }

    int rotationInDegree;
    switch (tetronomio.rotation) {
        case pieceRotation::R0:
            rotationInDegree = 0;
            break;
        case pieceRotation::R90:
            rotationInDegree = 90;
            break;
        case pieceRotation::R180:
            rotationInDegree = 180;
            break;
        case pieceRotation::R270:
            rotationInDegree = 270;
            break;
    }

    std::vector<glm::vec4> positionsInWorld;
    positionsInWorld.reserve(positions.size());
    for (auto &position: positions) {
        positionsInWorld.emplace_back(glm::vec4(position.x, position.y, 0, 0));
    }

    //TODO: Calculate how much to rotate
    auto result = RotateMatrix(positionsInWorld);


    return result;
}

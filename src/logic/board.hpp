//
// Created by karl on 18.05.21.
//

#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP

#include <array>
#include <memory>
#include <map>
#include "../renderer/field.hpp"

enum class color {
    CYAN,
    YELLOW,
    PURPLE,
    GREEN,
    RED,
    BLUE,
    ORANGE,
    NONE
};

struct fieldColor {
    color c;

    fieldColor(color color = color::NONE) : c(color) {

    }
};

//TODO Adjust colors
static std::map<color, glm::vec3> colorMap = {
        std::make_pair(color::CYAN, glm::vec3(1, 1, 1)),
        std::make_pair(color::YELLOW, glm::vec3(1, 1, 1)),
        std::make_pair(color::PURPLE, glm::vec3(1, 1, 1)),
        std::make_pair(color::GREEN, glm::vec3(1, 1, 1)),
        std::make_pair(color::RED, glm::vec3(1, 0, 0)),
        std::make_pair(color::BLUE, glm::vec3(1, 1, 1)),
        std::make_pair(color::ORANGE, glm::vec3(1, 1, 1)),
        std::make_pair(color::NONE, glm::vec3(0, 0, 0))
};

class board {
private:
    using fieldPair = std::pair<fieldColor, field>;

public:
    board();

    void render();

    void setColor(size_t x, size_t y, color c);

    //TODO Implement add tetromino function

private:
    std::array<std::array<fieldPair , 10>, 20> m_board;
};


#endif //TETRIS_BOARD_HPP

//
// Created by karl on 18.05.21.
//

#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP

#include <array>
#include <memory>
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

class board {
private:
    using fieldPair = std::pair<fieldColor, field>;

public:
    board();

    void render();

private:
    std::array<std::array<fieldPair , 20>, 10> m_board;
};


#endif //TETRIS_BOARD_HPP

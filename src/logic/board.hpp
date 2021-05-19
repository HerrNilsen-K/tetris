//
// Created by karl on 18.05.21.
//

#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP

#include <array>
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

    fieldColor(color color) : c(color) {

    }
};

class board {
private:
    struct fieldPair : std::pair<fieldColor, field> {
        fieldPair() : std::pair<fieldColor, field>(color::NONE, field()) {}
    };

public:
    board();

private:
    std::array<std::array<fieldPair, 10>, 20> m_board {};
};


#endif //TETRIS_BOARD_HPP

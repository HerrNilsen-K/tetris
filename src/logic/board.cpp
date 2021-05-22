//
// Created by karl on 18.05.21.
//

#include <iostream>
#include "board.hpp"

board::board() {
    for (auto &i : m_board) {
        for (auto &j : i) {
            static std::string pos = "color";
            j.second.uniform(pos, colorMap[color::NONE]);
        }
    }
};

void board::render() {
    for (auto &i : m_board) {
        for (auto &j : i) {
            j.second.render();
        }
    }
}

//
// Created by karl on 18.05.21.
//

#include <iostream>
#include "board.hpp"

board::board() = default;

void board::render() {
    for (auto &i : m_board) {
        for (auto &j : i) {
            j.second.render();
        }
    }
}

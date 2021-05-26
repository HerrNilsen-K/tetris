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
    for (float y = 0; auto &i : m_board) {
        for (float x = 0; auto &j : i) {
            static std::string col = "color", pos = "aMat";
            //TODO Turn color to NONE
            //It's red for debugging
            j.second.uniform(col, colorMap[color::RED]);
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
    for (auto &i : m_board) {
        for (auto &j : i) {
            j.second.render();
        }
    }
}

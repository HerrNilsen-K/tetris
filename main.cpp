//
// Created by karl on 09.05.21.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "app.hpp"

int main() {
    /*
     * Create Window
     * initialize the board
     * start game loop
     *      spawn piece
     *      let piece drop/transform it
     *      end when game over
     */

    app game;
    game.run();
    return 0;
}
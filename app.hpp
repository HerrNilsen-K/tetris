//
// Created by karl on 11.05.21.
//

#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP

#include "events.hpp"
#include <chrono>
#include <iostream>
#include <thread>

class app {
private:
    //Main loop
    bool appLoop();

    bool init();


    events currentEvent;

public:
    bool run();
};

bool app::run() {
    if (!init())
        return false;
    return appLoop();
}

bool app::appLoop() {
    //TODO Remove this
    currentEvent = events::CHOOSE_PIECE;
    bool appIsRunning = true, appIsOk = true;

    //Delta time
    double deltaTime = 1;
    auto oldTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    while (appIsRunning) {
        oldTime = currentTime;
        currentTime = std::chrono::system_clock::now();
        deltaTime = std::chrono::duration<double, std::milli>(currentTime - oldTime).count();
        std::cout << "FPS: " << 1000 / deltaTime << std::endl;
        //Event handler
        switch (currentEvent) {
            case events::CLOSE:
                appIsRunning = false;
            case CHOOSE_PIECE:
                //selectPiece();
                break;
            case PIECE_FALLING:
                /*
                 * fall(input);
                 * checkCollision();
                 */
                break;
            default:
                appIsOk = false;
                appIsRunning = false;
                break;
        }
    }

    return appIsOk;
}

bool app::init() {
    if(!glfwInit())
        return false;
    return true;
}

#endif //TETRIS_APP_HPP

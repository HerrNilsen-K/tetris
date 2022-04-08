//
// Created by karl on 11.05.21.
//

#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP

#include "logic/events.hpp"
#include "window/window.hpp"
#include "logic/board.hpp"
#include "constants.hpp"
#include "logic/pieces.hpp"
#include "logic/randomGenerator.hpp"
#include <chrono>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

class app {
private:
    //Main loop
    bool appLoop();

    bool init();


    events currentEvent;
    window m_win;

public:
    bool run();
};

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Source: Other";
            break;
    }
    std::cout << std::endl;

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other";
            break;
    }
    std::cout << std::endl;

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification";
            break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

bool app::run() {
    if (!init())
        return false;
    if (GLenum err = glewInit(); err != GLEW_OK)
        throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(err)));
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugOutput, nullptr);
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

    board b;
    while (m_win.run()) {
        m_win.swapBuffers();
        m_win.pollEvents();
        m_win.setViewport();
        glClear(GL_COLOR_BUFFER_BIT);
        oldTime = currentTime;
        currentTime = std::chrono::system_clock::now();
        deltaTime = std::chrono::duration<double, std::milli>(currentTime - oldTime).count();
        std::cout << "FPS: " << 1000 / deltaTime << std::endl;

        tetronomio currentTetronomio(
                pieceType::I,
                pieceRotation::R0,
                glm::vec2(0, 0));



        //Event handler
        switch (currentEvent) {
            case events::CLOSE:
                appIsRunning = false;
            case CHOOSE_PIECE:
                //Choose random piece in range of piecType
                currentTetronomio.type = static_cast<pieceType>(
                        generate::random(static_cast<int>(pieceType::BEGIN),
                                         static_cast<int>(pieceType::END)));
                currentEvent = events::PIECE_FALLING;
                break;
            case PIECE_FALLING:
                /*
                 * fall(input);
                 * bool hit = hitGround();
                 * if (hit) {
                 *  currentEvent = events::CHOOSE_PIECE;
                 * }
                 */
                break;
            default:
                appIsOk = false;
                appIsRunning = false;
                break;
        }
        b.render();
    }

    return appIsOk;
}

bool app::init() {
    if (!glfwInit())
        return false;
    //TODO Make window unresizable
    windowAttributes winAtt{constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, 0, 0, "TETRIS"};
    m_win.windowAttributes(winAtt);
    m_win.createWindow();
    return true;
}

#endif //TETRIS_APP_HPP

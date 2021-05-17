//
// Created by karl on 11.05.21.
//

#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP

#include "events.hpp"
#include "window/window.hpp"
#include "renderer/GL/GLrenderer.hpp"
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
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW cannot be initialized");
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

    //Testing the renderer
    std::vector<float> vertecies{
            0, 0.5,
            0.5, -0.5,
            -0.5, -0.5
    };

    std::vector<unsigned> indicies{
            0, 1, 2
    };

    std::string_view
            fragment{
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n"
    };
    std::string_view vertex{
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 aMat;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = aMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\n"
    };

    GLbuffer vbo;
    GLarray vao;
    GLshader program;

    vbo.data(vertecies, indicies);
    vao.data(0, 2, 2, 0);
    vao.enable(0);

    std::string programResult = program.shader(vertex, fragment);
    if (!programResult.empty())
        throw std::runtime_error(programResult);

    glm::mat4 mat(1.0f);
    mat = glm::rotate(mat, glm::radians(90.f), glm::vec3(0, 0, 1));
    std::string pos = "aMat";
    program.uniform(pos, mat);

    while (m_win.run()) {
        m_win.swapBuffers();
        m_win.pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        GLrenderer::render2D(vbo, vao, program);
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
    if (!glfwInit())
        return false;
    windowAttributes winAtt{200, 400, 0, 0, "TETRIS"};
    m_win.windowAttributes(winAtt);
    m_win.createWindow();
    return true;
}

#endif //TETRIS_APP_HPP

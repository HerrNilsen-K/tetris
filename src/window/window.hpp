//
// Created by karl on 13.05.21.
//

#ifndef TETRIS_WINDOW_HPP
#define TETRIS_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <functional>

struct windowAttributes {
    uint32_t sizeX{};
    uint32_t sizeY{};

    uint32_t posX{};
    uint32_t posY{};

    std::string name;
};

class window {
private:
    struct customGLFWwindowDestroyer {
        void operator()(GLFWwindow *win) {
            glfwDestroyWindow(win);
        }
    };

    std::unique_ptr<GLFWwindow, customGLFWwindowDestroyer> m_win;
    windowAttributes m_attributes;


    void destroyWindow();

public:
    window() = default;

    void windowAttributes(windowAttributes attributes);

    void createWindow();

    void closeWindow();

    void swapBuffers();

    bool run();

    ~window();

    void pollEvents();
};

void window::createWindow() {
    m_win.reset(glfwCreateWindow(m_attributes.sizeX, m_attributes.sizeY,
                                 m_attributes.name.c_str(),
                                 nullptr, nullptr));
    glfwMakeContextCurrent(m_win.get());
    glfwSwapInterval(GLFW_FALSE);
}

void window::closeWindow() {
    if (m_win) {
        glfwSetWindowShouldClose(m_win.get(), GLFW_TRUE);
        destroyWindow();
    }
}

window::~window() {
    m_win.reset(nullptr);
    glfwTerminate();
}

void window::destroyWindow() {
    glfwDestroyWindow(m_win.get());
}

void window::windowAttributes(struct windowAttributes attributes) {
    m_attributes = attributes;
}

bool window::run() {
    return !glfwWindowShouldClose(m_win.get());
}

void window::swapBuffers() {
    glfwSwapBuffers(m_win.get());
}

void window::pollEvents() {
    glfwPollEvents();
}

#endif //TETRIS_WINDOW_HPP

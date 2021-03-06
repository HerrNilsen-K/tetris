CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(TETRIS)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH "")
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/app.hpp src/logic/events.hpp src/renderer/GL/GLbuffer.hpp src/renderer/GL/GLarray.hpp src/renderer/GL/GLshader.hpp src/renderer/GL/GLrenderer.hpp src/window/window.hpp src/renderer/field.hpp src/logic/board.cpp src/logic/board.hpp src/constants.hpp src/logic/pieces.hpp src/logic/randomGenerator.hpp)

include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW)

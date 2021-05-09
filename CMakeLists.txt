CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(TETRIS)

list(APPEND CMAKE_PREFIX_PATH "")
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW)

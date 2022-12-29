cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(opengl_tests VERSION 1.0)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
add_subdirectory(glfw-3.3.8)
include_directories(glfw-3.3.8)

add_executable(opengl_tests src/main.cpp glad/src/glad.c)

target_include_directories(opengl_tests PUBLIC
                           "${PROJECT_BINARY_DIR}/includes"
                           )
target_include_directories(opengl_tests PUBLIC
                           "${PROJECT_BINARY_DIR}/glad/include"
                           )
target_link_libraries(opengl_tests glfw ${GLFW_LIBRARIES})
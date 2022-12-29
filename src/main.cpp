#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

std::string read_file(std::string filename) {
    std::ostringstream vertstream;
    std::ifstream vert("shaders/main.vert");
    vertstream << vert.rdbuf();
    std::string str(vertstream.str());
    return str;
}

unsigned int create_shader(int shader_type, const char* source, const char* error) {
    unsigned int shader;
    shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << error << infoLog << "\n";
    }

    return shader;
}

int main() {
    const std::string vertexSource = read_file("shaders/main.vert");
    const char* vertexSourceCStr = vertexSource.c_str();

    const std::string fragmentSource = read_file("shaders/main.frag");
    const char* fragmentSourceCStr = fragmentSource.c_str();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader experiments", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    unsigned int vertexShader = create_shader(GL_VERTEX_SHADER, vertexSourceCStr, "Error with vertex shader \n");
    unsigned int fragmentShader = create_shader(GL_FRAGMENT_SHADER, fragmentSourceCStr, "Error with fragment shader \n");

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
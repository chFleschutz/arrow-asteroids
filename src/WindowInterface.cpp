#include "WindowInterface.h"

#include <iostream>
#include <stdio.h>
#include <stdexcept>


using namespace std;


WindowInterface::WindowInterface(std::string name, int width, int height) {
    this->width = width;
    this->height = height;
    this->title = name;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void WindowInterface::createWindow() {
    if (!glfwInit()) {
        throw runtime_error("No GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (win == nullptr) {
        glfwTerminate();
        throw runtime_error("Cannot create window");
    }

    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwSetWindowPos(win, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
    glfwShowWindow(win);
}

GLFWwindow* WindowInterface::getWinReference() {
    return win;
}

bool WindowInterface::windowShouldClose() {
    glfwPollEvents();
    return glfwWindowShouldClose(win);
}

void WindowInterface::swapBuffers() {
    glfwSwapBuffers(win);
}



WindowInterface::~WindowInterface() {
    glfwDestroyWindow(win);
    glfwTerminate();
}

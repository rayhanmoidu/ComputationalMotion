#include "Canvas.hpp"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Canvas::Canvas(int screenWidth, int screenHeight, char* windowTitle) {
    title = windowTitle;
    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, nullptr, nullptr);
        
    glfwGetFramebufferSize(window, &width, &height);
}

void Canvas::initCanvas() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    glfwPollEvents();
}

void Canvas::drawTestShape() {
    glColor3f(0.5f, 0.5f, 0.5f);
    
    glBegin(GL_QUADS);
    
    glVertex2f(100, 100);
    glVertex2f(200, 100);
    glVertex2f(200, 200);
    glVertex2f(100, 200);
    glEnd();
}

GLFWwindow* Canvas::getWindow() {
    return window;
}

int Canvas::getHeight() {
    return height;
}

int Canvas::getWidth() {
    return width;
}

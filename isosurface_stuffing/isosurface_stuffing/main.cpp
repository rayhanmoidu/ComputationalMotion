#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 500, HEIGHT = 500;

int main() {
    glfwInit();
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Isosurface Stuffing", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to create GLEW" << std::endl;
        
        return -1;
    }
    
    
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glViewport(0, 0, screenWidth, screenHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, screenWidth, 0.0f, screenHeight, 0.0f, 1.0f);
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();
        
        
        glfwPollEvents();

        glColor3f(0.5f, 0.5f, 0.5f);
        
        std:: cout << screenWidth << std :: endl;
        glBegin(GL_QUADS);

        glVertex3f(100, 100, 0.0f);              // Top Left
                glVertex3f( 200, 100, 0.0f);              // Top Right
                glVertex3f( 200,200, 0.0f);              // Bottom Right
                glVertex3f(100,200, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}




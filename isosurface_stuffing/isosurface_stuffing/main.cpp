#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Canvas.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include <stdlib.h>
#include <time.h>
#include "EquilateralTiling.hpp"
#include "CircleIsosurface.hpp"

const GLint WIDTH = 500, HEIGHT = 500;

int main() {
    glfwInit();
    char* windowTitle = "Isosurface Stuffing";
    Canvas canvas(WIDTH, HEIGHT, windowTitle);
    GLFWwindow *window = canvas.getWindow();
    
    
    
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
    
    cout << canvas.getWidth() << canvas.getHeight();
    
    EquilateralTiling newTiling(canvas.getWidth(), canvas.getHeight(), 100);
    newTiling.createTiling(0, 0, "all", "normal");
    
    CircleIsosurface circle(200, canvas.getWidth(), canvas.getHeight(), 2);
    
    while (!glfwWindowShouldClose(window)) {
                
        canvas.initCanvas();
        newTiling.render();
        circle.render();

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}




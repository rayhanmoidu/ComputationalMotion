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
#include "Algorithm.hpp"
#include "Quadtree.hpp"
#include "BarGraph.hpp"

const GLint WIDTH = 1000, HEIGHT = 500;
const int triangleSideLength = 40;
const int circleRadius = 200;
const float alpha = 60;
const int numBars = 18; // 180 % numBars should be 0

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
    
    // TILING
    EquilateralTiling newTiling(canvas.getWidth() / 2, canvas.getHeight(), triangleSideLength);
    newTiling.createTiling(0, 0, "all", "normal");
    
    // ISOSURFACE
    CircleIsosurface circle(circleRadius, canvas.getWidth() / 2, canvas.getHeight(), 2);
    
    // ALGORITHM
    Algorithm algorithmInstance(newTiling, circle, alpha);
    algorithmInstance.execute();
    
    // QUADTREE
    Quadtree quadtreeTiling(canvas.getWidth() / 2, canvas.getHeight(), circle);
    
    // BARGRAPH
    BarGraph bargraph(algorithmInstance.getProcessedTriangles(), canvas.getWidth() / 2, canvas.getHeight(), canvas.getWidth() / 2, numBars);
    
        
    while (!glfwWindowShouldClose(window)) {
                
        canvas.initCanvas();
        
        algorithmInstance.renderProcessedTriangles();
        circle.render();
        algorithmInstance.renderProcessedTriangleCutpoints();
        bargraph.drawGraph();
//        quadtreeTiling.render();

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


// balanace the quadtree
// quadtree tiling (introduce diagonals to make it into triangles, can either simply use the diagonal or do it like the paper did it)
// skew the quadtree to make it into parallelograms that turn into equilateral triangles
// provably good meshig (probably the most ideal one!)



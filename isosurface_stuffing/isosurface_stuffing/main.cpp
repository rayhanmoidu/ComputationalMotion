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
#include "IsoscelesTiling.hpp"
#include "CircleIsosurface.hpp"
#include "Algorithm.hpp"
#include "Quadtree.hpp"
#include "BarGraph.hpp"
#include "RectangleIsosurface.hpp"
#include "QuadtreeTiling.hpp"
#include "IsoscelesSingleQuadtreeTiling.hpp"
#include "IsoscelesDoubleQuadtreeTiling.hpp"
#include "SquareQuadtree.hpp"
#include "ParallelogramQuadtree.hpp"
#include "EquilateralQuadtreeTiling.hpp"
#include "ProvablyGoodTriangleFactory.hpp"
#include "SquareIsosurface.hpp"
#include "ProvablyGoodQuadtreeTiling.hpp"

const GLint WIDTH = 1000, HEIGHT = 500;
const int triangleSideLength = 80;
const int circleRadius = 200;
const int rectangleWidth = 200;
const int rectangleHeight = 200;
const float alpha = 1;
const float isosurfaceRenderingThreshold = 2;
const int numBars = 18; // 180 % numBars should be 0
const int smallestQuadtreeCell = 10;


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
//    IsoscelesTiling newTiling(canvas.getWidth() / 2, canvas.getHeight(), triangleSideLength);
//    newTiling.createTiling(0, 0, "all", "normal");
    
    // ISOSURFACE
    CircleIsosurface isosurface(circleRadius, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);

    RectangleIsosurface rectangle(rectangleWidth, rectangleHeight, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);
    
    // QUADTREE
    SquareQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, isosurface);
    IsoscelesSingleQuadtreeTiling quadtreeTiling(quadtree);
    
    cout << quadtreeTiling.getTriangles().size()<<endl;
//
     //ALGORITHM
    Algorithm algorithmInstance(quadtreeTiling, isosurface, alpha);
    algorithmInstance.execute();

    // BARGRAPH
    BarGraph bargraph(algorithmInstance.getProcessedTriangles(), canvas.getWidth() / 2, canvas.getHeight(), canvas.getWidth() / 2, numBars);

    while (!glfwWindowShouldClose(window)) {
                
        canvas.initCanvas();
//
        algorithmInstance.renderProcessedTriangles();
        algorithmInstance.renderProcessedTriangleCutpoints();
        bargraph.drawGraph();
//        quadtree.render();
//        quadtreeTiling.render();
        

//        isosurface.render();
        

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


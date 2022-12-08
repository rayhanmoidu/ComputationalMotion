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
#include "ProvablyGoodQuadtreeTiling.hpp"
#include "CustomIsosurface.hpp"

const GLint WIDTH = 1000, HEIGHT = 500;
const int triangleSideLength = 80;
const int circleRadius = 200;
const int rectangleWidth = 200;
const int rectangleHeight = 200;
const float alpha = 60;
const float isosurfaceRenderingThreshold = 2;
const int numBars = 18; // 180 % numBars should be 0
const int smallestQuadtreeCell = 2;

float sizingFunction(float x, float y) {
    if (x >= 400 && x <= 600) {
        if (y >= 50 && y <= 200) {
            return 1;
        }
    }
    return 100;
}

float sdf(float x, float y) {
    float valueToRoot = (x - 500)*(x - 500) + (y - 500)*(y - 500);
    float vectorLength = sqrt(valueToRoot);
    return vectorLength - 400;
}

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
    
    
    CustomIsosurface isosurface(&sdf);

    RectangleIsosurface rectangle(rectangleWidth, rectangleHeight, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);
    
    // QUADTREE
//    SquareQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, 10, &sizingFunction, 10);
    ParallelogramQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, isosurface);
    EquilateralQuadtreeTiling quadtreeTiling(quadtree);
    
//    SquareQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, isosurface);
//    IsoscelesDoubleQuadtreeTiling quadtreeTiling(quadtree);

    //
     //ALGORITHM
    Algorithm algorithmInstance(quadtreeTiling, isosurface, alpha);
    algorithmInstance.execute();
    
    cout << algorithmInstance.getProcessedTriangles().size()<<endl;

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
        

        isosurface.render();
        

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


// allow users to only specify refinemenet in cells blocks of size x
// thus, need to test x units away accross area of each cell for refinement



// ask about inputs / outputs

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

const GLint WIDTH = 1000, HEIGHT = 500;
const int triangleSideLength = 80;
const int circleRadius = 200;
const int rectangleWidth = 200;
const int rectangleHeight = 200;
const float alpha = 60;
const float isosurfaceRenderingThreshold = 2;
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
//    IsoscelesTiling newTiling(canvas.getWidth() / 2, canvas.getHeight(), triangleSideLength);
//    newTiling.createTiling(0, 0, "all", "normal");
    
    // ISOSURFACE
    SquareIsosurface isosurface(circleRadius, circleRadius, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);
    RectangleIsosurface rectangle(rectangleWidth, rectangleHeight, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);
    
    // QUADTREE
    ParallelogramQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), 10, isosurface);
    EquilateralQuadtreeTiling quadtreeTiling(quadtree);
//
    // ALGORITHM
    Algorithm algorithmInstance(quadtreeTiling, isosurface, alpha);
    algorithmInstance.execute();

    // BARGRAPH
    BarGraph bargraph(algorithmInstance.getProcessedTriangles(), canvas.getWidth() / 2, canvas.getHeight(), canvas.getWidth() / 2, numBars);
    
//    ProvablyGoodTriangleFactory testProvablyGood_1(AAAA, Point(200, 200), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_2(AAAB, Point(200, 400), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_3(AABB, Point(200, 600), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_4(BBCC, Point(400, 200), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_5(BBBB, Point(400, 400), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_6(BBBC, Point(400, 600), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_7(ABCB, Point(600, 200), 200, 0);
//    ProvablyGoodTriangleFactory testProvablyGood_8(ABAB, Point(600, 400), 500, M_PI/2);
//    ProvablyGoodTriangleFactory testProvablyGood_9(ABBB, Point(600, 600), 200, 0);
    ProvablyGoodTriangleFactory testProvablyGood_8(ABAB, Point(600, 400), 500, M_PI/2);


    while (!glfwWindowShouldClose(window)) {
                
        canvas.initCanvas();
//
//        algorithmInstance.renderProcessedTriangles();
//        algorithmInstance.renderProcessedTriangleCutpoints();
//        bargraph.drawGraph();
//        quadtree.render();
//        quadtreeTiling.render();
        

//        isosurface.render();
        
//        testProvablyGood_1.render();
//        testProvablyGood_2.render();
//        testProvablyGood_3.render();
//        testProvablyGood_4.render();
//        testProvablyGood_5.render();
//        testProvablyGood_6.render();
//        testProvablyGood_7.render();
        testProvablyGood_8.render();
//        testProvablyGood_9.render();
        

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


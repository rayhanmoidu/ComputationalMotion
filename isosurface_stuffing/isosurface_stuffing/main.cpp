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
const float alpha = 0.25;
const float isosurfaceRenderingThreshold = 2;
const int numBars = 18; // 180 % numBars should be 0
const int smallestQuadtreeCell = 10;

const float originX = -500;
const float originY = -500;

float sizingFunction(float x, float y) {
    if (x >= -100 && x <= 100) {
        if (y >= -100 && y <= 100) {
            return 1;
        }
    }
    return 100;
}

float sdf(float x, float y) {
    float valueToRoot = (x)*(x) + (y)*(y);
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
    
    
    CustomIsosurface isosurface(&sdf, originX, originY);

    RectangleIsosurface rectangle(rectangleWidth, rectangleHeight, canvas.getWidth() / 2, canvas.getHeight(), isosurfaceRenderingThreshold);
    
    // QUADTREE
    SquareQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, 10, &sizingFunction, 10, originX, originY);
//    ParallelogramQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, isosurface);
//    EquilateralQuadtreeTiling quadtreeTiling(quadtree);
    
//    SquareQuadtree quadtree(canvas.getWidth() / 2, canvas.getHeight(), smallestQuadtreeCell, isosurface);
    ProvablyGoodQuadtreeTiling quadtreeTiling(quadtree);
//    IsoscelesTiling quadtreeTiling(canvas.getWidth() / 2, canvas.getHeight(), triangleSideLength);
    //
     //ALGORITHM
    Algorithm algorithmInstance(&quadtreeTiling, isosurface, alpha);
    algorithmInstance.execute();
    
    cout << algorithmInstance.getProcessedTriangles().size()<<endl;

    // BARGRAPH
    BarGraph bargraph(algorithmInstance.getProcessedTrianglesObjects(), canvas.getWidth() / 2, canvas.getHeight(), canvas.getWidth() / 2, numBars);
    
    pair<vector<pair<float, float>>, vector<vector<int>>> output = algorithmInstance.getOutput(originX, originY);
    
    vector<pair<float, float>> retVertices = output.first;
    vector<vector<int>> retTriangles = output.second;
//    vector<pair<float, float>> vertices = algorithmInstance.getResultingVertices();
//    vector<vector<int>> triangles = algorithmInstance.getProcessedTriangles();
//
//
//    // ORGANIZING USER OUTPUT - this is actually working well, nice.
//    std::unordered_map<int, int> oldIndexToNewIndex;
//    std::unordered_set<int> coveredIndices;
//
//    vector<pair<float, float>> retVertices;
//    vector<vector<int>> retTriangles;
//
//    for (int i = 0; i < triangles.size(); i++) {
//        vector<int> oldTriangleIndices = triangles[i];
//        vector<int> newTriangleIndices;
//
//        for (int j = 0; j < oldTriangleIndices.size(); j++) {
//            if (coveredIndices.count(oldTriangleIndices[j])) {
//                newTriangleIndices.push_back(oldIndexToNewIndex.at(oldTriangleIndices[j]));
//            } else {
//                pair<float, float> oldVertex = vertices[oldTriangleIndices[j]];
//                pair<float, float> newVertex(oldVertex.first + originX, oldVertex.second + originY);
//
//                retVertices.push_back(newVertex);
//                coveredIndices.insert(oldTriangleIndices[j]);
//
//                pair<int, int> mapInsertion(oldTriangleIndices[j], retVertices.size()-1);
//                oldIndexToNewIndex.insert(mapInsertion);
//
//                newTriangleIndices.push_back(retVertices.size()-1);
//            }
//        }
//
//        if (newTriangleIndices[0]!=newTriangleIndices[1] && newTriangleIndices[1]!=newTriangleIndices[2] && newTriangleIndices[2]!=newTriangleIndices[0]) {
//            retTriangles.push_back(newTriangleIndices);
//        }
//    }
//
//    for (int i = 0; i < retVertices.size(); i++) {
//        cout << retVertices[i].first<<" "<<retVertices[i].second<<endl;
//    }
    
    
//    unordered_map<int, int> mymap;
//    for (int i = 0; i < finalTriangles.size(); i++) {
//
//        for (int j = 0; j < finalTriangles[i].size(); j++) {
//            int i1 = finalTriangles[i][j];
//            if (mymap.count(i1)) {
//                int ims = mymap.at(i1)+1;
////                cout<<"LALA "<<ims<<endl;
//                mymap.insert_or_assign(i1, ims);
//            }
//            else mymap.insert(pair<int, int>(i1, 1));
//        }
//    }
//
//    for (int i = 0; i < vertices.size(); i++) {
//        cout << "vertex "<<vertices[i].first << " "<<vertices[i].second<<endl;
//    }
//
//    for (int i = 0; i < vertices.size(); i++) {
//        for (int j = 0; j < vertices.size(); j++) {
//            Point p1(vertices[i].first, vertices[i].second);
//            Point p2(vertices[j].first, vertices[j].second);
//
//            if (i!=j && p1==p2) {
//                cout <<"DUPLICATES THAT HASHING ISNT COVERING"<<endl;
//                cout <<i<<" "<<j<<endl;
//                cout << vertices[i].first << " "<<vertices[i].second<<endl;
//                cout << vertices[j].first << " "<<vertices[j].second<<endl;
//            }
//        }
//    }
    float offset = 500;
    
    while (!glfwWindowShouldClose(window)) {
                
        canvas.initCanvas();

        
        for (int i = 0; i < retTriangles.size(); i++) {
            vector<int> curTriangle = retTriangles[i];
            Point p1(retVertices[curTriangle[0]].first+offset, retVertices[curTriangle[0]].second+offset);
            Point p2(retVertices[curTriangle[1]].first+offset, retVertices[curTriangle[1]].second+offset);
            Point p3(retVertices[curTriangle[2]].first+offset, retVertices[curTriangle[2]].second+offset);
            
            Triangle newTri(p1, p2, p3, 0, 0, 0);
            newTri.render();
        }
                    

//        bargraph.drawGraph();
        

        isosurface.render();
        

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


// allow users to only specify refinemenet in cells blocks of size x
// thus, need to test x units away accross area of each cell for refinement



// ask about inputs / outputs




// ASK PROFESSOR BATTY ABOUT HOW THE USER WILL DEFINT THE SDF AND THE SIZING FUNCTION WITH RESPECT TO THE ORIGIN!

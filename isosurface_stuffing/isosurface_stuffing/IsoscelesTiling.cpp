#include "IsoscelesTiling.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

IsoscelesTiling::IsoscelesTiling(int width, int height, int triangleSize) {
    hBound = width;
    vBound = height;
    triangleSideLength = triangleSize*2; // accounts for doubled canvas size
    createTiling(0, 0, "all", "normal");
}

void IsoscelesTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    if (xPos < hBound && yPos < vBound) {
        Point p1(xPos, yPos);
        Point p2(xPos + triangleSideLength, yPos);
        Point p3(xPos + triangleSideLength, yPos + triangleSideLength);
        Point p4(xPos, yPos + triangleSideLength);
        
        int p1Index = 0;
        int p2Index = 0;
        int p3Index = 0;
        int p4Index = 0;
        
        if (verticesSet.count(pair<float, float>(p1.getX(), p1.getY()))) {
            p1Index = findVertexIndex(p1);
        } else {
            addVertex(p1);
            p1Index = int(vertices.size() - 1);
        }
        
        if (verticesSet.count(pair<float, float>(p2.getX(), p2.getY()))) {
            p2Index = findVertexIndex(p2);
        } else {
            addVertex(p1);
            p2Index = int(vertices.size() - 1);
        }
        
        if (verticesSet.count(pair<float, float>(p3.getX(), p3.getY()))) {
            p3Index = findVertexIndex(p3);
        } else {
            addVertex(p1);
            p3Index = int(vertices.size() - 1);
        }
        
        if (verticesSet.count(pair<float, float>(p4.getX(), p4.getY()))) {
            p4Index = findVertexIndex(p4);
        } else {
            addVertex(p1);
            p4Index = int(vertices.size() - 1);
        }
        
        Triangle t1;
        Triangle t2;
        
        if (orientation=="normal") {
            t1.setPointsAndIndices(p1, p2, p3, p1Index, p2Index, p3Index);
            t2.setPointsAndIndices(p1, p3, p4, p1Index, p3Index, p4Index);
        } else {
            t1.setPointsAndIndices(p1, p2, p4, p1Index, p2Index, p4Index);
            t2.setPointsAndIndices(p2, p3, p4, p2Index, p3Index, p4Index);
        }
        
        triangles.push_back(t1);
        triangles.push_back(t2);
        
        string oppositeKey = "";
        
        if (orientation=="normal") {
            oppositeKey = "inverted";
        } else {
            oppositeKey = "normal";
        }
        
        if (key=="up") {
            createTiling(p4.getX(), p4.getY(), "up", oppositeKey);
        } else if (key=="right") {
            createTiling(p2.getX(), p2.getY(), "right", oppositeKey);
        } else {
            createTiling(p2.getX(), p2.getY(), "right", oppositeKey);
            createTiling(p3.getX(), p3.getY(), "all", orientation);
            createTiling(p4.getX(), p4.getY(), "up", oppositeKey);
        }
    }
}

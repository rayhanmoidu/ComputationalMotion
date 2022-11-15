#include "EquilateralTiling.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

EquilateralTiling::EquilateralTiling(int width, int height, int triangleSize) {
    hBound = width;
    vBound = height;
    triangleSideLength = triangleSize*2; // accounts for doubled canvas size
}

void EquilateralTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    if (xPos < hBound && yPos < vBound) {
        Point p1(xPos, yPos);
        Point p2(xPos + triangleSideLength, yPos);
        Point p3;
        Point p4;
        
        if (orientation=="normal") {
            p3.setX(xPos + triangleSideLength + (triangleSideLength/2));
            p3.setY(yPos + sqrt(3)/2*triangleSideLength);
            p4.setX(xPos + (triangleSideLength/2));
            p4.setY(yPos + sqrt(3)/2*triangleSideLength);
        } else {
            p3.setX(xPos + (triangleSideLength/2));
            p3.setY(yPos + sqrt(3)/2*triangleSideLength);
            p4.setX(xPos - (triangleSideLength/2));
            p4.setY(yPos + sqrt(3)/2*triangleSideLength);
        }
        
//        vertices.insert(pair<float, float>(p1.getX(), p1.getY()));
//        vertices.insert(pair<float, float>(p2.getX(), p2.getY()));
//        vertices.insert(pair<float, float>(p3.getX(), p3.getY()));
//        vertices.insert(pair<float, float>(p4.getX(), p4.getY()));
        
        addVertex(p1);
        addVertex(p2);
        addVertex(p3);
        addVertex(p4);
        
        Triangle t1;
        Triangle t2;
        
        if (orientation=="normal") {
            t1.setPoints(p1, p2, p4);
            t2.setPoints(p2, p4, p3);
        } else {
            t1.setPoints(p1, p2, p3);
            t2.setPoints(p1, p4, p3);
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
            createTiling(p2.getX(), p2.getY(), "right", orientation);
        } else {
            createTiling(p2.getX(), p2.getY(), "right", orientation);
            createTiling(p3.getX(), p3.getY(), "all", oppositeKey);
            createTiling(p4.getX(), p4.getY(), "up", oppositeKey);
        }
    }
}

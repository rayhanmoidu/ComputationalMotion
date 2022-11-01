#include "IsoscelesTiling.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

IsoscelesTiling::IsoscelesTiling(int width, int height, int triangleSize) {
    hBound = width;
    vBound = height;
    triangleSideLength = triangleSize*2; // accounts for doubled canvas size
}

void IsoscelesTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    if (xPos < hBound && yPos < vBound) {
        Point p1(xPos, yPos);
        Point p2(xPos + triangleSideLength, yPos);
        Point p3(xPos + triangleSideLength, yPos + triangleSideLength);
        Point p4(xPos, yPos + triangleSideLength);
        
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);
        
        Triangle t1;
        Triangle t2;
        
        if (orientation=="normal") {
            t1.setPoints(p1, p2, p3);
            t2.setPoints(p1, p4, p3);
        } else {
            t1.setPoints(p1, p2, p4);
            t2.setPoints(p2, p4, p3);
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

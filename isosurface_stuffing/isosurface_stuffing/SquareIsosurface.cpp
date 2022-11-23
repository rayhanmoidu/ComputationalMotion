//
//  SquareIsosurface.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#include "SquareIsosurface.hpp"
#include <cmath>
#include <algorithm>

SquareIsosurface::SquareIsosurface(int rectWidth, int rectHeight, int width, int height, float threshold) {
    rectangleWidth = rectWidth*2;
    rectangleHeight = rectHeight*2;
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = threshold;
}

float SquareIsosurface::signedDistanceFunction(Point p) {
    float newX = p.getX() - (screenWidth / 2);
    float newY = p.getY() - (screenWidth / 2);
    
    float dx = abs(newX) - rectangleWidth;
    float dy = abs(newY) - rectangleHeight;
    
    if ((dx==0 && dy < 0) || (dy==0 && dx < 0)) return 0;
    if (dx < 0 && dy < 0) return std::max(dx, dy);
    if (dx < 0) return dy;
    if (dy < 0) return dx;
    return sqrt(dx*dx + dy*dy);

}



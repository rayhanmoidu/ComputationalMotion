//
//  RectangleIsosurface.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-01.
//

#include "RectangleIsosurface.hpp"
#include <cmath>

RectangleIsosurface::RectangleIsosurface(int rectWidth, int rectHeight, int width, int height, float threshold) {
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = threshold;
    rectangleWidth = rectWidth*2; // accounts for doubled canvas size
    rectangleHeight = rectHeight*2; // accounts for doubled canvas size
}

float RectangleIsosurface::signedDistanceFunction(Point p) {
    float newX = p.getX() - (screenWidth / 2);
    float newY = p.getY() - (screenHeight / 2);
    
    float px = abs(newX) - rectangleWidth;
    float py = abs(newY) - rectangleHeight;
    
    if ((px==0 && py < 0) || (py==0 && px < 0)) return 0;
    if (px < 0 && py < 0) {
        if (px < py) return py;
        return px;
    }
    if (px < 0) return py;
    if (py < 0) return px;
    return sqrt(px*px + py*py);
}


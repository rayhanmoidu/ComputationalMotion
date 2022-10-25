//
//  CircleIsosurface.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-10-25.
//

#include "CircleIsosurface.hpp"
#include <cmath>

CircleIsosurface::CircleIsosurface(int circleRadius, int width, int height, float threshold) {
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = threshold;
    radius = circleRadius*2; // accounts for doubled canvas size
}

float CircleIsosurface::signedDistanceFunction(Point p) {
    float valueToRoot = (p.getX() - (screenWidth / 2))*(p.getX() - (screenWidth / 2)) + (p.getY() - (screenHeight / 2))*(p.getY() - (screenHeight / 2));
    float vectorLength = sqrt(valueToRoot);
    return vectorLength - radius;
}

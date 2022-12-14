//
//  CustomIsosurface.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-12-07.
//

#include "CustomIsosurface.hpp"

CustomIsosurface::CustomIsosurface(float (*func)(float, float), float oX, float oY) {
    customSignedDistanceFunction = func;
    originX = oX;
    originY = oY;
}

float CustomIsosurface::signedDistanceFunction(Point p) {
    return customSignedDistanceFunction(p.getX() + originX, p.getY() + originY);

//    return customSignedDistanceFunction(p.getX() - screenWidth/2, p.getY() - screenHeight/2);
}

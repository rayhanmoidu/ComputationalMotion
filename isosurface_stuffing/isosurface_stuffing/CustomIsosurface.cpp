//
//  CustomIsosurface.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-12-07.
//

#include "CustomIsosurface.hpp"

CustomIsosurface::CustomIsosurface(float (*func)(float, float)) {
    customSignedDistanceFunction = func;
}

float CustomIsosurface::signedDistanceFunction(Point p) {
    return customSignedDistanceFunction(p.getX(), p.getY());
}

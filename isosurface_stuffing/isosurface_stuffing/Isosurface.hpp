#ifndef Isosurface_hpp
#define Isosurface_hpp

#include <stdio.h>
#include "Point.hpp"

class Isosurface {
public:
    Isosurface(int=0, int=0, float=0);
    virtual float signedDistanceFunction(Point) = 0;
    int evaluatePoint(Point);
    void render();
    
protected:
    int screenWidth;
    int screenHeight;
    float renderingThreshold;
};

#endif /* Isosurface_hpp */

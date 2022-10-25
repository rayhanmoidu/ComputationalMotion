#ifndef Tiling_hpp
#define Tiling_hpp

#include <stdio.h>
#include "Triangle.hpp"

class Tiling {
public:
    Tiling(int=0, int=0, int=0);
    void render();
    
    // virtual
    virtual void createTiling(float, float, string, string) = 0;
    
    // getters
    vector<Triangle>* getTriangles();
    
protected:    
    vector<Triangle> triangles;
    vector<Point> vertices;
    int hBound;
    int vBound;
    int triangleSideLength;
};

#endif /* Tiling_hpp */

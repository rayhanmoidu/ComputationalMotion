//
//  RenderTriangle.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-12-13.
//

#ifndef RenderTriangle_hpp
#define RenderTriangle_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Cutpoint.hpp"
#include <vector>
#include <utility>
#include "Triangle.hpp"

using namespace std;

class RenderTriangle {
public:
    RenderTriangle(vector<pair<float, float>>, Triangle);
    vector<float> computeAngles();
    
    void render();
    void renderCutpoints();
    
private:
    void setColors();
    float applyCosineLaw(float, float, float);
    
    vector<Cutpoint> cutpoints;
    Point p1;
    Point p2;
    Point p3;
    
    float colorkey1;
    float colorkey2;
    float colorkey3;
};

#endif /* RenderTriangle_hpp */

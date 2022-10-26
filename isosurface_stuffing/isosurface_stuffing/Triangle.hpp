#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Cutpoint.hpp"
#include <vector>

using namespace std;

class Triangle {
public:
    Triangle(Point, Point, Point);
    Triangle();
    bool doesContainCutpoint(Cutpoint);
    bool doesContainVertex(Point);
    void wrapVertexToCutpoint(Point, Cutpoint);
    void removeCutpoint(Cutpoint);
    void removeAllCutpoints();
    void addCutpoint(Cutpoint);
    
    void render();
    void renderCutpoints();
    
    void setPoints(Point, Point, Point);
    vector<Point> getPoints();
    
private:
    void setColors();
    
    Point p1;
    Point p2;
    Point p3;
    vector<Cutpoint> cutpoints;
    float colorkey1;
    float colorkey2;
    float colorkey3;
};

#endif /* Triangle_hpp */

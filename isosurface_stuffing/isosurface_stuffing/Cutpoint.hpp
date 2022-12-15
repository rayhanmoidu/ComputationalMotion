#ifndef Cutpoint_hpp
#define Cutpoint_hpp

#include <stdio.h>
#include "Point.hpp"
#include <utility>

class Cutpoint : public Point {
public:
    Cutpoint(float, float, Point, Point);
    bool operator == (Cutpoint &obj);
    
    bool isContainedByVertex(Point);
    std::pair<Point, Point> getBounds();
    
private:
    Point bound1;
    Point bound2;
};

#endif /* Cutpoint_hpp */

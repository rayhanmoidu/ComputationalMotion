#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point {
public:
    Point(float pointX = 0, float pointY = 0);
    bool operator == (Point &obj);
    
    //getters
    float getX();
    float getY();
    
    //setters
    void setX(float);
    void setY(float);
    
    void plot(int);
    
    void rotate(float, Point);

protected:
    int getCanvasCoordinate(int);
    
    float x;
    float y;
};

#endif

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Cutpoint.hpp"
#include <vector>

using namespace std;

class Triangle {
public:
    Triangle(Point, Point, Point, int, int, int);
    Triangle();
    bool doesContainCutpoint(Cutpoint);
    bool doesContainVertex(Point);
    bool doesContainVertex(int);
    void warpVertexToCutpoint(Point, Cutpoint, int);
    void removeCutpoint(Cutpoint);
    void removeAllCutpoints();
    void addCutpoint(Cutpoint);
    vector<float> computeAngles();
    
    void render();
    void renderCutpoints();
    
    void setPointsAndIndices(Point, Point, Point, int, int, int);
    vector<Point> getPoints();
    vector<Cutpoint> getCutpoints();
    vector<int> getIndices();
    
    bool operator == (Triangle &obj);
    
private:
    void setColors();
    float applyCosineLaw(float, float, float);
    
    Point p1;
    Point p2;
    Point p3;
    vector<Cutpoint> cutpoints;
    float colorkey1;
    float colorkey2;
    float colorkey3;
    
    int i1;
    int i2;
    int i3;
};

#endif /* Triangle_hpp */

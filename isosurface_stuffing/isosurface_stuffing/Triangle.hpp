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
    void warpVertexToCutpoint(Point, Cutpoint);
    void removeCutpoint(Cutpoint);
    void removeAllCutpoints();
    void addCutpoint(Cutpoint);
    vector<float> computeAngles();
    
    void render();
    void renderCutpoints();
    
    void setPoints(Point, Point, Point);
    
    void setDoesExistVertexBetweenP1P2(bool);
    void setDoesExistVertexBetweenP2P3(bool);
    void setDoesExistVertexBetweenP1P3(bool);
    bool getDoesExistVertexBetweenP1P2();
    bool getDoesExistVertexBetweenP2P3();
    bool getDoesExistVertexBetweenP1P3();
    
    void addTwin(Triangle);
    vector<Triangle> getTwins();
    
    vector<Point> getPoints();
    vector<Cutpoint> getCutpoints();
    
    bool doTriangleVerticesMatch(Triangle t2);
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
    
    bool doesExistVertexBetweenP1P2;
    bool doesExistVertexBetweenP2P3;
    bool doesExistVertexBetweenP1P3;
    vector<Triangle> twins;
};

#endif /* Triangle_hpp */

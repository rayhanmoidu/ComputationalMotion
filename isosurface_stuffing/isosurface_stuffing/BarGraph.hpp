#ifndef BarGraph_hpp
#define BarGraph_hpp

#include "Triangle.hpp"
#include <map>

class BarGraph {
public:
    BarGraph(vector<Triangle>, int, int, int, int);
    void drawGraph();
    
private:
    void drawGraphTemplate();
    
    void computeAngles();
    void distributeGraphValues();
    float applyCosineLaw(float, float, float);
    
    vector<Triangle> triangles;
    vector<float> angles;
    map<int, int> graphValues;
    
    int screenWidth;
    int screenHeight;
    int xStartPos;
    
    int numBars;
    int angleWindowPerBar;
    
    int maxGraphValue;
    
    const int horizontalOffset = 50;
    const int verticalOffset = 50;
    const int templateThickness = 10;
};

#endif /* BarGraph_hpp */

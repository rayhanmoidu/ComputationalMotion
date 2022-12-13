#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Cutpoint.hpp"
#include <vector>

using namespace std;

class Triangle {
public:
    Triangle(int, int, int);
    Triangle();
    
    bool doesContainCutpoint(Cutpoint);
    bool doesContainIndex(int);
    
    void warpVertexToCutpoint(int, int);
    
    void removeCutpoint(Cutpoint);
    void removeAllCutpoints();
    void addCutpoint(Cutpoint);
    
    void setIndices(int, int, int);
    vector<int> getIndices();

    vector<Cutpoint> getCutpoints();
    
    vector<Point> getPoints(vector<pair<float, float>> vertices);
    
    bool operator == (Triangle &obj);
    bool doIndicesMatch(Triangle obj);
    
private:
    vector<Cutpoint> cutpoints;
    int i1;
    int i2;
    int i3;
};

#endif /* Triangle_hpp */

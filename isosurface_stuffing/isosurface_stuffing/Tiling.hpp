#ifndef Tiling_hpp
#define Tiling_hpp

#include <stdio.h>
#include "Triangle.hpp"
#include "Quadtree.hpp"
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <set>
#include "Point.hpp"
#include "Isosurface.hpp"
#include <vector>
#include <map>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<float,float> & v) const {
        double ok1 = ceil(v.first);
        double ok2 = ceil(v.second);
        double prime = 31;
        double result = 1;
        result = prime * result + ok1;
        result = prime * result + ok2;
        return result;
//        return std::round(result * 1000.0) / 1000.0;
        return pow((result*v.first), v.second);
    }
};

class Tiling {
public:
    Tiling(int=0, int=0, int=0);
    void render();
    
    // virtual
    virtual void createTiling(float, float, string, string) = 0;
    
    // getters
    vector<Triangle> getTriangles();
    vector<pair<float, float>> getVertices();
    Point getVertex(int);
    
    int check_addVertex_getIndex(Point p);
    int addVertex_getIndex(Point p);
    
protected:
    vector<Triangle> triangles;
    
    vector<pair<float, float>> vertices;
    std::unordered_set<std::pair<float, float>, pair_hash> verticesSet;
    std::unordered_map<std::pair<float, float>, int, pair_hash> verticesToIndexInList;
    int findVertexIndex(Point p);
    void addVertex(pair<float, float> v);
    bool doesVertexExist(Point p);
    
    int hBound;
    int vBound;
    int triangleSideLength;
};

#endif /* Tiling_hpp */

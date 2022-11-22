#ifndef Tiling_hpp
#define Tiling_hpp

#include <stdio.h>
#include "Triangle.hpp"
#include "Quadtree.hpp"
#include <unordered_set>
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
        int prime = 31;
        int result = 1;
        result = prime * result + v.first;
        result = prime * result + v.second;
        return result;
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
    
    void addVertex(Point);
    vector<Triangle> removeTriangle(vector<Triangle>, Triangle);
    
protected:
    vector<Triangle> triangles;
    std::unordered_set<std::pair<float, float>, pair_hash> vertices;
    int hBound;
    int vBound;
    int triangleSideLength;
};

#endif /* Tiling_hpp */

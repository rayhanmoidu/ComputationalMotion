//
//  Quadtree.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-10-26.
//

#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <stdio.h>
#include "Isosurface.hpp"
#include <vector>
#include <utility>
//#include <pair>

using namespace std;

enum Direction { north, east, south, west };

struct QuadtreeNode {
    float centerX;
    float centerY;
    float dimension;
    vector<QuadtreeNode> children;
    
    QuadtreeNode() {
        centerX = 0;
        centerY = 0;
        dimension = 0;
        children = vector<QuadtreeNode>();
    }
    
    QuadtreeNode(float cx, float cy, float d) {
        centerX = cx;
        centerY = cy;
        dimension = d;
        children = vector<QuadtreeNode>();
    }
    
    void addChild(QuadtreeNode newChild) {
        children.push_back(newChild);
    }
    
    bool operator == (QuadtreeNode &obj) {
        return obj.centerY == centerY && obj.centerX == centerX && obj.dimension == dimension;
    }
};

class Quadtree {
public:
    Quadtree(int, int, int, Isosurface&);
    void render();
    void test123();
    
private:
    bool shouldRefine(QuadtreeNode);
    
    void construct();
    void constructChildren(QuadtreeNode*);
    
    // balancing
    pair<Point, Point> findCellBoundsInDirection(QuadtreeNode, Direction);
    vector<QuadtreeNode> findLeafNeighborsInDirection(QuadtreeNode, Direction);
    vector<QuadtreeNode> neighborsHelper(Point, Point, vector<QuadtreeNode>, QuadtreeNode, Direction);
    vector<QuadtreeNode*> getListOfLeavesHelper(QuadtreeNode*, vector<QuadtreeNode*>);
    vector<QuadtreeNode*> getListOfLeaves();
    void balanceQuadtree();
        
    void renderHelper(QuadtreeNode);
    
    int gridSizeLimit;
    int hBound;
    int vBound;
    
    Isosurface &isosurface;
    QuadtreeNode root;
};

#endif /* Quadtree_hpp */

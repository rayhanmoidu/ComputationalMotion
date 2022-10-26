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

using namespace std;

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
};

class Quadtree {
public:
    Quadtree(int, int, Isosurface&);
    void construct();
    void render();
    bool shouldRefine(QuadtreeNode);
    void constructChildren(QuadtreeNode*);
    
private:
    void renderHelper(QuadtreeNode);
    
    int hBound;
    int vBound;
    Isosurface &isosurface;
    QuadtreeNode root;
};

#endif /* Quadtree_hpp */

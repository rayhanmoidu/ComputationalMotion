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
#include <iostream>
#include "QuadtreeNode.hpp"
//#include <pair>

using namespace std;

class Quadtree {
public:
    Quadtree(int, int, int, Isosurface&);
    Quadtree(Isosurface&);
    virtual void render() = 0;
    
    QuadtreeNode* getRoot();
    Isosurface& getIsosurface();
    
protected:
    virtual bool shouldRefine(QuadtreeNode*) = 0;
    virtual void constructChildren(QuadtreeNode*) = 0;
    virtual void renderHelper(QuadtreeNode*) = 0;
    virtual void colorSquare(QuadtreeNode) = 0;
    
    // balancing
    vector<QuadtreeNode*> getListOfLeavesHelper(QuadtreeNode*, vector<QuadtreeNode*>);
    vector<QuadtreeNode*> getListOfLeaves();
    vector<QuadtreeNode*> removeNodeFromVector(vector<QuadtreeNode*>, QuadtreeNode*);
    
    // test neighbour finding
    QuadtreeNode* getNeighbourOfGreaterOrEqualSize(QuadtreeNode*, Direction);
    vector<QuadtreeNode*> getNeighboursOfSmallerSize(QuadtreeNode*, QuadtreeNode*, Direction);
    vector<QuadtreeNode*> getNeighbours(QuadtreeNode*, Direction);
    
    bool doesContainLeaf(vector<QuadtreeNode*>, QuadtreeNode*);
    void balanceQuadtree();
    bool isBalanced();
    
    int gridSizeLimit;
    int hBound;
    int vBound;
    
    Isosurface &isosurface;
    QuadtreeNode* root;
};

#endif /* Quadtree_hpp */

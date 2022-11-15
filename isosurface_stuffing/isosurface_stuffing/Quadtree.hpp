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
    void render();
    
    QuadtreeNode* getRoot();
    
private:
    bool shouldRefine(QuadtreeNode*);
    
    void construct();
    void constructChildren(QuadtreeNode*);
    
    // balancing
    pair<Point, Point> findCellBoundsInDirection(QuadtreeNode, Direction);
    vector<QuadtreeNode*> findLeafNeighborsInDirection(QuadtreeNode*, Direction);
    vector<QuadtreeNode*> findLeafNeighborsInDirectionHelper(Point, Point, vector<QuadtreeNode*>, QuadtreeNode*, Direction);
    vector<QuadtreeNode*> getListOfLeavesHelper(QuadtreeNode*, vector<QuadtreeNode*>);
    vector<QuadtreeNode*> getListOfLeaves();
    vector<QuadtreeNode*> removeLeaf(vector<QuadtreeNode*>, QuadtreeNode*);
    bool doesContainLeaf(vector<QuadtreeNode*>, QuadtreeNode*);
    void balanceQuadtree();
    bool isBalanced();
        
    void renderHelper(QuadtreeNode*);
    
    int gridSizeLimit;
    int hBound;
    int vBound;
    
    Isosurface &isosurface;
    QuadtreeNode* root;
};

#endif /* Quadtree_hpp */

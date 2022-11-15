//
//  QuadtreeNode.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-14.
//

#ifndef QuadtreeNode_hpp
#define QuadtreeNode_hpp

#include <stdio.h>
#include <vector>

using namespace std;

enum Direction { north, east, south, west, northeast, northwest, southeast, southwest };

class QuadtreeNode {
public:
    QuadtreeNode();
    QuadtreeNode(float, float, float, QuadtreeNode*);
    
    int numChildren();
    void addChild(QuadtreeNode*, Direction);
    bool isLeaf();
    
    vector<QuadtreeNode*> getChildren();
    float getCenterX();
    float getCenterY();
    float getDimension();
    
    QuadtreeNode* getParent();
    QuadtreeNode* getNEChild();
    QuadtreeNode* getNWChild();
    QuadtreeNode* getSEChild();
    QuadtreeNode* getSWChild();
    
    bool operator == (QuadtreeNode &obj);

private:
    float centerX;
    float centerY;
    float dimension;
    QuadtreeNode* NEChild;
    QuadtreeNode* NWChild;
    QuadtreeNode* SEChild;
    QuadtreeNode* SWChild;
    QuadtreeNode* parent;
};

//QuadtreeNode nullQuadtreeNode(-1, -1, -1);

#endif /* QuadtreeNode_hpp */

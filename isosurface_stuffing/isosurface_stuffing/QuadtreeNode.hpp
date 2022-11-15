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
    QuadtreeNode(float, float, float);
    int numChildren();
    vector<QuadtreeNode*> getChildren();
    float getCenterX();
    float getCenterY();
    float getDimension();
    
    void addChild(QuadtreeNode*, Direction);
    
    bool operator == (QuadtreeNode &obj);

private:
    float centerX;
    float centerY;
    float dimension;
    QuadtreeNode* NEChild;
    QuadtreeNode* NWChild;
    QuadtreeNode* SEChild;
    QuadtreeNode* SWChild;
};

//QuadtreeNode nullQuadtreeNode(-1, -1, -1);

#endif /* QuadtreeNode_hpp */

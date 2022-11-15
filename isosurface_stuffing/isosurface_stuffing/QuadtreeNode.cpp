//
//  QuadtreeNode.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-14.
//

#include "QuadtreeNode.hpp"
#include <iostream>

using namespace std;

QuadtreeNode::QuadtreeNode() {
    centerX = 0;
    centerY = 0;
    dimension = 0;
    NEChild = NULL;
    NWChild = NULL;
    SEChild = NULL;
    SWChild = NULL;
}

QuadtreeNode::QuadtreeNode(float cx, float cy, float d) {
    centerX = cx;
    centerY = cy;
    dimension = d;
    NEChild = NULL;
    NWChild = NULL;
    SEChild = NULL;
    SWChild = NULL;
}

float QuadtreeNode::getDimension() {
    return dimension;
}

float QuadtreeNode::getCenterX() {
    return centerX;
}

float QuadtreeNode::getCenterY() {
    return centerY;
}

int QuadtreeNode::numChildren() {
    int count = 0;
    if (NEChild != NULL) count++;
    if (NWChild != NULL) count++;
    if (SEChild != NULL) count++;
    if (SWChild != NULL) count++;
    return count;
}

vector<QuadtreeNode*> QuadtreeNode::getChildren() {
    vector<QuadtreeNode*> children;
    if (NEChild != NULL) children.push_back(NEChild);
    if (NWChild != NULL) children.push_back(NWChild);
    if (SEChild != NULL) children.push_back(SEChild);
    if (SWChild != NULL) children.push_back(SWChild);
    return children;
}

void QuadtreeNode::addChild(QuadtreeNode* newChild, Direction dir) {
    if (dir==northeast) NEChild = newChild;
    if (dir==northwest) NWChild = newChild;
    if (dir==southeast) SEChild = newChild;
    if (dir==southwest) SWChild = newChild;
}

bool QuadtreeNode::operator == (QuadtreeNode &obj) {
    return obj.centerY == centerY && obj.centerX == centerX && obj.dimension == dimension;
}

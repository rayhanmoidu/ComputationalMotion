//
//  QuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-02.
//

#include "QuadtreeTiling.hpp"
#include <iostream>
#include <cmath>
#include "Triangle.hpp"
#include <vector>
#include "Quadtree.hpp"

QuadtreeTiling::QuadtreeTiling() {
}

void QuadtreeTiling::createTilingHelper(QuadtreeNode* curNode) {
    vector<QuadtreeNode*> children = curNode->getChildren();
    if (children.size()==0) {
        createTrianglesFromCell(curNode);
    } else {
        for (int i = 0; i < children.size(); i++) createTilingHelper(children[i]);
    }
}

void QuadtreeTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    cout<<" should never be called " << endl;
}

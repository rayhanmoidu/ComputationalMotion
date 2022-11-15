//
//  EquilateralQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "EquilateralQuadtreeTiling.hpp"

EquilateralQuadtreeTiling::EquilateralQuadtreeTiling(Quadtree tree) : QuadtreeTiling(tree) {
    createTilingHelper(tree.getRoot());
    satisfyJunctions();
}

void EquilateralQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
    float val = M_PI / 180;
    float shift = (tan(30*val) * curNode->getDimension());
    Point ULCorner((curNode->getCenterX() - curNode->getDimension() / 2) + shift, curNode->getCenterY() - curNode->getDimension() / 2);
    Point URCorner((curNode->getCenterX() + curNode->getDimension() / 2) + shift, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BLCorner((curNode->getCenterX() - curNode->getDimension() / 2), curNode->getCenterY() + curNode->getDimension() / 2);
    Point BRCorner((curNode->getCenterX() + curNode->getDimension() / 2), curNode->getCenterY() + curNode->getDimension() / 2);

    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);

    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(URCorner, BRCorner, ULCorner);

    vector<float> angles1 = t1.computeAngles();
    vector<float> angles2 = t2.computeAngles();

    triangles.push_back(t1);
    triangles.push_back(t2);
}

void EquilateralQuadtreeTiling::satisfyJunctions() {
    // todo
}

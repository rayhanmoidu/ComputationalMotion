//
//  IsoscelesDoubleQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "IsoscelesDoubleQuadtreeTiling.hpp"

IsoscelesDoubleQuadtreeTiling::IsoscelesDoubleQuadtreeTiling(Quadtree tree) : QuadtreeTiling(tree) {
    createTilingHelper(tree.getRoot());
    satisfyJunctions();
}

void IsoscelesDoubleQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
    Point ULCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point URCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BLCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point BRCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point center(curNode->getCenterX(), curNode->getCenterY());

    Triangle t1(ULCorner, URCorner, center);
    Triangle t2(ULCorner, BLCorner, center);
    Triangle t3(URCorner, BRCorner, center);
    Triangle t4(BLCorner, BRCorner, center);

    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    addVertex(center);

    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
}

void IsoscelesDoubleQuadtreeTiling::satisfyJunctions() {
    // todo
}

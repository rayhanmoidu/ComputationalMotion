//
//  IsoscelesDoubleQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "IsoscelesDoubleQuadtreeTiling.hpp"

IsoscelesDoubleQuadtreeTiling::IsoscelesDoubleQuadtreeTiling(SquareQuadtree tree) : QuadtreeTiling() {
    createTilingHelper(tree.getRoot());
}

void IsoscelesDoubleQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {    
    Point ULCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point URCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point BLCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BRCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point center(curNode->getCenterX(), curNode->getCenterY());

    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    if (northNeighbours.size()>1) {
        Point northMP((ULCorner.getX() + URCorner.getX()) / 2, ULCorner.getY());
        Triangle t1(ULCorner, northMP, center);
        Triangle t2(URCorner, northMP, center);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(ULCorner, URCorner, center);
        triangles.push_back(t1);
    }
    
    if (southNeighbours.size()>1) {
        Point southMP((BLCorner.getX() + BRCorner.getX()) / 2, BLCorner.getY());
        Triangle t1(BLCorner, southMP, center);
        Triangle t2(BRCorner, southMP, center);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(BLCorner, BRCorner, center);
        triangles.push_back(t1);
    }
    
    if (westNeighbours.size()>1) {
        Point westMP(ULCorner.getX(), (ULCorner.getY() + BLCorner.getY()) / 2);
        Triangle t1(ULCorner, westMP, center);
        Triangle t2(BLCorner, westMP, center);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(ULCorner, BLCorner, center);
        triangles.push_back(t1);
    }
    
    if (eastNeighbours.size()>1) {
        Point eastMP(URCorner.getX(), (URCorner.getY() + BRCorner.getY()) / 2);
        Triangle t1(URCorner, eastMP, center);
        Triangle t2(BRCorner, eastMP, center);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(BRCorner, URCorner, center);
        triangles.push_back(t1);
    }
    
    
}

void IsoscelesDoubleQuadtreeTiling::satisfyJunctions() {
}

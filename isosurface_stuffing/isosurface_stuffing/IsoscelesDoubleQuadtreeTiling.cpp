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
    Point northMP((ULCorner.getX() + URCorner.getX()) / 2, ULCorner.getY());
    Point southMP((BLCorner.getX() + BRCorner.getX()) / 2, BLCorner.getY());
    Point westMP(ULCorner.getX(), (ULCorner.getY() + BLCorner.getY()) / 2);
    Point eastMP(URCorner.getX(), (URCorner.getY() + BRCorner.getY()) / 2);
    
    int ULCornerIndex = check_addVertex_getIndex(ULCorner);
    int URCornerIndex = check_addVertex_getIndex(URCorner);
    int BLCornerIndex = check_addVertex_getIndex(BLCorner);
    int BRCornerIndex = check_addVertex_getIndex(BRCorner);
    int centerIndex = check_addVertex_getIndex(center);
    int northMPIndex = check_addVertex_getIndex(northMP);
    int southMPIndex = check_addVertex_getIndex(southMP);
    int westMPIndex = check_addVertex_getIndex(westMP);
    int eastMPIndex = check_addVertex_getIndex(eastMP);
    
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    if (northNeighbours.size()>1) {
        Triangle t1(center, northMP, ULCorner, centerIndex, northMPIndex, ULCornerIndex);
        Triangle t2(center, URCorner, northMP, centerIndex, URCornerIndex, northMPIndex);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(center, URCorner, ULCorner, centerIndex, URCornerIndex, ULCornerIndex);
        triangles.push_back(t1);
    }
    
    if (southNeighbours.size()>1) {
        Triangle t1(BLCorner, southMP, center, BLCornerIndex, southMPIndex, centerIndex);
        Triangle t2(southMP, BRCorner, center, southMPIndex, BRCornerIndex, centerIndex);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(BLCorner, BRCorner, center, BLCornerIndex, BRCornerIndex, centerIndex);
        triangles.push_back(t1);
    }
    
    if (westNeighbours.size()>1) {
        Triangle t1(westMP, center, ULCorner, westMPIndex, centerIndex, ULCornerIndex);
        Triangle t2(BLCorner, center, westMP, BLCornerIndex, centerIndex, westMPIndex);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(BLCorner, center, ULCorner, BLCornerIndex, centerIndex, ULCornerIndex);
        triangles.push_back(t1);
    }
    
    if (eastNeighbours.size()>1) {
        Triangle t1(center, eastMP, URCorner, centerIndex, eastMPIndex, URCornerIndex);
        Triangle t2(BRCorner, eastMP, center, BRCornerIndex, eastMPIndex, centerIndex);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        Triangle t1(BRCorner, URCorner, center, BRCornerIndex, URCornerIndex, centerIndex);
        triangles.push_back(t1);
    }
    
    
}

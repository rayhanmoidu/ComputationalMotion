//
//  IsoscelesSingleQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "IsoscelesSingleQuadtreeTiling.hpp"

IsoscelesSingleQuadtreeTiling::IsoscelesSingleQuadtreeTiling(SquareQuadtree tree) : QuadtreeTiling() {
    createTilingHelper(tree.getRoot());
}

void IsoscelesSingleQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
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
    
    if (eastNeighbours.size()>1) {
        if (southNeighbours.size()>1) {
            // east + south
            Triangle t1(BLCorner, southMP, URCorner, BLCornerIndex, southMPIndex, BLCornerIndex);
            Triangle t2(southMP, eastMP, URCorner, southMPIndex, eastMPIndex, URCornerIndex);
            Triangle t3(BRCorner, southMP, eastMP, BRCornerIndex, southMPIndex, eastMPIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        } else {
            // east
            Triangle t1(BLCorner, eastMP, URCorner, BLCornerIndex, eastMPIndex, URCornerIndex);
            Triangle t2(BLCorner, BRCorner, eastMP, BLCornerIndex, BRCornerIndex, eastMPIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    } else {
        if (southNeighbours.size()>1) {
            // south
            Triangle t1(BLCorner, southMP, URCorner, BLCornerIndex, southMPIndex, URCornerIndex);
            Triangle t2(southMP, BRCorner, URCorner, southMPIndex, BRCornerIndex, URCornerIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
        } else {
            // neither
            Triangle t1(BLCorner, BRCorner, URCorner, BLCornerIndex, BRCornerIndex, URCornerIndex);
            triangles.push_back(t1);
        }
    }
    
    if (westNeighbours.size()>1) {
        if (northNeighbours.size()>1) {
            // west + north
            Triangle t1(BLCorner, URCorner, northMP, BLCornerIndex, URCornerIndex, northMPIndex);
            Triangle t2(BLCorner, northMP, westMP, BLCornerIndex, northMPIndex, westMPIndex);
            Triangle t3(northMP, ULCorner, westMP, northMPIndex, ULCornerIndex, westMPIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        } else {
            // west
            Triangle t1(BLCorner, URCorner, westMP, BLCornerIndex, URCornerIndex, westMPIndex);
            Triangle t2(URCorner, ULCorner, westMP, URCornerIndex, ULCornerIndex, westMPIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    } else {
        if (northNeighbours.size()>1) {
            // north
            Triangle t1(BLCorner, URCorner, northMP, BLCornerIndex, URCornerIndex, northMPIndex);
            Triangle t2(BLCorner, northMP, ULCorner, BLCornerIndex, northMPIndex, ULCornerIndex);
            
            triangles.push_back(t1);
            triangles.push_back(t2);
        } else {
            // neither
            Triangle t1(BLCorner, URCorner, ULCorner, BLCornerIndex, URCornerIndex, ULCornerIndex);
            triangles.push_back(t1);
        }
    }
    
    
}

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
    
    int ULCornerIndex = 0;
    int URCornerIndex = 0;
    int BLCornerIndex = 0;
    int BRCornerIndex = 0;
    int centerIndex = 0;
    int northMPIndex = 0;
    int southMPIndex = 0;
    int westMPIndex = 0;
    int eastMPIndex = 0;
    
    if (verticesSet.count(pair<float, float>(ULCorner.getX(), ULCorner.getY()))) {
        ULCornerIndex = findVertexIndex(ULCorner);
    } else {
        addVertex(ULCorner);
        ULCornerIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(URCorner.getX(), URCorner.getY()))) {
        URCornerIndex = findVertexIndex(URCorner);
    } else {
        addVertex(URCorner);
        URCornerIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(BLCorner.getX(), BLCorner.getY()))) {
        BLCornerIndex = findVertexIndex(BLCorner);
    } else {
        addVertex(BLCorner);
        BLCornerIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(BRCorner.getX(), BRCorner.getY()))) {
        BRCornerIndex = findVertexIndex(BRCorner);
    } else {
        addVertex(BRCorner);
        BRCornerIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(center.getX(), center.getY()))) {
        centerIndex = findVertexIndex(center);
    } else {
        addVertex(center);
        centerIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(northMP.getX(), northMP.getY()))) {
        northMPIndex = findVertexIndex(northMP);
    } else {
        addVertex(northMP);
        northMPIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(southMP.getX(), southMP.getY()))) {
        southMPIndex = findVertexIndex(southMP);
    } else {
        addVertex(southMP);
        southMPIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(westMP.getX(), westMP.getY()))) {
        westMPIndex = findVertexIndex(westMP);
    } else {
        addVertex(westMP);
        westMPIndex = int(vertices.size() - 1);
    }
    
    if (verticesSet.count(pair<float, float>(eastMP.getX(), eastMP.getY()))) {
        eastMPIndex = findVertexIndex(eastMP);
    } else {
        addVertex(eastMP);
        eastMPIndex = int(vertices.size() - 1);
    }
    
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

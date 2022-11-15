//
//  QuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-02.
//

#include "QuadtreeTiling.hpp"
#include <iostream>
#include <cmath>

QuadtreeTiling::QuadtreeTiling(Quadtree quadtree, QuadtreeTilingType tilingType) {
    createTilingHelper(quadtree.getRoot(), tilingType);
}

void QuadtreeTiling::createTilingHelper(QuadtreeNode* curNode, QuadtreeTilingType tilingType) {
    if (curNode->children.size()==0) {
        if (tilingType==isoscelesSingle) createTrianglesFromCell_isoscelesSingle(curNode);
        if (tilingType==isoscelesDouble) createTrianglesFromCell_isoscelesDouble(curNode);
        if (tilingType==equilateral) createTrianglesFromCell_equilateral(curNode);
        if (tilingType==provablyGood) createTrianglesFromCell_provablyGood(curNode);
    } else {
        for (int i = 0; i < curNode->children.size(); i++) createTilingHelper(&(curNode->children[i]), tilingType);
    }
}

void QuadtreeTiling::createTrianglesFromCell_isoscelesSingle(QuadtreeNode *curNode) {
    Point ULCorner(curNode->centerX - curNode->dimension / 2, curNode->centerY - curNode->dimension / 2);
    Point URCorner(curNode->centerX + curNode->dimension / 2, curNode->centerY - curNode->dimension / 2);
    Point BLCorner(curNode->centerX - curNode->dimension / 2, curNode->centerY + curNode->dimension / 2);
    Point BRCorner(curNode->centerX + curNode->dimension / 2, curNode->centerY + curNode->dimension / 2);
    
    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(URCorner, BRCorner, ULCorner);
    
    triangles.push_back(t1);
    triangles.push_back(t2);
}

void QuadtreeTiling::createTrianglesFromCell_isoscelesDouble(QuadtreeNode *curNode) {
    Point ULCorner(curNode->centerX - curNode->dimension / 2, curNode->centerY - curNode->dimension / 2);
    Point URCorner(curNode->centerX + curNode->dimension / 2, curNode->centerY - curNode->dimension / 2);
    Point BLCorner(curNode->centerX - curNode->dimension / 2, curNode->centerY + curNode->dimension / 2);
    Point BRCorner(curNode->centerX + curNode->dimension / 2, curNode->centerY + curNode->dimension / 2);
    Point center(curNode->centerX, curNode->centerY);
    
    Triangle t1(ULCorner, URCorner, center);
    Triangle t2(ULCorner, BLCorner, center);
    Triangle t3(URCorner, BRCorner, center);
    Triangle t4(BLCorner, BRCorner, center);
    
    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
}

void QuadtreeTiling::createTrianglesFromCell_equilateral(QuadtreeNode *curNode) {
    //todo
    float val = M_PI / 180;
    float shift = (tan(30*val) * curNode->dimension);
    Point ULCorner((curNode->centerX - curNode->dimension / 2) + shift, curNode->centerY - curNode->dimension / 2);
    Point URCorner((curNode->centerX + curNode->dimension / 2) + shift, curNode->centerY - curNode->dimension / 2);
    Point BLCorner((curNode->centerX - curNode->dimension / 2), curNode->centerY + curNode->dimension / 2);
    Point BRCorner((curNode->centerX + curNode->dimension / 2), curNode->centerY + curNode->dimension / 2);
    
    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(URCorner, BRCorner, ULCorner);
    
    vector<float> angles1 = t1.computeAngles();
    vector<float> angles2 = t2.computeAngles();

    triangles.push_back(t1);
    triangles.push_back(t2);
}

void QuadtreeTiling::createTrianglesFromCell_provablyGood(QuadtreeNode *curNode) {
    //todo
}

void QuadtreeTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    cout<<" should never be called " << endl;
}

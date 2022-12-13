//
//  EquilateralQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "EquilateralQuadtreeTiling.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

EquilateralQuadtreeTiling::EquilateralQuadtreeTiling(ParallelogramQuadtree tree) : QuadtreeTiling() {
    rebalanceQuadtree(tree);
    createTilingHelper(tree.getRoot());
}

void EquilateralQuadtreeTiling::rebalanceQuadtree(ParallelogramQuadtree tree) {
    vector<QuadtreeNode*> leavesToProcess = tree.getListOfLeaves();
    while(leavesToProcess.size() > 0) {
        QuadtreeNode* curLeaf = leavesToProcess[0];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbours = curLeaf->getNeighbours(north);
        vector<QuadtreeNode*> southNeighbours = curLeaf->getNeighbours(south);
        vector<QuadtreeNode*> eastNeighbours = curLeaf->getNeighbours(east);
        vector<QuadtreeNode*> westNeighbours = curLeaf->getNeighbours(west);
        
        int numSmallerNeighbours = 0;
        if (northNeighbours.size()>1) numSmallerNeighbours++;
        if (eastNeighbours.size()>1) numSmallerNeighbours++;
        if (westNeighbours.size()>1) numSmallerNeighbours++;
        if (southNeighbours.size()>1) numSmallerNeighbours++;

        neighbors.insert(neighbors.end(), northNeighbours.begin(), northNeighbours.end());
        neighbors.insert(neighbors.end(), southNeighbours.begin(), southNeighbours.end());
        neighbors.insert(neighbors.end(), eastNeighbours.begin(), eastNeighbours.end());
        neighbors.insert(neighbors.end(), westNeighbours.begin(), westNeighbours.end());
        
        bool mustRefineCurLeaf = false;
        QuadtreeNode* neighbourToAdd = NULL;
        
        if (numSmallerNeighbours==4) mustRefineCurLeaf = true;
        if (numSmallerNeighbours==3) {
            mustRefineCurLeaf = true;
            if (northNeighbours.size()==1) neighbourToAdd = northNeighbours[0];
            if (eastNeighbours.size()==1) neighbourToAdd = eastNeighbours[0];
            if (westNeighbours.size()==1) neighbourToAdd = westNeighbours[0];
            if (southNeighbours.size()==1) neighbourToAdd = southNeighbours[0];
        }

        if (mustRefineCurLeaf) {
            tree.refineNode(curLeaf);
            if (neighbourToAdd != NULL) leavesToProcess.push_back(neighbourToAdd);
            for (int i = 0; i < neighbors.size(); i++) leavesToProcess.push_back(neighbors[i]);
        }
        leavesToProcess = tree.removeNodeFromVector(leavesToProcess, curLeaf);
    }
}

void EquilateralQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
    float height = sqrt(3) * curNode->getDimension()/2;
    
    Point ULCorner((curNode->getCenterX() - curNode->getDimension() / 4), curNode->getCenterY() + height / 2);
    Point URCorner((curNode->getCenterX() + 3*curNode->getDimension() / 4), curNode->getCenterY() + height / 2);
    Point BLCorner((curNode->getCenterX() - 3*curNode->getDimension() / 4), curNode->getCenterY() - height / 2);
    Point BRCorner((curNode->getCenterX() + curNode->getDimension() / 4), curNode->getCenterY() - height / 2);
    Point northMP((ULCorner.getX() + URCorner.getX()) / 2, (ULCorner.getY() + URCorner.getY()) / 2);
    Point southMP((BLCorner.getX() + BRCorner.getX()) / 2, (BLCorner.getY() + BRCorner.getY()) / 2);
    Point eastMP((BRCorner.getX() + URCorner.getX()) / 2, (BRCorner.getY() + URCorner.getY()) / 2);
    Point westMP((ULCorner.getX() + BLCorner.getX()) / 2, (ULCorner.getY() + BLCorner.getY()) / 2);
    Point middleMP((BRCorner.getX() + ULCorner.getX()) / 2, (BRCorner.getY() + ULCorner.getY()) / 2);
    
    int ULCornerIndex = check_addVertex_getIndex(ULCorner);
    int URCornerIndex = check_addVertex_getIndex(URCorner);
    int BLCornerIndex = check_addVertex_getIndex(BLCorner);
    int BRCornerIndex = check_addVertex_getIndex(BRCorner);
    int middleMPIndex = check_addVertex_getIndex(middleMP);
    int northMPIndex = check_addVertex_getIndex(northMP);
    int southMPIndex = check_addVertex_getIndex(southMP);
    int westMPIndex = check_addVertex_getIndex(westMP);
    int eastMPIndex = check_addVertex_getIndex(eastMP);

    
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    int numSmallerNeighbours = 0;
    if (northNeighbours.size()>1) numSmallerNeighbours++;
    if (eastNeighbours.size()>1) numSmallerNeighbours++;
    if (westNeighbours.size()>1) numSmallerNeighbours++;
    if (southNeighbours.size()>1) numSmallerNeighbours++;
    
    if (numSmallerNeighbours==3 || numSmallerNeighbours==4) {cout<<"UNEXPECTED"<<endl;}
    
    if (numSmallerNeighbours==1) {
        if (northNeighbours.size()>1) {
            Triangle t1(BRCornerIndex, URCornerIndex, northMPIndex);
            Triangle t2(BRCornerIndex, ULCornerIndex, northMPIndex);
            Triangle t3(BLCornerIndex, BRCornerIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (southNeighbours.size()>1) {
            Triangle t1(BLCornerIndex, southMPIndex, ULCornerIndex);
            Triangle t2(southMPIndex, BRCornerIndex, ULCornerIndex);
            Triangle t3(URCornerIndex, BRCornerIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (eastNeighbours.size()>1) {
            Triangle t1(eastMPIndex, URCornerIndex, ULCornerIndex);
            Triangle t2(BRCornerIndex, eastMPIndex, ULCornerIndex);
            Triangle t3(BLCornerIndex, BRCornerIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (westNeighbours.size()>1) {
            Triangle t1(BLCornerIndex, BRCornerIndex, westMPIndex);
            Triangle t2(BRCornerIndex, westMPIndex, ULCornerIndex);
            Triangle t3(BRCornerIndex, URCornerIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
    } else if (numSmallerNeighbours==2) {
        if (northNeighbours.size()>1 && eastNeighbours.size()>1) {
            Triangle t1(eastMPIndex, URCornerIndex, northMPIndex);
            Triangle t2(middleMPIndex, BRCornerIndex, eastMPIndex);
            Triangle t3(middleMPIndex, northMPIndex, ULCornerIndex);
            Triangle t4(middleMPIndex, eastMPIndex, northMPIndex);
            Triangle t5(BLCornerIndex, middleMPIndex, ULCornerIndex);
            Triangle t6(BLCornerIndex, BRCornerIndex, middleMPIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
            triangles.push_back(t5);
            triangles.push_back(t6);
        } else if (northNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(BRCornerIndex, URCornerIndex, northMPIndex);
            Triangle t2(BRCornerIndex, northMPIndex, ULCornerIndex);
            Triangle t3(southMPIndex, BRCornerIndex, ULCornerIndex);
            Triangle t4(BLCornerIndex, southMPIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (northNeighbours.size()>1 && westNeighbours.size()>1) {
            Triangle t1(BRCornerIndex, URCornerIndex, northMPIndex);
            Triangle t2(BRCornerIndex, northMPIndex, ULCornerIndex);
            Triangle t3(BRCornerIndex, westMPIndex, ULCornerIndex);
            Triangle t4(BLCornerIndex, BRCornerIndex, westMPIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (eastNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(eastMPIndex, URCornerIndex, ULCornerIndex);
            Triangle t2(BRCornerIndex, eastMPIndex, ULCornerIndex);
            Triangle t3(southMPIndex, BRCornerIndex, ULCornerIndex);
            Triangle t4(BLCornerIndex, southMPIndex, ULCornerIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (eastNeighbours.size()>1 && westNeighbours.size()>1) {
            Triangle t1(eastMPIndex, URCornerIndex, ULCornerIndex);
            Triangle t2(BRCornerIndex, eastMPIndex, ULCornerIndex);
            Triangle t3(BRCornerIndex, ULCornerIndex, westMPIndex);
            Triangle t4(BLCornerIndex, BRCornerIndex, westMPIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (westNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(middleMPIndex, URCornerIndex, ULCornerIndex);
            Triangle t2(BRCornerIndex, URCornerIndex, middleMPIndex);
            Triangle t3(southMPIndex, BRCornerIndex, middleMPIndex);
            Triangle t4(BLCornerIndex, southMPIndex, westMPIndex);
            Triangle t5(westMPIndex, middleMPIndex, ULCornerIndex);
            Triangle t6(southMPIndex, middleMPIndex, westMPIndex);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
            triangles.push_back(t5);
            triangles.push_back(t6);
        }
    } else if (numSmallerNeighbours==0) {
        Triangle t1(BRCornerIndex, URCornerIndex, ULCornerIndex);
        Triangle t2(BLCornerIndex, BRCornerIndex, ULCornerIndex);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        cout <<"ERROR"<<numSmallerNeighbours<<endl;
    }
}

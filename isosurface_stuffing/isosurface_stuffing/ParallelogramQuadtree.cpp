//
//  ParallelogramQuadtree.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "ParallelogramQuadtree.hpp"
#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "CircleIsosurface.hpp"

ParallelogramQuadtree::ParallelogramQuadtree(int screenWidth, int screenHeight, int smallestGridSize, Isosurface &isosurface) : Quadtree(isosurface) {
    hBound = screenWidth;
    vBound = screenHeight;
    gridSizeLimit = smallestGridSize;
    refineAroundIsosurface = true;
    
    float newH = 4*hBound/3;
    
    float curDimension = 2*newH/sqrt(3);
    float curCenterX = hBound/2;
    float curCenterY = hBound/2;

    root = new QuadtreeNode(curCenterX, curCenterY, curDimension, NULL);

    if (shouldRefine(root)) {
        constructChildren(root);
    }
    balanceQuadtree();
    
    if (isBalanced()) {
        cout <<"correctly balanced!"<<endl;
    } else {
        cout <<"ERROR incorrectly balanced!"<<endl;
    }
}

ParallelogramQuadtree::ParallelogramQuadtree(int screenWidth, int screenHeight, int smallestGridSize, int cellToTraingleSizeRatio, float (*func)(float, float), int probingValue) : Quadtree() {
    hBound = screenWidth;
    vBound = screenHeight;
    gridSizeLimit = smallestGridSize;
    refineAroundIsosurface = false;
    tilingCellSizeToMaxTriangleSizeRatio = cellToTraingleSizeRatio;
    sizingFunction = func;
    probingDistance = probingValue;


    root = new QuadtreeNode(hBound / 2, vBound / 2, hBound, NULL);

    if (shouldRefine(root)) {
        constructChildren(root);
    }
    balanceQuadtree();
    
    if (isBalanced()) {
        cout <<"correctly balanced!"<<endl;
    } else {
        cout <<"ERROR incorrectly balanced!"<<endl;
    }
}

void ParallelogramQuadtree::constructChildren(QuadtreeNode *node) {
    
    float shiftX = (node->getDimension() / 2) * (tan60) / (tan30+tan60);
    float shiftY = shiftX*tan30;
    
    float newCurX1 = node->getCenterX() - node->getDimension() / 4;
    float newCurY1 = node->getCenterY() - getCellHeight(node)/2;
    
    float newCurX2 = node->getCenterX() + node->getDimension() / 4;
    float newCurY2 = node->getCenterY() + getCellHeight(node)/2;
    
    QuadtreeNode* northEastChild = new QuadtreeNode(node->getCenterX() + shiftX, node->getCenterY() + shiftY, node->getDimension() / 2, node);
    QuadtreeNode* northWestChild = new QuadtreeNode(newCurX2 - shiftX, newCurY2 - shiftY, node->getDimension() / 2, node);
    QuadtreeNode* southEastChild = new QuadtreeNode(newCurX1 + shiftX, newCurY1 + shiftY, node->getDimension() / 2, node);
    QuadtreeNode* southWestChild = new QuadtreeNode(node->getCenterX() - shiftX, node->getCenterY() - shiftY, node->getDimension() / 2, node);

    if (shouldRefine(northEastChild)) constructChildren(northEastChild);
    if (shouldRefine(northWestChild)) constructChildren(northWestChild);
    if (shouldRefine(southEastChild)) constructChildren(southEastChild);
    if (shouldRefine(southWestChild)) constructChildren(southWestChild);

    node->addChild(northEastChild, northeast);
    node->addChild(northWestChild, northwest);
    node->addChild(southEastChild, southeast);
    node->addChild(southWestChild, southwest);
}

bool ParallelogramQuadtree::shouldRefine(QuadtreeNode* node) {
    if (refineAroundIsosurface) {
        float diagonalLength = (2*(getCellHeight(node)));

        Point corner1(node->getCenterX() + (node->getDimension()/2), node->getCenterY() + (node->getDimension()/2));
        Point corner2(node->getCenterX() - (node->getDimension()/2), node->getCenterY() + (node->getDimension()/2));
        Point corner3(node->getCenterX() + (node->getDimension()/2), node->getCenterY() - (node->getDimension()/2));
        Point corner4(node->getCenterX() - (node->getDimension()/2), node->getCenterY() - (node->getDimension()/2));

        if (node->getDimension() < gridSizeLimit) return false;
        if (abs(isosurface.signedDistanceFunction(corner1)) > diagonalLength) return false;
        if (abs(isosurface.signedDistanceFunction(corner4)) > diagonalLength) return false;
        if (abs(isosurface.signedDistanceFunction(corner2)) > diagonalLength) return false;
        if (abs(isosurface.signedDistanceFunction(corner3)) > diagonalLength) return false;
        return true;
    } else {
        Point curProbePoint(node->getCenterX() - (node->getDimension() / 2), node->getCenterY() + (node->getDimension() / 2));
        
        bool shouldRefine = false;
        while (curProbePoint.getY() >= node->getCenterY() - (node->getDimension() / 2)) {
            // TEST PROBE POINT
            float maxTriangleSideLength = sizingFunction(curProbePoint.getX(), curProbePoint.getY());
            
            if (maxTriangleSideLength < node->getDimension()/tilingCellSizeToMaxTriangleSizeRatio) {
                shouldRefine = true;
                break;
            }
            
            // ADJUST PROBE POINT
            float newX = curProbePoint.getX() + probingDistance;
            float newY = curProbePoint.getY();
            if (newX > node->getCenterX() + (node->getDimension() / 2)) {
                newX = node->getCenterX() - (node->getDimension() / 2);
                newY = curProbePoint.getY() - probingDistance;
            }
            Point newProbePoint(newX, newY);
            curProbePoint = newProbePoint;
        }
        return shouldRefine;
    }
}

void ParallelogramQuadtree::render() {
    glColor3f(1, 1, 1);
    renderHelper(root);
}

void ParallelogramQuadtree::renderHelper(QuadtreeNode* curNode) {
    if (curNode->numChildren() != 0) {
        glBegin(GL_LINES);
            glVertex2f(curNode->getCenterX() - curNode->getDimension()/2, curNode->getCenterY());
            glVertex2f(curNode->getCenterX() + curNode->getDimension()/2, curNode->getCenterY());
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(curNode->getCenterX() - curNode->getDimension()/4, curNode->getCenterY() - getCellHeight(curNode) / 2);
            glVertex2f(curNode->getCenterX() + curNode->getDimension()/4, curNode->getCenterY() + getCellHeight(curNode) / 2);
        glEnd();
    }

    vector<QuadtreeNode*> curChildren = curNode->getChildren();
    for (int i = 0; i < curChildren.size(); i++) {
        renderHelper(curChildren[i]);
    }
}

//void ParallelogramQuadtree::renderHelper2(QuadtreeNode* curNode, int count) {
//    if (curNode->numChildren() != 0 && count <= 100) {
////    if (count<=9) {
////        cout<<count<<endl;
////        cout << curNode->getDimension()<<endl;
//        glColor3f(float(1/float(count)), float(1/float(count))*2, float(1/float(count))*3);
//        glBegin(GL_LINES);
//            glVertex2f(curNode->getCenterX() - curNode->getDimension()/2, curNode->getCenterY());
//            glVertex2f(curNode->getCenterX() + curNode->getDimension()/2, curNode->getCenterY());
//        glEnd();
//        glColor3f(float(1/float(count)), float(1/float(count))*2, float(1/float(count))*3);
//        glBegin(GL_LINES);
//            glVertex2f(curNode->getCenterX() - curNode->getDimension()/4, curNode->getCenterY() - getCellHeight(curNode) / 2);
//            glVertex2f(curNode->getCenterX() + curNode->getDimension()/4, curNode->getCenterY() + getCellHeight(curNode) / 2);
//        glEnd();
////        glColor3f(float(1/float(count)), float(1/float(count))*2, float(1/float(count))*3);
////        glBegin(GL_QUADS);
////            glVertex2f(curNode->getCenterX() - 4, curNode->getCenterY() - 4);
////            glVertex2f(curNode->getCenterX() + 4, curNode->getCenterY() - 4);
////            glVertex2f(curNode->getCenterX() + 4, curNode->getCenterY() + 4);
////            glVertex2f(curNode->getCenterX() - 4, curNode->getCenterY() + 4);
////        glEnd();
//    }
//
//    vector<QuadtreeNode*> curChildren = curNode->getChildren();
//    for (int i = 0; i < curChildren.size(); i++) {
//        renderHelper2(curChildren[i], count+1);
//    }
//}

float ParallelogramQuadtree::getCellHeight(QuadtreeNode* curNode) {
    return sqrt(3)*curNode->getDimension()/2;
}

void ParallelogramQuadtree::colorSquare(QuadtreeNode node) {
    glBegin(GL_QUADS);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
    glEnd();
}

void ParallelogramQuadtree::refineNode(QuadtreeNode* node) {
    float shiftX = (node->getDimension() / 2) * (tan60) / (tan30+tan60);
    float shiftY = shiftX*tan30;
    
    float newCurX1 = node->getCenterX() - node->getDimension() / 4;
    float newCurY1 = node->getCenterY() - getCellHeight(node)/2;
    
    float newCurX2 = node->getCenterX() + node->getDimension() / 4;
    float newCurY2 = node->getCenterY() + getCellHeight(node)/2;
    
    QuadtreeNode* northEastChild = new QuadtreeNode(node->getCenterX() + shiftX, node->getCenterY() + shiftY, node->getDimension() / 2, node);
    QuadtreeNode* northWestChild = new QuadtreeNode(newCurX2 - shiftX, newCurY2 - shiftY, node->getDimension() / 2, node);
    QuadtreeNode* southEastChild = new QuadtreeNode(newCurX1 + shiftX, newCurY1 + shiftY, node->getDimension() / 2, node);
    QuadtreeNode* southWestChild = new QuadtreeNode(node->getCenterX() - shiftX, node->getCenterY() - shiftY, node->getDimension() / 2, node);

    node->addChild(northEastChild, northeast);
    node->addChild(northWestChild, northwest);
    node->addChild(southEastChild, southeast);
    node->addChild(southWestChild, southwest);
}



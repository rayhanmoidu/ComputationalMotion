//
//  SquareQuadtree.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "SquareQuadtree.hpp"
#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "CircleIsosurface.hpp"

SquareQuadtree::SquareQuadtree(int screenWidth, int screenHeight, int smallestGridSize, Isosurface &isosurface) : Quadtree(isosurface) {
    hBound = screenWidth;
    vBound = screenHeight;
    gridSizeLimit = smallestGridSize;

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

void SquareQuadtree::constructChildren(QuadtreeNode *node) {
    QuadtreeNode* northEastChild = new QuadtreeNode(node->getCenterX() + node->getDimension()/4, node->getCenterY() + node->getDimension()/4, node->getDimension() / 2, node);
    QuadtreeNode* northWestChild = new QuadtreeNode(node->getCenterX() - node->getDimension()/4, node->getCenterY() + node->getDimension()/4, node->getDimension() / 2, node);
    QuadtreeNode* southEastChild = new QuadtreeNode(node->getCenterX() + node->getDimension()/4, node->getCenterY() - node->getDimension()/4, node->getDimension() / 2, node);
    QuadtreeNode* southWestChild = new QuadtreeNode(node->getCenterX() - node->getDimension()/4, node->getCenterY() - node->getDimension()/4, node->getDimension() / 2, node);

    if (shouldRefine(northEastChild)) constructChildren(northEastChild);
    if (shouldRefine(northWestChild)) constructChildren(northWestChild);
    if (shouldRefine(southEastChild)) constructChildren(southEastChild);
    if (shouldRefine(southWestChild)) constructChildren(southWestChild);

    node->addChild(northEastChild, northeast);
    node->addChild(northWestChild, northwest);
    node->addChild(southEastChild, southeast);
    node->addChild(southWestChild, southwest);
}

bool SquareQuadtree::shouldRefine(QuadtreeNode* node) {
    float diagonalLength = (sqrt(node->getDimension()*node->getDimension()*2));

    Point corner1(node->getCenterX() + (node->getDimension()/2), node->getCenterY() + (node->getDimension()/2));
    Point corner2(node->getCenterX() - (node->getDimension()/2), node->getCenterY() + (node->getDimension()/2));
    Point corner3(node->getCenterX() + (node->getDimension()/2), node->getCenterY() - (node->getDimension()/2));
    Point corner4(node->getCenterX() - (node->getDimension()/2), node->getCenterY() - (node->getDimension()/2));
//    cout <<"lala" << node->getDimension()<<endl;
    if (node->getDimension() < gridSizeLimit) return false;
    if (abs(isosurface.signedDistanceFunction(corner1)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner4)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner2)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner3)) > diagonalLength) return false;
    return true;
}

void SquareQuadtree::render() {
    glColor3f(1, 1, 1);
    renderHelper(root);
}

void SquareQuadtree::renderHelper(QuadtreeNode* curNode) {
    if (curNode->numChildren() != 0) {
        glBegin(GL_LINES);
            glVertex2f(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY());
            glVertex2f(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY());
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(curNode->getCenterX(), curNode->getCenterY() - curNode->getDimension() / 2);
            glVertex2f(curNode->getCenterX(), curNode->getCenterY() + curNode->getDimension() / 2);
        glEnd();
    }

    vector<QuadtreeNode*> curChildren = curNode->getChildren();
    for (int i = 0; i < curChildren.size(); i++) {
        renderHelper(curChildren[i]);
    }
}

void SquareQuadtree::colorSquare(QuadtreeNode node) {
    glBegin(GL_QUADS);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
    glEnd();
}

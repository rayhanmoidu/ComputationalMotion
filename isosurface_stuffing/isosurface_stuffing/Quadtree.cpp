#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

Quadtree::Quadtree(int screenWidth, int screenHeight, Isosurface &isosurface) :
isosurface(isosurface) {
    hBound = screenWidth;
    vBound = screenHeight;
    root = QuadtreeNode(hBound / 2, vBound / 2, hBound);
    
    if (shouldRefine(root)) {
        constructChildren(&root);
    }
}

void Quadtree::constructChildren(QuadtreeNode *node) {
    QuadtreeNode northEastChild(node->centerX + node->dimension/4, node->centerY + node->dimension/4, node->dimension / 2);
    QuadtreeNode northWestChild(node->centerX - node->dimension/4, node->centerY + node->dimension/4, node->dimension / 2);
    QuadtreeNode southEastChild(node->centerX + node->dimension/4, node->centerY - node->dimension/4, node->dimension / 2);
    QuadtreeNode southWestChild(node->centerX - node->dimension/4, node->centerY - node->dimension/4, node->dimension / 2);
    
    if (shouldRefine(northEastChild)) constructChildren(&northEastChild);
    if (shouldRefine(northWestChild)) constructChildren(&northWestChild);
    if (shouldRefine(southEastChild)) constructChildren(&southEastChild);
    if (shouldRefine(southWestChild)) constructChildren(&southWestChild);
    
    node->addChild(northEastChild);
    node->addChild(northWestChild);
    node->addChild(southEastChild);
    node->addChild(southWestChild);
}

bool Quadtree::shouldRefine(QuadtreeNode node) {
    float diagonalLength = (sqrt(node.dimension*node.dimension*2));
    
    Point corner1(node.centerX + (node.dimension/2), node.centerY + (node.dimension/2));
    Point corner2(node.centerX - (node.dimension/2), node.centerY + (node.dimension/2));
    Point corner3(node.centerX + (node.dimension/2), node.centerY - (node.dimension/2));
    Point corner4(node.centerX - (node.dimension/2), node.centerY - (node.dimension/2));
    
    if (node.dimension < 30) return false;
    if (abs(isosurface.signedDistanceFunction(corner1)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner4)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner2)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner3)) > diagonalLength) return false;
    return true;
}

void Quadtree::render() {
    renderHelper(root);
}

void Quadtree::renderHelper(QuadtreeNode curNode) {
    glBegin(GL_LINES);
        glVertex2f(curNode.centerX - curNode.dimension / 2, curNode.centerY);
        glVertex2f(curNode.centerX + curNode.dimension / 2, curNode.centerY);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(curNode.centerX, curNode.centerY - curNode.dimension / 2);
        glVertex2f(curNode.centerX, curNode.centerY + curNode.dimension / 2);
    glEnd();
    
    for (int i = 0; i < curNode.children.size(); i++) {
        renderHelper(curNode.children[i]);
    }
}


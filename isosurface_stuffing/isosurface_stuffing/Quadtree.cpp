#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

Quadtree::Quadtree(int screenWidth, int screenHeight, int smallestGridSize, Isosurface &isosurface) :
isosurface(isosurface) {
    hBound = screenWidth;
    vBound = screenHeight;
    gridSizeLimit = smallestGridSize;
    root = QuadtreeNode(hBound / 2, vBound / 2, hBound);
    
    if (shouldRefine(root)) {
        constructChildren(&root);
    }
    balanceQuadtree();
    balanceQuadtree();
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
    
    if (node.dimension < gridSizeLimit) return false;
    if (abs(isosurface.signedDistanceFunction(corner1)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner4)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner2)) > diagonalLength) return false;
    if (abs(isosurface.signedDistanceFunction(corner3)) > diagonalLength) return false;
    return true;
}

void Quadtree::render() {
    glColor3f(1, 1, 1);
    renderHelper(root);
}

void Quadtree::renderHelper(QuadtreeNode curNode) {
    if (curNode.children.size()!=0) {
        glBegin(GL_LINES);
            glVertex2f(curNode.centerX - curNode.dimension / 2, curNode.centerY);
            glVertex2f(curNode.centerX + curNode.dimension / 2, curNode.centerY);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(curNode.centerX, curNode.centerY - curNode.dimension / 2);
            glVertex2f(curNode.centerX, curNode.centerY + curNode.dimension / 2);
        glEnd();
    }
    
    for (int i = 0; i < curNode.children.size(); i++) {
        renderHelper(curNode.children[i]);
    }
}

pair<Point, Point> Quadtree::findCellBoundsInDirection(QuadtreeNode curNode, Direction direction) {
    Point p1;
    Point p2;
    if (direction == north) {
        float x1 = curNode.centerX - (curNode.dimension / 2);
        float x2 = curNode.centerX + (curNode.dimension / 2);
        float y = curNode.centerY + (curNode.dimension / 2);
        p1.setX(x1);
        p1.setY(y);
        p2.setX(x2);
        p2.setY(y);
    } else if (direction == south) {
        float x1 = curNode.centerX - (curNode.dimension / 2);
        float x2 = curNode.centerX + (curNode.dimension / 2);
        float y = curNode.centerY - (curNode.dimension / 2);
        p1.setX(x1);
        p1.setY(y);
        p2.setX(x2);
        p2.setY(y);
    } else if (direction == east) {
        float x = curNode.centerX + (curNode.dimension / 2);
        float y1 = curNode.centerY - (curNode.dimension / 2);
        float y2 = curNode.centerY + (curNode.dimension / 2);
        p1.setX(x);
        p1.setY(y1);
        p2.setX(x);
        p2.setY(y2);
    } else if (direction == west) {
        float x = curNode.centerX - (curNode.dimension / 2);
        float y1 = curNode.centerY - (curNode.dimension / 2);
        float y2 = curNode.centerY + (curNode.dimension / 2);
        p1.setX(x);
        p1.setY(y1);
        p2.setX(x);
        p2.setY(y2);
    }
    
    return pair<Point, Point>(p1, p2);
}

void Quadtree::test123() {
    for (int i = 0; i < root.children.size(); i++) {
        QuadtreeNode step1 = root.children[i];
        for (int j = 0; j < step1.children.size(); j++) {
            QuadtreeNode step2 = root.children[i];
            for (int k = 0; k < step2.children.size(); k++) {
                QuadtreeNode step3 = root.children[i];

                for (int l = 0; l < step3.children.size(); l++) {
                    findLeafNeighborsInDirection(step3.children[l], west);
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
}

void colorSquare(QuadtreeNode node) {
    glBegin(GL_QUADS);
        glVertex2f(node.centerX - node.dimension / 2, node.centerY - node.dimension / 2);
        glVertex2f(node.centerX + node.dimension / 2, node.centerY - node.dimension / 2);
        glVertex2f(node.centerX + node.dimension / 2, node.centerY + node.dimension / 2);
        glVertex2f(node.centerX - node.dimension / 2, node.centerY + node.dimension / 2);
    glEnd();
}

vector<QuadtreeNode> Quadtree::findLeafNeighborsInDirection(QuadtreeNode curNode, Direction direction) {
    pair<Point, Point> bounds = findCellBoundsInDirection(curNode, direction);
    
//    glColor3f(1, 0, 0);
//    colorSquare(curNode);
    
    vector<QuadtreeNode> neighborsInDirection;
    neighborsInDirection = neighborsHelper(bounds.first, bounds.second, neighborsInDirection, root, direction);
//    glColor3f(0, 1, 0);
//    for (int i = 0; i < neighborsInDirection.size(); i++) colorSquare(neighborsInDirection[i]);
    
//    QuadtreeNode newNode = neighborsInDirection[1];
//    pair<Point, Point> boundslala = findCellBoundsInDirection(newNode, east);
//    glColor3f(0, 0, 1);
//    colorSquare(newNode);
//    vector<QuadtreeNode>  newNeighbours;
//    newNeighbours = neighborsHelper(boundslala.first, boundslala.second, newNeighbours, root, east);
//    glColor3f(1, 1, 1);
//    for (int i = 0; i < newNeighbours.size(); i++) colorSquare(newNeighbours[i]);
    
    
    return neighborsInDirection;
}

vector<QuadtreeNode> Quadtree::neighborsHelper(Point bound1, Point bound2, vector<QuadtreeNode> foundNeighbors, QuadtreeNode curNode, Direction dir) {
    if (curNode.children.size()!=0) {
        for (int i = 0; i < curNode.children.size(); i++) {
            foundNeighbors = neighborsHelper(bound1, bound2, foundNeighbors, curNode.children[i], dir);
        }
    } else {
        pair<Point, Point> testBounds;
        if (dir==north) {
            testBounds = findCellBoundsInDirection(curNode, south);
            if (testBounds.first.getY()== bound1.getY() && testBounds.second.getY()== bound2.getY()) {
                if (testBounds.first.getX() >= bound1.getX() && testBounds.second.getX() <= bound2.getX()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getX() >= testBounds.first.getX() && bound2.getX() <= testBounds.second.getX()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==south) {
            testBounds = findCellBoundsInDirection(curNode, north);
            if (testBounds.first.getY()== bound1.getY() && testBounds.second.getY()== bound2.getY()) {
                if (testBounds.first.getX() >= bound1.getX() && testBounds.second.getX() <= bound2.getX()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getX() >= testBounds.first.getX() && bound2.getX() <= testBounds.second.getX()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==east) {
            testBounds = findCellBoundsInDirection(curNode, west);
            if (testBounds.first.getX()== bound1.getX() && testBounds.second.getX()== bound2.getX()) {
                if (testBounds.first.getY() >= bound1.getY() && testBounds.second.getY() <= bound2.getY()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getY() >= testBounds.first.getY() && bound2.getY() <= testBounds.second.getY()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==west) {
            testBounds = findCellBoundsInDirection(curNode, east);
            if (testBounds.first.getX()== bound1.getX() && testBounds.second.getX()== bound2.getX()) {
                if (testBounds.first.getY() >= bound1.getY() && testBounds.second.getY() <= bound2.getY()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getY() >= testBounds.first.getY() && bound2.getY() <= testBounds.second.getY()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
    }
    return foundNeighbors;
}

vector<QuadtreeNode*> Quadtree::getListOfLeaves() {
    vector<QuadtreeNode*> leaves;
    leaves = getListOfLeavesHelper(&root, leaves);
    return leaves;
}

vector<QuadtreeNode*> Quadtree::getListOfLeavesHelper(QuadtreeNode* curNode, vector<QuadtreeNode*> leaves) {
    if (curNode->children.size()==0) {
        
        leaves.push_back(curNode);
        return leaves;
    }
    else {
        for (int i = 0; i < curNode->children.size(); i++) {
            vector<QuadtreeNode*> newLeaves = getListOfLeavesHelper(&(curNode->children[i]), leaves);
            leaves = newLeaves;
        }
    }
    return leaves;
}

vector<QuadtreeNode*> removeLeaf(vector<QuadtreeNode*> leaves, QuadtreeNode* leafToRemove) {
    vector<QuadtreeNode*> newLeaves;
    for (int i = 0; i < leaves.size(); i++) {
        if (!(leaves[i] == leafToRemove)) {
            newLeaves.push_back(leaves[i]);
        }
    }
    return newLeaves;
}

bool doesContainLeaf(vector<QuadtreeNode*> leaves, QuadtreeNode leaf) {
    for (int i = 0; i < leaves.size(); i++) {
        if (*leaves[i] == leaf) {
            return true;
        }
    }
    return false;
}


void Quadtree::balanceQuadtree() {
    vector<QuadtreeNode*> hahaha;
    vector<QuadtreeNode*> leaves = getListOfLeaves();
    cout<<leaves.size()<<endl;
    while(leaves.size() > 0) {
        QuadtreeNode* curLeaf = leaves[0];
        
//        cout << curLeaf->dimension << endl;
        cout << "before " << leaves.size() <<endl;
        
        
        vector<QuadtreeNode> neighbors;
        vector<QuadtreeNode> northNeighbors = findLeafNeighborsInDirection(*curLeaf, north);
        vector<QuadtreeNode> southNeighbors = findLeafNeighborsInDirection(*curLeaf, south);
        vector<QuadtreeNode> eastNeighbors = findLeafNeighborsInDirection(*curLeaf, east);
        vector<QuadtreeNode> westNeighbors = findLeafNeighborsInDirection(*curLeaf, west);
        
        neighbors.insert(neighbors.end(), northNeighbors.begin(), northNeighbors.end());
        neighbors.insert(neighbors.end(), southNeighbors.begin(), southNeighbors.end());
        neighbors.insert(neighbors.end(), eastNeighbors.begin(), eastNeighbors.end());
        neighbors.insert(neighbors.end(), westNeighbors.begin(), westNeighbors.end());
        
//        cout << "haha lala " << neighbors.size()<<endl;
//
//
        bool mustRefineCurLeaf = false;
        for (int j = 0; j < neighbors.size(); j++) {
            if (curLeaf->dimension / neighbors[j].dimension > 2) {
                mustRefineCurLeaf = true;
                break;
            }
        }
//
//        cout <<mustRefineCurLeaf<<endl;
//
        if (mustRefineCurLeaf) {
            // refine leaf and add children, along with all neighbours into the list as well
            QuadtreeNode northEastChild(curLeaf->centerX + curLeaf->dimension/4, curLeaf->centerY + curLeaf->dimension/4, curLeaf->dimension / 2);
            QuadtreeNode northWestChild(curLeaf->centerX - curLeaf->dimension/4, curLeaf->centerY + curLeaf->dimension/4, curLeaf->dimension / 2);
            QuadtreeNode southEastChild(curLeaf->centerX + curLeaf->dimension/4, curLeaf->centerY - curLeaf->dimension/4, curLeaf->dimension / 2);
            QuadtreeNode southWestChild(curLeaf->centerX - curLeaf->dimension/4, curLeaf->centerY - curLeaf->dimension/4, curLeaf->dimension / 2);
            curLeaf->addChild(northEastChild);
            curLeaf->addChild(northWestChild);
            curLeaf->addChild(southEastChild);
            curLeaf->addChild(southWestChild);

            leaves.push_back(&northEastChild);
            leaves.push_back(&northWestChild);
            leaves.push_back(&southEastChild);
            leaves.push_back(&southWestChild);

            for (int j = 0; j < neighbors.size(); j++) {
                if (!doesContainLeaf(leaves, neighbors[j])) {
                    hahaha.push_back(&(neighbors[j]));
                }
            }
            cout << "during refining " << leaves.size() <<endl;
        }
        leaves = removeLeaf(leaves, curLeaf);
        cout << "after " << leaves.size() <<endl;
    }
    
    
    
//    while(hahaha.size() > 0) {
//        QuadtreeNode* curLeaf = hahaha[0];
//
////        cout << curLeaf->dimension << endl;
//        cout << "before " << hahaha.size() <<endl;
//
//
//        vector<QuadtreeNode> neighbors;
//        vector<QuadtreeNode> northNeighbors = findLeafNeighborsInDirection(*curLeaf, north);
//        vector<QuadtreeNode> southNeighbors = findLeafNeighborsInDirection(*curLeaf, south);
//        vector<QuadtreeNode> eastNeighbors = findLeafNeighborsInDirection(*curLeaf, east);
//        vector<QuadtreeNode> westNeighbors = findLeafNeighborsInDirection(*curLeaf, west);
//
//        neighbors.insert(neighbors.end(), northNeighbors.begin(), northNeighbors.end());
//        neighbors.insert(neighbors.end(), southNeighbors.begin(), southNeighbors.end());
//        neighbors.insert(neighbors.end(), eastNeighbors.begin(), eastNeighbors.end());
//        neighbors.insert(neighbors.end(), westNeighbors.begin(), westNeighbors.end());
//
////        cout << "haha lala " << neighbors.size()<<endl;
////
////
//        bool mustRefineCurLeaf = false;
//        for (int j = 0; j < neighbors.size(); j++) {
//            if (curLeaf->dimension / neighbors[j].dimension > 2) {
//                mustRefineCurLeaf = true;
//                break;
//            }
//        }
////
////        cout <<mustRefineCurLeaf<<endl;
////
//        if (mustRefineCurLeaf) {
//            // refine leaf and add children, along with all neighbours into the list as well
//            QuadtreeNode northEastChild(curLeaf->centerX + curLeaf->dimension/4, curLeaf->centerY + curLeaf->dimension/4, curLeaf->dimension / 2);
//            QuadtreeNode northWestChild(curLeaf->centerX - curLeaf->dimension/4, curLeaf->centerY + curLeaf->dimension/4, curLeaf->dimension / 2);
//            QuadtreeNode southEastChild(curLeaf->centerX + curLeaf->dimension/4, curLeaf->centerY - curLeaf->dimension/4, curLeaf->dimension / 2);
//            QuadtreeNode southWestChild(curLeaf->centerX - curLeaf->dimension/4, curLeaf->centerY - curLeaf->dimension/4, curLeaf->dimension / 2);
//            curLeaf->addChild(northEastChild);
//            curLeaf->addChild(northWestChild);
//            curLeaf->addChild(southEastChild);
//            curLeaf->addChild(southWestChild);
//
//            hahaha.push_back(&northEastChild);
//            hahaha.push_back(&northWestChild);
//            hahaha.push_back(&southEastChild);
//            hahaha.push_back(&southWestChild);
//
//            for (int j = 0; j < neighbors.size(); j++) {
//                if (!doesContainLeaf(hahaha, neighbors[j])) {
//                    hahaha.push_back(&(neighbors[j]));
//                }
//            }
//            cout << "during refining " << hahaha.size() <<endl;
//        }
//        hahaha = removeLeaf(hahaha, curLeaf);
//        cout << "after " << hahaha.size() <<endl;
//    }
}

// make function to find neighbor (n, s, e, w), will have to return a list of neighbors tbh
// make list of all leaves
// for each leaf, if any neighbor is differing by >1 resolution, refine that current leaf into 4 new leaves. add 4 new leaves to the list
// continue until the list is empty


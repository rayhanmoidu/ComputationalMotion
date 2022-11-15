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

    root = new QuadtreeNode(hBound / 2, vBound / 2, hBound);

    if (shouldRefine(root)) {
        constructChildren(root);
    }
    while (!isBalanced()) balanceQuadtree();
}

void Quadtree::constructChildren(QuadtreeNode *node) {
    QuadtreeNode* northEastChild = new QuadtreeNode(node->getCenterX() + node->getDimension()/4, node->getCenterY() + node->getDimension()/4, node->getDimension() / 2);
    QuadtreeNode* northWestChild = new QuadtreeNode(node->getCenterX() - node->getDimension()/4, node->getCenterY() + node->getDimension()/4, node->getDimension() / 2);
    QuadtreeNode* southEastChild = new QuadtreeNode(node->getCenterX() + node->getDimension()/4, node->getCenterY() - node->getDimension()/4, node->getDimension() / 2);
    QuadtreeNode* southWestChild = new QuadtreeNode(node->getCenterX() - node->getDimension()/4, node->getCenterY() - node->getDimension()/4, node->getDimension() / 2);

    if (shouldRefine(northEastChild)) constructChildren(northEastChild);
    if (shouldRefine(northWestChild)) constructChildren(northWestChild);
    if (shouldRefine(southEastChild)) constructChildren(southEastChild);
    if (shouldRefine(southWestChild)) constructChildren(southWestChild);

    node->addChild(northEastChild, northeast);
    node->addChild(northWestChild, northwest);
    node->addChild(southEastChild, southeast);
    node->addChild(southWestChild, southwest);
}

bool Quadtree::shouldRefine(QuadtreeNode* node) {
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

void Quadtree::render() {
    glColor3f(1, 1, 1);
    renderHelper(root);
}

void Quadtree::renderHelper(QuadtreeNode* curNode) {
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

pair<Point, Point> Quadtree::findCellBoundsInDirection(QuadtreeNode curNode, Direction direction) {
    Point p1;
    Point p2;
    if (direction == north) {
        float x1 = curNode.getCenterX() - (curNode.getDimension() / 2);
        float x2 = curNode.getCenterX() + (curNode.getDimension() / 2);
        float y = curNode.getCenterY() + (curNode.getDimension() / 2);
        p1.setX(x1);
        p1.setY(y);
        p2.setX(x2);
        p2.setY(y);
    } else if (direction == south) {
        float x1 = curNode.getCenterX() - (curNode.getDimension() / 2);
        float x2 = curNode.getCenterX() + (curNode.getDimension() / 2);
        float y = curNode.getCenterY() - (curNode.getDimension() / 2);
        p1.setX(x1);
        p1.setY(y);
        p2.setX(x2);
        p2.setY(y);
    } else if (direction == east) {
        float x = curNode.getCenterX() + (curNode.getDimension() / 2);
        float y1 = curNode.getCenterY() - (curNode.getDimension() / 2);
        float y2 = curNode.getCenterY() + (curNode.getDimension() / 2);
        p1.setX(x);
        p1.setY(y1);
        p2.setX(x);
        p2.setY(y2);
    } else if (direction == west) {
        float x = curNode.getCenterX() - (curNode.getDimension() / 2);
        float y1 = curNode.getCenterY() - (curNode.getDimension() / 2);
        float y2 = curNode.getCenterY() + (curNode.getDimension() / 2);
        p1.setX(x);
        p1.setY(y1);
        p2.setX(x);
        p2.setY(y2);
    }

    return pair<Point, Point>(p1, p2);
}

void colorSquare(QuadtreeNode node) {
    glBegin(GL_QUADS);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
    glEnd();
}

vector<QuadtreeNode*> Quadtree::findLeafNeighborsInDirection(QuadtreeNode* curNode, Direction direction) {
    pair<Point, Point> bounds = findCellBoundsInDirection(*curNode, direction);

    vector<QuadtreeNode*> neighborsInDirection;
    neighborsInDirection = findLeafNeighborsInDirectionHelper(bounds.first, bounds.second, neighborsInDirection, root, direction);

    return neighborsInDirection;
}

vector<QuadtreeNode*> Quadtree::findLeafNeighborsInDirectionHelper(Point bound1, Point bound2, vector<QuadtreeNode*> foundNeighbors, QuadtreeNode* curNode, Direction dir) {
    if (curNode->numChildren()!=0) {
        vector<QuadtreeNode*> curChildren = curNode->getChildren();
        for (int i = 0; i < curChildren.size(); i++) {
            foundNeighbors = findLeafNeighborsInDirectionHelper(bound1, bound2, foundNeighbors, curChildren[i], dir);
        }
    } else {
        pair<Point, Point> testBounds;
        if (dir==north) {
            testBounds = findCellBoundsInDirection(*curNode, south);
            if (testBounds.first.getY()== bound1.getY() && testBounds.second.getY()== bound2.getY()) {
                if (testBounds.first.getX() >= bound1.getX() && testBounds.second.getX() <= bound2.getX()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getX() >= testBounds.first.getX() && bound2.getX() <= testBounds.second.getX()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==south) {
            testBounds = findCellBoundsInDirection(*curNode, north);
            if (testBounds.first.getY()== bound1.getY() && testBounds.second.getY()== bound2.getY()) {
                if (testBounds.first.getX() >= bound1.getX() && testBounds.second.getX() <= bound2.getX()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getX() >= testBounds.first.getX() && bound2.getX() <= testBounds.second.getX()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==east) {
            testBounds = findCellBoundsInDirection(*curNode, west);
            if (testBounds.first.getX()== bound1.getX() && testBounds.second.getX()== bound2.getX()) {
                if (testBounds.first.getY() >= bound1.getY() && testBounds.second.getY() <= bound2.getY()) {
                    foundNeighbors.push_back(curNode);
                } else if (bound1.getY() >= testBounds.first.getY() && bound2.getY() <= testBounds.second.getY()) {
                    foundNeighbors.push_back(curNode);
                }
            }
        }
        else if (dir==west) {
            testBounds = findCellBoundsInDirection(*curNode, east);
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
    leaves = getListOfLeavesHelper(root, leaves);
    return leaves;
}

vector<QuadtreeNode*> Quadtree::getListOfLeavesHelper(QuadtreeNode* curNode, vector<QuadtreeNode*> leaves) {
//    cout << "get list of leaves helper "<< curNode->getDimension() <<endl;
    if (curNode->numChildren()==0) {
        leaves.push_back(curNode);
        return leaves;
    }
    else {
//        cout <<"starting with node "<< curNode->getDimension()<<endl;
        vector<QuadtreeNode*> curChildren = curNode->getChildren();
        for (int i = 0; i < curChildren.size(); i++) {
//            cout <<"continuing with node "<< curChildren[i]->getDimension()<<endl;
            vector<QuadtreeNode*> newLeaves = getListOfLeavesHelper(curChildren[i], leaves);
            leaves = newLeaves;
        }
    }
    return leaves;
}

vector<QuadtreeNode*> Quadtree::removeLeaf(vector<QuadtreeNode*> leaves, QuadtreeNode* leafToRemove) {
    vector<QuadtreeNode*> newLeaves;
    for (int i = 0; i < leaves.size(); i++) {
        if (!(leaves[i] == leafToRemove)) {
            newLeaves.push_back(leaves[i]);
        }
    }
    return newLeaves;
}

bool Quadtree::doesContainLeaf(vector<QuadtreeNode*> leaves, QuadtreeNode* leaf) {
    for (int i = 0; i < leaves.size(); i++) {
        if (*leaves[i] == *leaf) {
            return true;
        }
    }
    return false;
}

bool Quadtree::isBalanced() {
    vector<QuadtreeNode*> leaves = getListOfLeaves();
    bool isBalanced = true;
    for (int i = 0; i < leaves.size(); i++) {
        QuadtreeNode* curLeaf = leaves[i];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbors = findLeafNeighborsInDirection(curLeaf, north);
        vector<QuadtreeNode*> southNeighbors = findLeafNeighborsInDirection(curLeaf, south);
        vector<QuadtreeNode*> eastNeighbors = findLeafNeighborsInDirection(curLeaf, east);
        vector<QuadtreeNode*> westNeighbors = findLeafNeighborsInDirection(curLeaf, west);

        neighbors.insert(neighbors.end(), northNeighbors.begin(), northNeighbors.end());
        neighbors.insert(neighbors.end(), southNeighbors.begin(), southNeighbors.end());
        neighbors.insert(neighbors.end(), eastNeighbors.begin(), eastNeighbors.end());
        neighbors.insert(neighbors.end(), westNeighbors.begin(), westNeighbors.end());

        bool mustRefineCurLeaf = false;
        for (int j = 0; j < neighbors.size(); j++) {
            if (curLeaf->getDimension() / neighbors[j]->getDimension() > 2) {
                mustRefineCurLeaf = true;
                break;
            }
        }
        if (mustRefineCurLeaf) {
            isBalanced = false;
            break;
        }
    }
    return isBalanced;
}


void Quadtree::balanceQuadtree() {
    vector<QuadtreeNode*> leaves = getListOfLeaves();
    cout<<leaves.size()<<endl;
    while(leaves.size() > 0) {
        QuadtreeNode* curLeaf = leaves[0];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbors = findLeafNeighborsInDirection(curLeaf, north);
        vector<QuadtreeNode*> southNeighbors = findLeafNeighborsInDirection(curLeaf, south);
        vector<QuadtreeNode*> eastNeighbors = findLeafNeighborsInDirection(curLeaf, east);
        vector<QuadtreeNode*> westNeighbors = findLeafNeighborsInDirection(curLeaf, west);

        neighbors.insert(neighbors.end(), northNeighbors.begin(), northNeighbors.end());
        neighbors.insert(neighbors.end(), southNeighbors.begin(), southNeighbors.end());
        neighbors.insert(neighbors.end(), eastNeighbors.begin(), eastNeighbors.end());
        neighbors.insert(neighbors.end(), westNeighbors.begin(), westNeighbors.end());

        bool mustRefineCurLeaf = false;
        for (int j = 0; j < neighbors.size(); j++) {
            if (curLeaf->getDimension() / neighbors[j]->getDimension() > 2) {
                mustRefineCurLeaf = true;
                break;
            }
        }

        if (mustRefineCurLeaf) {
//            cout <<"LALALALALALLALA" << endl;
            
            QuadtreeNode* northEastChild = new QuadtreeNode(curLeaf->getCenterX() + curLeaf->getDimension()/4, curLeaf->getCenterY() + curLeaf->getDimension()/4, curLeaf->getDimension() / 2);
            QuadtreeNode* northWestChild = new QuadtreeNode(curLeaf->getCenterX() - curLeaf->getDimension()/4, curLeaf->getCenterY() + curLeaf->getDimension()/4, curLeaf->getDimension() / 2);
            QuadtreeNode* southEastChild = new QuadtreeNode(curLeaf->getCenterX() + curLeaf->getDimension()/4, curLeaf->getCenterY() - curLeaf->getDimension()/4, curLeaf->getDimension() / 2);
            QuadtreeNode* southWestChild = new QuadtreeNode(curLeaf->getCenterX() - curLeaf->getDimension()/4, curLeaf->getCenterY() - curLeaf->getDimension()/4, curLeaf->getDimension() / 2);

            curLeaf->addChild(northEastChild, northeast);
            curLeaf->addChild(northWestChild, northwest);
            curLeaf->addChild(southEastChild, southeast);
            curLeaf->addChild(southWestChild, southwest);

            leaves.push_back(northEastChild);
            leaves.push_back(northWestChild);
            leaves.push_back(southEastChild);
            leaves.push_back(southWestChild);
        }
        leaves = removeLeaf(leaves, curLeaf);
    }
}

QuadtreeNode* Quadtree::getRoot() {
    return root;
}


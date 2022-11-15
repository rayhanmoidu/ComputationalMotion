#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "CircleIsosurface.hpp"

Quadtree::Quadtree(int screenWidth, int screenHeight, int smallestGridSize, Isosurface &isosurface) :
isosurface(isosurface) {
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

Quadtree::Quadtree(Isosurface &isosurface) : isosurface(isosurface) {
    hBound = 0;
    vBound = 0;
    gridSizeLimit = 0;
}

Isosurface& Quadtree::getIsosurface() {
    return isosurface;
}

void Quadtree::constructChildren(QuadtreeNode *node) {
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

void colorSquare(QuadtreeNode node) {
    glBegin(GL_QUADS);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() - node.getDimension() / 2);
        glVertex2f(node.getCenterX() + node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
        glVertex2f(node.getCenterX() - node.getDimension() / 2, node.getCenterY() + node.getDimension() / 2);
    glEnd();
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

vector<QuadtreeNode*> Quadtree::removeNodeFromVector(vector<QuadtreeNode*> leaves, QuadtreeNode* leafToRemove) {
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
        vector<QuadtreeNode*> northNeighbors = getNeighbours(curLeaf, north);
        vector<QuadtreeNode*> southNeighbors = getNeighbours(curLeaf, south);
        vector<QuadtreeNode*> eastNeighbors = getNeighbours(curLeaf, east);
        vector<QuadtreeNode*> westNeighbors = getNeighbours(curLeaf, west);

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
    while(leaves.size() > 0) {
        QuadtreeNode* curLeaf = leaves[0];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbors = getNeighbours(curLeaf, north);
        vector<QuadtreeNode*> southNeighbors = getNeighbours(curLeaf, south);
        vector<QuadtreeNode*> eastNeighbors = getNeighbours(curLeaf, east);
        vector<QuadtreeNode*> westNeighbors = getNeighbours(curLeaf, west);

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
            
            QuadtreeNode* northEastChild = new QuadtreeNode(curLeaf->getCenterX() + curLeaf->getDimension()/4, curLeaf->getCenterY() + curLeaf->getDimension()/4, curLeaf->getDimension() / 2, curLeaf);
            QuadtreeNode* northWestChild = new QuadtreeNode(curLeaf->getCenterX() - curLeaf->getDimension()/4, curLeaf->getCenterY() + curLeaf->getDimension()/4, curLeaf->getDimension() / 2, curLeaf);
            QuadtreeNode* southEastChild = new QuadtreeNode(curLeaf->getCenterX() + curLeaf->getDimension()/4, curLeaf->getCenterY() - curLeaf->getDimension()/4, curLeaf->getDimension() / 2, curLeaf);
            QuadtreeNode* southWestChild = new QuadtreeNode(curLeaf->getCenterX() - curLeaf->getDimension()/4, curLeaf->getCenterY() - curLeaf->getDimension()/4, curLeaf->getDimension() / 2, curLeaf);

            curLeaf->addChild(northEastChild, northeast);
            curLeaf->addChild(northWestChild, northwest);
            curLeaf->addChild(southEastChild, southeast);
            curLeaf->addChild(southWestChild, southwest);

            leaves.push_back(northEastChild);
            leaves.push_back(northWestChild);
            leaves.push_back(southEastChild);
            leaves.push_back(southWestChild);
            
            for (int i = 0; i < neighbors.size(); i++) {
                leaves.push_back(neighbors[i]);
            }
        }
        leaves = removeNodeFromVector(leaves, curLeaf);
    }
}

QuadtreeNode* Quadtree::getRoot() {
    return root;
}

QuadtreeNode* Quadtree::getNeighbourOfGreaterOrEqualSize(QuadtreeNode* curNode, Direction dir) {
    if (dir==north) {
        if (curNode->getParent()==NULL) return NULL;
        if (curNode->getParent()->getSWChild()==curNode) return curNode->getParent()->getNWChild();
        if (curNode->getParent()->getSEChild()==curNode) return curNode->getParent()->getNEChild();
        
        QuadtreeNode* testNode = getNeighbourOfGreaterOrEqualSize(curNode->getParent(), dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (curNode->getParent()->getNWChild()==curNode) return testNode->getSWChild();
        else return testNode->getSEChild();
    } else if (dir == south) {
        if (curNode->getParent()==NULL) return NULL;
        if (curNode->getParent()->getNWChild()==curNode) return curNode->getParent()->getSWChild();
        if (curNode->getParent()->getNEChild()==curNode) return curNode->getParent()->getSEChild();
        
        QuadtreeNode* testNode = getNeighbourOfGreaterOrEqualSize(curNode->getParent(), dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (curNode->getParent()->getSWChild()==curNode) return testNode->getNWChild();
        else return testNode->getNEChild();
    } else if (dir == east) {
        if (curNode->getParent()==NULL) return NULL;
        if (curNode->getParent()->getNWChild()==curNode) return curNode->getParent()->getNEChild();
        if (curNode->getParent()->getSWChild()==curNode) return curNode->getParent()->getSEChild();
        
        QuadtreeNode* testNode = getNeighbourOfGreaterOrEqualSize(curNode->getParent(), dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (curNode->getParent()->getNEChild()==curNode) return testNode->getNWChild();
        else return testNode->getSWChild();
    } else if (dir==west) {
        if (curNode->getParent()==NULL) return NULL;
        if (curNode->getParent()->getNEChild()==curNode) return curNode->getParent()->getNWChild();
        if (curNode->getParent()->getSEChild()==curNode) return curNode->getParent()->getSWChild();
        
        QuadtreeNode* testNode = getNeighbourOfGreaterOrEqualSize(curNode->getParent(), dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (curNode->getParent()->getNWChild()==curNode) return testNode->getNEChild();
        else return testNode->getSEChild();
    }
    cout << "should never go here" << endl;
    return NULL;
}

vector<QuadtreeNode*> Quadtree::getNeighboursOfSmallerSize(QuadtreeNode* curNode, QuadtreeNode* neighbour, Direction dir) {
    vector<QuadtreeNode*> neighbours;
    vector<QuadtreeNode*> candidates;
    if (neighbour!=NULL) candidates.push_back(neighbour);
    
    if (dir==north) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getSWChild());
                candidates.push_back(curCandidate->getSEChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==south) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getNEChild());
                candidates.push_back(curCandidate->getNWChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==east) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getSWChild());
                candidates.push_back(curCandidate->getNWChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==west) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getNEChild());
                candidates.push_back(curCandidate->getSEChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    }
    return neighbours;
}

vector<QuadtreeNode*> Quadtree::getNeighbours(QuadtreeNode* curNode, Direction dir) {
    QuadtreeNode* neighbour = getNeighbourOfGreaterOrEqualSize(curNode, dir);
    vector<QuadtreeNode*> neighbours = getNeighboursOfSmallerSize(curNode, neighbour, dir);
    return neighbours;
}


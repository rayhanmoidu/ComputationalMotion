//
//  QuadtreeNode.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-14.
//

#include "QuadtreeNode.hpp"
#include <iostream>

using namespace std;

QuadtreeNode::QuadtreeNode() {
    centerX = 0;
    centerY = 0;
    dimension = 0;
    NEChild = NULL;
    NWChild = NULL;
    SEChild = NULL;
    SWChild = NULL;
    parent = NULL;
}

QuadtreeNode::QuadtreeNode(float cx, float cy, float d, QuadtreeNode* newParent) {
    centerX = cx;
    centerY = cy;
    dimension = d;
    NEChild = NULL;
    NWChild = NULL;
    SEChild = NULL;
    SWChild = NULL;
    parent = newParent;
}

float QuadtreeNode::getDimension() {
    return dimension;
}

float QuadtreeNode::getCenterX() {
    return centerX;
}

float QuadtreeNode::getCenterY() {
    return centerY;
}

int QuadtreeNode::numChildren() {
    int count = 0;
    if (NEChild != NULL) count++;
    if (NWChild != NULL) count++;
    if (SEChild != NULL) count++;
    if (SWChild != NULL) count++;
    return count;
}

vector<QuadtreeNode*> QuadtreeNode::getChildren() {
    vector<QuadtreeNode*> children;
    if (NEChild != NULL) children.push_back(NEChild);
    if (NWChild != NULL) children.push_back(NWChild);
    if (SEChild != NULL) children.push_back(SEChild);
    if (SWChild != NULL) children.push_back(SWChild);
    return children;
}

void QuadtreeNode::addChild(QuadtreeNode* newChild, Direction dir) {
    if (dir==northeast) NEChild = newChild;
    if (dir==northwest) NWChild = newChild;
    if (dir==southeast) SEChild = newChild;
    if (dir==southwest) SWChild = newChild;
}

bool QuadtreeNode::operator == (QuadtreeNode &obj) {
    return obj.centerY == centerY && obj.centerX == centerX && obj.dimension == dimension;
}

QuadtreeNode* QuadtreeNode::getParent() {
    return parent;
}

QuadtreeNode* QuadtreeNode::getNEChild() {
    return NEChild;
}

QuadtreeNode* QuadtreeNode::getNWChild() {
    return NWChild;
}

QuadtreeNode* QuadtreeNode::getSEChild() {
    return SEChild;
}

QuadtreeNode* QuadtreeNode::getSWChild() {
    return SWChild;
}

bool QuadtreeNode::isLeaf() {
    return numChildren()==0;
}

QuadtreeNode* QuadtreeNode::getNeighbourOfGreaterOrEqualSize(Direction dir) {
    if (this==NULL) return NULL;
    if (dir==north) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getSWChild()==this) return this->getParent()->getNWChild();
        if (this->getParent()->getSEChild()==this) return this->getParent()->getNEChild();
        
        QuadtreeNode* testNode = this->getParent()->getNeighbourOfGreaterOrEqualSize(dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (this->getParent()->getNWChild()==this) return testNode->getSWChild();
        else return testNode->getSEChild();
    } else if (dir == south) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getNWChild()==this) return this->getParent()->getSWChild();
        if (this->getParent()->getNEChild()==this) return this->getParent()->getSEChild();
        
        QuadtreeNode* testNode = this->getParent()->getNeighbourOfGreaterOrEqualSize(dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (this->getParent()->getSWChild()==this) return testNode->getNWChild();
        else return testNode->getNEChild();
    } else if (dir == east) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getNWChild()==this) return this->getParent()->getNEChild();
        if (this->getParent()->getSWChild()==this) return this->getParent()->getSEChild();
        
        QuadtreeNode* testNode = this->getParent()->getNeighbourOfGreaterOrEqualSize(dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (this->getParent()->getNEChild()==this) return testNode->getNWChild();
        else return testNode->getSWChild();
    } else if (dir==west) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getNEChild()==this) return this->getParent()->getNWChild();
        if (this->getParent()->getSEChild()==this) return this->getParent()->getSWChild();
        
        QuadtreeNode* testNode = this->getParent()->getNeighbourOfGreaterOrEqualSize(dir);
        if (testNode==NULL || testNode->isLeaf()) return testNode;
        
        if (this->getParent()->getNWChild()==this) return testNode->getNEChild();
        else return testNode->getSEChild();
    } else if (dir==northwest) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getSEChild()==this) return this->getParent()->getNWChild();
        if (this->getParent()->getSWChild()==this) {
            return this->getParent()->getNWChild()->getNeighbourOfGreaterOrEqualSize(west);
        }
        if (this->getParent()->getNEChild()==this) return this->getParent()->getNWChild()->getNeighbourOfGreaterOrEqualSize(north);
        if (this->getParent()->getNWChild()==this) {
            QuadtreeNode* testNode_1 = this->getNeighbourOfGreaterOrEqualSize(north);
            QuadtreeNode* testNode_2 = testNode_1->getNeighbourOfGreaterOrEqualSize(west);
            return testNode_2;
        }
    } else if (dir==northeast) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getSWChild()==this) return this->getParent()->getNEChild();
        if (this->getParent()->getSEChild()==this) return this->getParent()->getNEChild()->getNeighbourOfGreaterOrEqualSize(east);
        if (this->getParent()->getNWChild()==this) return this->getParent()->getNEChild()->getNeighbourOfGreaterOrEqualSize(north);
        if (this->getParent()->getNEChild()==this) {
            QuadtreeNode* testNode_1 = this->getNeighbourOfGreaterOrEqualSize(north);
            QuadtreeNode* testNode_2 = testNode_1->getNeighbourOfGreaterOrEqualSize(east);
            return testNode_2;
        }
    } else if (dir==southeast) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getNWChild()==this) return this->getParent()->getSEChild();
        if (this->getParent()->getNEChild()==this) return this->getParent()->getSEChild()->getNeighbourOfGreaterOrEqualSize(east);
        if (this->getParent()->getSWChild()==this) return this->getParent()->getSEChild()->getNeighbourOfGreaterOrEqualSize(south);
        if (this->getParent()->getSEChild()==this) {
            QuadtreeNode* testNode_1 = this->getNeighbourOfGreaterOrEqualSize(south);
            QuadtreeNode* testNode_2 = testNode_1->getNeighbourOfGreaterOrEqualSize(east);
            return testNode_2;
        }
    } else if (dir==southwest) {
        if (this->getParent()==NULL) return NULL;
        if (this->getParent()->getNEChild()==this) return this->getParent()->getSWChild();
        if (this->getParent()->getNWChild()==this) return this->getParent()->getSWChild()->getNeighbourOfGreaterOrEqualSize(west);
        if (this->getParent()->getSEChild()==this) return this->getParent()->getSWChild()->getNeighbourOfGreaterOrEqualSize(south);
        if (this->getParent()->getSWChild()==this) {
            QuadtreeNode* testNode_1 = this->getNeighbourOfGreaterOrEqualSize(south);
            QuadtreeNode* testNode_2 = testNode_1->getNeighbourOfGreaterOrEqualSize(west);
            return testNode_2;
        }
    }
    cout << "should never go here" << endl;
    return NULL;
}

vector<QuadtreeNode*> QuadtreeNode::getNeighboursOfSmallerSize(QuadtreeNode* neighbour, Direction dir) {
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
    } else if (dir==northwest) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getSEChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==northeast) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getSWChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==southeast) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getNWChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    } else if (dir==southwest) {
        while (candidates.size() > 0) {
            QuadtreeNode* curCandidate = candidates[0];
            if (curCandidate->isLeaf()) neighbours.push_back(curCandidate);
            else {
                candidates.push_back(curCandidate->getNEChild());
            }
            candidates = removeNodeFromVector(candidates, curCandidate);
        }
    }
    return neighbours;
}

vector<QuadtreeNode*> QuadtreeNode::getNeighbours(Direction dir) {
    QuadtreeNode* neighbour = this->getNeighbourOfGreaterOrEqualSize(dir);
    vector<QuadtreeNode*> neighbours = this->getNeighboursOfSmallerSize(neighbour, dir);
    return neighbours;
}

vector<QuadtreeNode*> QuadtreeNode::removeNodeFromVector(vector<QuadtreeNode*> curVector, QuadtreeNode* nodeToRemove) {
    vector<QuadtreeNode*> newVector;
    for (int i = 0; i < curVector.size(); i++) {
        if (!(curVector[i] == nodeToRemove)) {
            newVector.push_back(curVector[i]);
        }
    }
    return newVector;
}

vector<QuadtreeNode*> QuadtreeNode::getListOfLeaves(vector<QuadtreeNode*> leaves) {
    if (this->numChildren()==0) {
        leaves.push_back(this);
        return leaves;
    }
    else {
        vector<QuadtreeNode*> curChildren = this->getChildren();
        for (int i = 0; i < curChildren.size(); i++) {
            vector<QuadtreeNode*> newLeaves = curChildren[i]->getListOfLeaves(leaves);
            leaves = newLeaves;
        }
    }
    return leaves;
}


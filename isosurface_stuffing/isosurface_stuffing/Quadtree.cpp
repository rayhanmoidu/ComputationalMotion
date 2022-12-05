#include "Quadtree.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "CircleIsosurface.hpp"

CircleIsosurface nullIsosurface;

Quadtree::Quadtree(int screenWidth, int screenHeight, int smallestGridSize, Isosurface &isosurface) :
isosurface(isosurface) {
}

Quadtree::Quadtree(Isosurface &isosurface) : isosurface(isosurface) {
}

Quadtree::Quadtree() : isosurface(nullIsosurface) {
}


Isosurface& Quadtree::getIsosurface() {
    return isosurface;
}

vector<QuadtreeNode*> Quadtree::getListOfLeaves() {
    vector<QuadtreeNode*> leaves;
    leaves = root->getListOfLeaves(leaves);
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
        vector<QuadtreeNode*> northNeighbors = curLeaf->getNeighbours(north);
        vector<QuadtreeNode*> southNeighbors = curLeaf->getNeighbours(south);
        vector<QuadtreeNode*> eastNeighbors = curLeaf->getNeighbours(east);
        vector<QuadtreeNode*> westNeighbors = curLeaf->getNeighbours(west);

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
        vector<QuadtreeNode*> northNeighbors = curLeaf->getNeighbours(north);
        vector<QuadtreeNode*> southNeighbors = curLeaf->getNeighbours(south);
        vector<QuadtreeNode*> eastNeighbors = curLeaf->getNeighbours(east);
        vector<QuadtreeNode*> westNeighbors = curLeaf->getNeighbours(west);

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
            refineNode(curLeaf);
            
            vector<QuadtreeNode*> children = curLeaf->getChildren();

            leaves.push_back(children[0]);
            leaves.push_back(children[1]);
            leaves.push_back(children[2]);
            leaves.push_back(children[3]);
            
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

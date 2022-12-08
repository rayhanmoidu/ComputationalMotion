//
//  ProvablyGoodQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-30.
//

#include "ProvablyGoodQuadtreeTiling.hpp"

ProvablyGoodQuadtreeTiling::ProvablyGoodQuadtreeTiling(SquareQuadtree tree) : QuadtreeTiling() {
    // rebalance strongly
    stronglyBalance(tree);
    createTilingHelper(tree.getRoot());
}

void ProvablyGoodQuadtreeTiling::stronglyBalance(SquareQuadtree tree) {
    vector<QuadtreeNode*> leaves;
    leaves = tree.getRoot()->getListOfLeaves(leaves);
    while(leaves.size() > 0) {
        QuadtreeNode* curLeaf = leaves[0];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbors = curLeaf->getNeighbours(north);
        vector<QuadtreeNode*> southNeighbors = curLeaf->getNeighbours(south);
        vector<QuadtreeNode*> eastNeighbors = curLeaf->getNeighbours(east);
        vector<QuadtreeNode*> westNeighbors = curLeaf->getNeighbours(west);
        vector<QuadtreeNode*> northEastNeighbors = curLeaf->getNeighbours(northeast);
        vector<QuadtreeNode*> southWestNeighbors = curLeaf->getNeighbours(southwest);
        vector<QuadtreeNode*> southEastNeighbors = curLeaf->getNeighbours(southeast);
        vector<QuadtreeNode*> northWestNeighbors = curLeaf->getNeighbours(northwest);

        neighbors.insert(neighbors.end(), northNeighbors.begin(), northNeighbors.end());
        neighbors.insert(neighbors.end(), southNeighbors.begin(), southNeighbors.end());
        neighbors.insert(neighbors.end(), eastNeighbors.begin(), eastNeighbors.end());
        neighbors.insert(neighbors.end(), westNeighbors.begin(), westNeighbors.end());
        neighbors.insert(neighbors.end(), northEastNeighbors.begin(), northEastNeighbors.end());
        neighbors.insert(neighbors.end(), southWestNeighbors.begin(), southWestNeighbors.end());
        neighbors.insert(neighbors.end(), southEastNeighbors.begin(), southEastNeighbors.end());
        neighbors.insert(neighbors.end(), northWestNeighbors.begin(), northWestNeighbors.end());

        bool mustRefineCurLeaf = false;
        for (int j = 0; j < neighbors.size(); j++) {
            if (curLeaf->getDimension() / neighbors[j]->getDimension() > 2) {
                mustRefineCurLeaf = true;
                break;
            }
        }

        if (mustRefineCurLeaf) {
            tree.refineNode(curLeaf);
            
            vector<QuadtreeNode*> children = curLeaf->getChildren();

            leaves.push_back(children[0]);
            leaves.push_back(children[1]);
            leaves.push_back(children[2]);
            leaves.push_back(children[3]);
            
            for (int i = 0; i < neighbors.size(); i++) {
                leaves.push_back(neighbors[i]);
            }
        }
        leaves = tree.removeNodeFromVector(leaves, curLeaf);
    }
}

string ProvablyGoodQuadtreeTiling::getSideLabel(vector<QuadtreeNode*> neighbours, QuadtreeNode* curNode) {
    if (neighbours.size()==0) return "B";
    float resolutionRatio = neighbours[0]->getDimension() / curNode->getDimension();
    if (resolutionRatio==2) return "C";
    else if (resolutionRatio==1) return "B";
    else if (resolutionRatio==0.5) return "A";
    
    cout <<" should never reach here fdnhipqdfh " << resolutionRatio <<endl;
    return "";
}

bool ProvablyGoodQuadtreeTiling::isRotationValid(string curRotation) {
    for (int i = 0; i < 9; i++) {
        if (validConfigurations[i]==curRotation) return true;
    }
    return false;
}

CellConfiguration ProvablyGoodQuadtreeTiling::getConfiguration(string configuration) {
    if (configuration=="ABAB") return ABAB;
    if (configuration=="ABCB") return ABCB;
    if (configuration=="BBCC") return BBCC;
    if (configuration=="BBBB") return BBBB;
    if (configuration=="ABBB") return ABBB;
    if (configuration=="AABB") return AABB;
    if (configuration=="AAAA") return AAAA;
    if (configuration=="AAAB") return AAAB;
    if (configuration=="BBBC") return BBBC;
    cout <<"should never reach here "<<configuration<<endl;;
    return ABAB;
}

void ProvablyGoodQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    string configuration = "";
    
    configuration = configuration + getSideLabel(northNeighbours, curNode);
    configuration = configuration + getSideLabel(eastNeighbours, curNode);
    configuration = configuration + getSideLabel(southNeighbours, curNode);
    configuration = configuration + getSideLabel(westNeighbours, curNode);
    
    float theta = 0;
    while (!isRotationValid(configuration)) {
        configuration = configuration[configuration.length()-1] + configuration.substr(0, 3);
        theta += M_PI/2;
        if (theta>2*M_PI) break;
    }
    
    vector<Triangle> newTriangles = triangulator.triangulate(getConfiguration(configuration), Point(curNode->getCenterX(), curNode->getCenterY()), curNode->getDimension(), theta);    
    for (int i = 0; i < newTriangles.size(); i++) triangles.push_back(newTriangles[i]);
}

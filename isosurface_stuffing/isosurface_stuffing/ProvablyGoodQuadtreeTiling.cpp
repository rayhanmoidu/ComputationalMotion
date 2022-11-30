//
//  ProvablyGoodQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-30.
//

#include "ProvablyGoodQuadtreeTiling.hpp"

ProvablyGoodQuadtreeTiling::ProvablyGoodQuadtreeTiling(SquareQuadtree tree) : QuadtreeTiling() {
    // rebalance strongly
    createTilingHelper(tree.getRoot());
    satisfyJunctions();
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

void ProvablyGoodQuadtreeTiling::satisfyJunctions() {
    // not needed
}


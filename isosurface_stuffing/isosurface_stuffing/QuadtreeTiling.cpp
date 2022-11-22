//
//  QuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-02.
//

#include "QuadtreeTiling.hpp"
#include <iostream>
#include <cmath>
#include "Triangle.hpp"
#include <vector>
#include "Quadtree.hpp"

QuadtreeTiling::QuadtreeTiling() {
}

void QuadtreeTiling::createTilingHelper(QuadtreeNode* curNode) {
    vector<QuadtreeNode*> children = curNode->getChildren();
    if (children.size()==0) {
        createTrianglesFromCell(curNode);
    } else {
        for (int i = 0; i < children.size(); i++) createTilingHelper(children[i]);
    }
}

vector<Point> QuadtreeTiling::findTriangleMidpointsThatAreVertices(Point mp1, Point mp2, Point mp3) {
    vector<Point> intersections;
    cout << mp1.getX() <<" "<<mp1.getY()<<endl;
    if (vertices.count(pair<float, float>(mp1.getX(), mp1.getY()))) intersections.push_back(mp1);
    if (vertices.count(pair<float, float>(mp2.getX(), mp2.getY()))) intersections.push_back(mp2);
    if (vertices.count(pair<float, float>(mp3.getX(), mp3.getY()))) intersections.push_back(mp3);
    return intersections;
}

void QuadtreeTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    cout<<" should never be called " << endl;
}

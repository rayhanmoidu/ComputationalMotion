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

QuadtreeTiling::QuadtreeTiling(Quadtree quadtree, QuadtreeTilingType tilingType) {
    createTilingHelper(quadtree.getRoot(), tilingType);
    if (tilingType==isoscelesSingle) satisfyJunctions_isoscelesSingle();
}

void QuadtreeTiling::createTilingHelper(QuadtreeNode* curNode, QuadtreeTilingType tilingType) {
    vector<QuadtreeNode*> children = curNode->getChildren();
    if (children.size()==0) {
        if (tilingType==isoscelesSingle) createTrianglesFromCell_isoscelesSingle(curNode);
        if (tilingType==isoscelesDouble) createTrianglesFromCell_isoscelesDouble(curNode);
        if (tilingType==equilateral) createTrianglesFromCell_equilateral(curNode);
        if (tilingType==provablyGood) createTrianglesFromCell_provablyGood(curNode);
    } else {
        for (int i = 0; i < children.size(); i++) createTilingHelper(children[i], tilingType);
    }
}


vector<Triangle> QuadtreeTiling::removeTriangle(vector<Triangle> curTriangles, Triangle triangleToRemove) {
    std::vector<Triangle> newTriangles;

    for (int i = 0; i < curTriangles.size(); i++) {
        if (!curTriangles[i].doTriangleVerticesMatch(triangleToRemove)) {
            newTriangles.push_back(curTriangles[i]);
        }
    }

    return newTriangles;
}

vector<Point> QuadtreeTiling::findTriangleMidpointsThatAreVertices(Point mp1, Point mp2, Point mp3) {
    vector<Point> intersections;
    for (int j = 0; j < vertices.size(); j++) {
        if (vertices[j]==mp1) intersections.push_back(mp1);
        if (vertices[j]==mp2) intersections.push_back(mp2);
        if (vertices[j]==mp3) intersections.push_back(mp3);
    }
    return intersections;
}

void QuadtreeTiling::satisfyJunctions_isoscelesSingle() {
    vector<Triangle> trianglesToProcess = triangles;
    
    while(trianglesToProcess.size()>0) {
        Triangle curTriangle = trianglesToProcess[0];
        vector<Point> curPoints = curTriangle.getPoints();
        float x1 = (curPoints[0].getX() + curPoints[1].getX()) / 2;
        float y1 = (curPoints[0].getY() + curPoints[1].getY()) / 2;
        
        float x2 = (curPoints[0].getX() + curPoints[2].getX()) / 2;
        float y2 = (curPoints[0].getY() + curPoints[2].getY()) / 2;
        
        float x3 = (curPoints[2].getX() + curPoints[1].getX()) / 2;
        float y3 = (curPoints[2].getY() + curPoints[1].getY()) / 2;
        
        Point p1(x1, y1);
        Point p2(x2, y2);
        Point p3(x3, y3);
        
        vector<Point> midPointVertices = findTriangleMidpointsThatAreVertices(p1, p2, p3);
        if (midPointVertices.size()==2) {
            Point mpv1 = midPointVertices[0];
            Point mpv2 = midPointVertices[1];
            
            cout<<"midpoints"<<endl;
            cout <<mpv1.getX()<<" "<<mpv1.getY()<<endl;
            cout <<mpv2.getX()<<" "<<mpv2.getY()<<endl;
            cout<<"points"<<endl;
            cout <<p1.getX()<<" "<<p1.getY()<<endl;
            cout <<p2.getX()<<" "<<p2.getY()<<endl;
            cout <<p3.getX()<<" "<<p3.getY()<<endl;
            
            if ((mpv1==p1 && mpv2==p2) || (mpv1==p2 && mpv2==p1)) {
                cout <<"hi"<<endl;
                Triangle t1(curPoints[2], p1, curPoints[1]);
                Triangle t2(curPoints[2], p1, p2);
                Triangle t3(curPoints[0], p1, p2);
                triangles = removeTriangle(triangles, curTriangle);
                triangles.push_back(t1);
                triangles.push_back(t2);
                triangles.push_back(t3);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
                trianglesToProcess.push_back(t3);
            } else if ((mpv1==p2 && mpv2==p3) || (mpv1==p3 && mpv2==p2)) {
                cout <<"hi"<<endl;
                Triangle t1(curPoints[0], p3, curPoints[1]);
                Triangle t2(curPoints[0], p3, p2);
                Triangle t3(curPoints[2], p3, p2);
                triangles.push_back(t1);
                triangles.push_back(t2);
                triangles.push_back(t3);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
                trianglesToProcess.push_back(t3);
            } else if ((mpv1==p1 && mpv2==p3) || (mpv1==p3 && mpv2==p1)) {
                cout <<"hi"<<endl;
                Triangle t1(curPoints[0], p3, curPoints[2]);
                Triangle t2(curPoints[0], p3, p1);
                Triangle t3(curPoints[1], p3, p1);
                triangles.push_back(t1);
                triangles.push_back(t2);
                triangles.push_back(t3);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
                trianglesToProcess.push_back(t3);
            }
        } else if (midPointVertices.size()==1) {
            Point mpv1 = midPointVertices[0];
            if (mpv1==p1) {
                Triangle t1(curPoints[0], p1, curPoints[2]);
                Triangle t2(curPoints[1], p1, curPoints[2]);

                triangles = removeTriangle(triangles, curTriangle);
                triangles.push_back(t1);
                triangles.push_back(t2);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
            } else if (mpv1==p2) {
                Triangle t1(curPoints[0], p2, curPoints[1]);
                Triangle t2(curPoints[2], p2, curPoints[1]);

                triangles = removeTriangle(triangles, curTriangle);
                triangles.push_back(t1);
                triangles.push_back(t2);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
            } else if (mpv1==p3) {
                Triangle t1(curPoints[1], p3, curPoints[0]);
                Triangle t2(curPoints[2], p3, curPoints[0]);

                triangles = removeTriangle(triangles, curTriangle);
                triangles.push_back(t1);
                triangles.push_back(t2);
                trianglesToProcess.push_back(t1);
                trianglesToProcess.push_back(t2);
            }
        }
        
        trianglesToProcess = removeTriangle(trianglesToProcess, curTriangle);
    }
}

void QuadtreeTiling::createTrianglesFromCell_isoscelesSingle(QuadtreeNode *curNode) {
    Point ULCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point URCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BLCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point BRCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    
    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(URCorner, BRCorner, ULCorner);
    
    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    
    triangles.push_back(t1);
    triangles.push_back(t2);
}

void QuadtreeTiling::createTrianglesFromCell_isoscelesDouble(QuadtreeNode *curNode) {
    Point ULCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point URCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BLCorner(curNode->getCenterX() - curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point BRCorner(curNode->getCenterX() + curNode->getDimension() / 2, curNode->getCenterY() + curNode->getDimension() / 2);
    Point center(curNode->getCenterX(), curNode->getCenterY());
    
    Triangle t1(ULCorner, URCorner, center);
    Triangle t2(ULCorner, BLCorner, center);
    Triangle t3(URCorner, BRCorner, center);
    Triangle t4(BLCorner, BRCorner, center);
    
    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    addVertex(center);
    
    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
}

void QuadtreeTiling::createTrianglesFromCell_equilateral(QuadtreeNode *curNode) {
    //todo
    float val = M_PI / 180;
    float shift = (tan(30*val) * curNode->getDimension());
    Point ULCorner((curNode->getCenterX() - curNode->getDimension() / 2) + shift, curNode->getCenterY() - curNode->getDimension() / 2);
    Point URCorner((curNode->getCenterX() + curNode->getDimension() / 2) + shift, curNode->getCenterY() - curNode->getDimension() / 2);
    Point BLCorner((curNode->getCenterX() - curNode->getDimension() / 2), curNode->getCenterY() + curNode->getDimension() / 2);
    Point BRCorner((curNode->getCenterX() + curNode->getDimension() / 2), curNode->getCenterY() + curNode->getDimension() / 2);

    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    
    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(URCorner, BRCorner, ULCorner);
    
    vector<float> angles1 = t1.computeAngles();
    vector<float> angles2 = t2.computeAngles();

    triangles.push_back(t1);
    triangles.push_back(t2);
}

void QuadtreeTiling::createTrianglesFromCell_provablyGood(QuadtreeNode *curNode) {
    //todo
}

void QuadtreeTiling::createTiling(float xPos, float yPos, string key, string orientation) {
    cout<<" should never be called " << endl;
}

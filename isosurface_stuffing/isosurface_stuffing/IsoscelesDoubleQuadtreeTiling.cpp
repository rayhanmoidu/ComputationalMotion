//
//  IsoscelesDoubleQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "IsoscelesDoubleQuadtreeTiling.hpp"

IsoscelesDoubleQuadtreeTiling::IsoscelesDoubleQuadtreeTiling(Quadtree tree) : QuadtreeTiling(tree) {
    createTilingHelper(tree.getRoot());
    satisfyJunctions();
}

void IsoscelesDoubleQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
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

void IsoscelesDoubleQuadtreeTiling::satisfyJunctions() {
    // todo
    vector<Triangle> trianglesToProcess = triangles;
    
    while (trianglesToProcess.size() > 0) {
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
        
        if (midPointVertices.size()==1) {
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

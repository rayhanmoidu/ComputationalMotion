//
//  EquilateralQuadtreeTiling.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#include "EquilateralQuadtreeTiling.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

EquilateralQuadtreeTiling::EquilateralQuadtreeTiling(ParallelogramQuadtree tree) : QuadtreeTiling() {
    rebalanceQuadtree(tree);
    createTilingHelper(tree.getRoot());
//    satisfyJunctions();
}

void EquilateralQuadtreeTiling::rebalanceQuadtree(ParallelogramQuadtree tree) {

    vector<QuadtreeNode*> leavesToProcess = tree.getListOfLeaves();
    while(leavesToProcess.size() > 0) {
        QuadtreeNode* curLeaf = leavesToProcess[0];

        vector<QuadtreeNode*> neighbors;
        vector<QuadtreeNode*> northNeighbours = curLeaf->getNeighbours(north);
        vector<QuadtreeNode*> southNeighbours = curLeaf->getNeighbours(south);
        vector<QuadtreeNode*> eastNeighbours = curLeaf->getNeighbours(east);
        vector<QuadtreeNode*> westNeighbours = curLeaf->getNeighbours(west);
        
        int numSmallerNeighbours = 0;
        if (northNeighbours.size()>1) numSmallerNeighbours++;
        if (eastNeighbours.size()>1) numSmallerNeighbours++;
        if (westNeighbours.size()>1) numSmallerNeighbours++;
        if (southNeighbours.size()>1) numSmallerNeighbours++;

        neighbors.insert(neighbors.end(), northNeighbours.begin(), northNeighbours.end());
        neighbors.insert(neighbors.end(), southNeighbours.begin(), southNeighbours.end());
        neighbors.insert(neighbors.end(), eastNeighbours.begin(), eastNeighbours.end());
        neighbors.insert(neighbors.end(), westNeighbours.begin(), westNeighbours.end());
        
        bool mustRefineCurLeaf = false;
        QuadtreeNode* neighbourToAdd = NULL;
        
        if (numSmallerNeighbours==4) mustRefineCurLeaf = true;
        if (numSmallerNeighbours==3) {
            mustRefineCurLeaf = true;
            if (northNeighbours.size()==1) neighbourToAdd = northNeighbours[0];
            if (eastNeighbours.size()==1) neighbourToAdd = eastNeighbours[0];
            if (westNeighbours.size()==1) neighbourToAdd = westNeighbours[0];
            if (southNeighbours.size()==1) neighbourToAdd = southNeighbours[0];
        }

        if (mustRefineCurLeaf) {
            tree.refineNode(curLeaf);
            
            if (neighbourToAdd != NULL) leavesToProcess.push_back(neighbourToAdd);
            
            vector<QuadtreeNode*> children = curLeaf->getChildren();

            leavesToProcess.push_back(children[0]);
            leavesToProcess.push_back(children[1]);
            leavesToProcess.push_back(children[2]);
            leavesToProcess.push_back(children[3]);
            
            for (int i = 0; i < neighbors.size(); i++) {
                leavesToProcess.push_back(neighbors[i]);
            }
        }
        leavesToProcess = tree.removeNodeFromVector(leavesToProcess, curLeaf);
    }
}

void EquilateralQuadtreeTiling::createTrianglesFromCell(QuadtreeNode *curNode) {
    float height = sqrt(3) * curNode->getDimension()/2;
    
    Point ULCorner((curNode->getCenterX() - curNode->getDimension() / 4), curNode->getCenterY() + height / 2);
    Point URCorner((curNode->getCenterX() + 3*curNode->getDimension() / 4), curNode->getCenterY() + height / 2);
    Point BLCorner((curNode->getCenterX() - 3*curNode->getDimension() / 4), curNode->getCenterY() - height / 2);
    Point BRCorner((curNode->getCenterX() + curNode->getDimension() / 4), curNode->getCenterY() - height / 2);

    addVertex(ULCorner);
    addVertex(URCorner);
    addVertex(BLCorner);
    addVertex(BRCorner);
    
    Triangle t1(ULCorner, BLCorner, BRCorner);
    Triangle t2(ULCorner, URCorner, BRCorner);
    
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    if (northNeighbours.size()>1) {
        t2.setDoesExistVertexBetweenP1P2(true);
    }
    if (eastNeighbours.size()>1) {
        t2.setDoesExistVertexBetweenP2P3(true);
    }
    if (westNeighbours.size()>1) {
        t1.setDoesExistVertexBetweenP1P2(true);
    }
    if (southNeighbours.size()>1) {
        t1.setDoesExistVertexBetweenP2P3(true);
    }

    t1.addTwin(t2);
    t2.addTwin(t1);

    vector<float> angles1 = t1.computeAngles();
    vector<float> angles2 = t2.computeAngles();

    triangles.push_back(t1);
    triangles.push_back(t2);
}

void EquilateralQuadtreeTiling::satisfyJunctions() {
    vector<Triangle> trianglesToProcess = triangles;

    while (trianglesToProcess.size() > 0) {
        cout << trianglesToProcess.size() << endl;
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

        int numVerticesAlongSideLengths = 0;
        if (curTriangle.getDoesExistVertexBetweenP1P2()) numVerticesAlongSideLengths++;
        if (curTriangle.getDoesExistVertexBetweenP1P3()) numVerticesAlongSideLengths++;
        if (curTriangle.getDoesExistVertexBetweenP2P3()) numVerticesAlongSideLengths++;
//        cout << numVerticesAlongSideLengths << endl;
        if (numVerticesAlongSideLengths==2) {
            Triangle t1(p1, p2, p3);
            Triangle t2(curPoints[0], p1, p2);
            Triangle t3(curPoints[1], p1, p3);
            Triangle t4(curPoints[2], p2, p3);
            triangles = removeTriangle(triangles, curTriangle);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
            trianglesToProcess.push_back(t1);
            trianglesToProcess.push_back(t2);
            trianglesToProcess.push_back(t3);
            trianglesToProcess.push_back(t4);

            //guaranteed to be one twin
            Triangle twin = curTriangle.getTwins()[0];
//            cout << twin.getDoesExistVertexBetweenP2P3()<<endl;
//            cout << twin.getDoesExistVertexBetweenP1P3()<<endl;
//            cout << twin.getDoesExistVertexBetweenP1P2()<<endl;
            twin.setDoesExistVertexBetweenP1P3(true);
            trianglesToProcess.push_back(twin);
        } else if (curTriangle.getDoesExistVertexBetweenP1P2()) {
            Triangle t1(curPoints[0], p1, curPoints[2]);
            Triangle t2(curPoints[1], p1, curPoints[2]);

            triangles = removeTriangle(triangles, curTriangle);
            triangles.push_back(t1);
            triangles.push_back(t2);
            trianglesToProcess.push_back(t1);
            trianglesToProcess.push_back(t2);
        } else if (curTriangle.getDoesExistVertexBetweenP2P3()) {
            Triangle t1(curPoints[1], p3, curPoints[0]);
            Triangle t2(curPoints[2], p3, curPoints[0]);

            triangles = removeTriangle(triangles, curTriangle);
            triangles.push_back(t1);
            triangles.push_back(t2);
            trianglesToProcess.push_back(t1);
            trianglesToProcess.push_back(t2);
        } else if (curTriangle.getDoesExistVertexBetweenP1P3()) {
            Triangle t1(curPoints[0], p2, curPoints[1]);
            Triangle t2(curPoints[2], p2, curPoints[1]);

            triangles = removeTriangle(triangles, curTriangle);
            triangles.push_back(t1);
            triangles.push_back(t2);
            trianglesToProcess.push_back(t1);
            trianglesToProcess.push_back(t2);
        }

        trianglesToProcess = removeTriangle(trianglesToProcess, curTriangle);
    }
}

//void EquilateralQuadtreeTiling::satisfyJunctions() {
//
//    vector<Triangle> trianglesToProcess = triangles;
//
//    while(trianglesToProcess.size()>0) {
//        cout << trianglesToProcess.size()<<endl;
//        Triangle curTriangle = trianglesToProcess[0];
//        vector<Point> curPoints = curTriangle.getPoints();
//        float x1 = (curPoints[0].getX() + curPoints[1].getX()) / 2;
//        float y1 = (curPoints[0].getY() + curPoints[1].getY()) / 2;
//
//        float x2 = (curPoints[0].getX() + curPoints[2].getX()) / 2;
//        float y2 = (curPoints[0].getY() + curPoints[2].getY()) / 2;
//
//        float x3 = (curPoints[2].getX() + curPoints[1].getX()) / 2;
//        float y3 = (curPoints[2].getY() + curPoints[1].getY()) / 2;
//
//        Point p1(x1, y1);
//        Point p2(x2, y2);
//        Point p3(x3, y3);
//
//        vector<Point> midPointVertices = findTriangleMidpointsThatAreVertices(p1, p2, p3);
//        cout<<midPointVertices.size()<<endl;
//        if (midPointVertices.size()==2) {
//            Triangle t1(p1, p2, p3);
//            Triangle t2(curPoints[0], p1, p2);
//            Triangle t3(curPoints[1], p1, p3);
//            Triangle t4(curPoints[2], p2, p3);
//            triangles = removeTriangle(triangles, curTriangle);
//            triangles.push_back(t1);
//            triangles.push_back(t2);
//            triangles.push_back(t3);
//            triangles.push_back(t4);
//            trianglesToProcess.push_back(t1);
//            trianglesToProcess.push_back(t2);
//            trianglesToProcess.push_back(t3);
//            trianglesToProcess.push_back(t4);
//        } else if (midPointVertices.size()==1) {
//            Point mpv1 = midPointVertices[0];
//            if (mpv1==p1) {
//                Triangle t1(curPoints[0], p1, curPoints[2]);
//                Triangle t2(curPoints[1], p1, curPoints[2]);
//
//                triangles = removeTriangle(triangles, curTriangle);
//                triangles.push_back(t1);
//                triangles.push_back(t2);
//                trianglesToProcess.push_back(t1);
//                trianglesToProcess.push_back(t2);
//            } else if (mpv1==p2) {
//                Triangle t1(curPoints[0], p2, curPoints[1]);
//                Triangle t2(curPoints[2], p2, curPoints[1]);
//
//                triangles = removeTriangle(triangles, curTriangle);
//                triangles.push_back(t1);
//                triangles.push_back(t2);
//                trianglesToProcess.push_back(t1);
//                trianglesToProcess.push_back(t2);
//            } else if (mpv1==p3) {
//                Triangle t1(curPoints[1], p3, curPoints[0]);
//                Triangle t2(curPoints[2], p3, curPoints[0]);
//
//                triangles = removeTriangle(triangles, curTriangle);
//                triangles.push_back(t1);
//                triangles.push_back(t2);
//                trianglesToProcess.push_back(t1);
//                trianglesToProcess.push_back(t2);
//            }
//        }
//
//        trianglesToProcess = removeTriangle(trianglesToProcess, curTriangle);
//    }
//}

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
    
    vector<QuadtreeNode*> northNeighbours = curNode->getNeighbours(north);
    vector<QuadtreeNode*> westNeighbours = curNode->getNeighbours(west);
    vector<QuadtreeNode*> eastNeighbours = curNode->getNeighbours(east);
    vector<QuadtreeNode*> southNeighbours = curNode->getNeighbours(south);
    
    int numSmallerNeighbours = 0;
    if (northNeighbours.size()>1) numSmallerNeighbours++;
    if (eastNeighbours.size()>1) numSmallerNeighbours++;
    if (westNeighbours.size()>1) numSmallerNeighbours++;
    if (southNeighbours.size()>1) numSmallerNeighbours++;
    
    if (numSmallerNeighbours==3 || numSmallerNeighbours==4) {cout<<"UNEXPECTED"<<endl;}
    
    if (numSmallerNeighbours==1) {
        if (northNeighbours.size()>1) {
            Point northMP((ULCorner.getX() + URCorner.getX()) / 2, (ULCorner.getY() + URCorner.getY()) / 2);
            Triangle t1(URCorner, BRCorner, northMP);
            Triangle t2(ULCorner, BRCorner, northMP);
            Triangle t3(ULCorner, BRCorner, BLCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (southNeighbours.size()>1) {
            Point southMP((BLCorner.getX() + BRCorner.getX()) / 2, (BLCorner.getY() + BRCorner.getY()) / 2);
            Triangle t1(ULCorner, BLCorner, southMP);
            Triangle t2(ULCorner, BRCorner, southMP);
            Triangle t3(ULCorner, URCorner, BRCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (eastNeighbours.size()>1) {
            Point eastMP((BRCorner.getX() + URCorner.getX()) / 2, (BRCorner.getY() + URCorner.getY()) / 2);
            Triangle t1(URCorner, ULCorner, eastMP);
            Triangle t2(ULCorner, BRCorner, eastMP);
            Triangle t3(ULCorner, BRCorner, BLCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
        if (westNeighbours.size()>1) {
            Point westMP((ULCorner.getX() + BLCorner.getX()) / 2, (ULCorner.getY() + BLCorner.getY()) / 2);
            Triangle t1(BRCorner, BLCorner, westMP);
            Triangle t2(ULCorner, BRCorner, westMP);
            Triangle t3(ULCorner, URCorner, BRCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }
//        triangles.push_back(t1);
//        triangles.push_back(t2);
//        triangles.push_back(t3);
    } else if (numSmallerNeighbours==2) {
        Point northMP((ULCorner.getX() + URCorner.getX()) / 2, (ULCorner.getY() + URCorner.getY()) / 2);
        Point southMP((BLCorner.getX() + BRCorner.getX()) / 2, (BLCorner.getY() + BRCorner.getY()) / 2);
        Point westMP((ULCorner.getX() + BLCorner.getX()) / 2, (ULCorner.getY() + BLCorner.getY()) / 2);
        Point eastMP((BRCorner.getX() + URCorner.getX()) / 2, (BRCorner.getY() + URCorner.getY()) / 2);
        Point middleMP((BRCorner.getX() + ULCorner.getX()) / 2, (BRCorner.getY() + ULCorner.getY()) / 2);
        
        if (northNeighbours.size()>1 && eastNeighbours.size()>1) {
            Triangle t1(URCorner, northMP, eastMP);
            Triangle t2(BRCorner, middleMP, eastMP);
            Triangle t3(ULCorner, northMP, middleMP);
            Triangle t4(northMP, middleMP, eastMP);
            Triangle t5(middleMP, ULCorner, BLCorner);
            Triangle t6(middleMP, BRCorner, BLCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
            triangles.push_back(t5);
            triangles.push_back(t6);
        } else if (northNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(URCorner, northMP, BRCorner);
            Triangle t2(ULCorner, northMP, BRCorner);
            Triangle t3(ULCorner, BRCorner, southMP);
            Triangle t4(ULCorner, BLCorner, southMP);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (northNeighbours.size()>1 && westNeighbours.size()>1) {
            Triangle t1(URCorner, northMP, BRCorner);
            Triangle t2(ULCorner, northMP, BRCorner);
            Triangle t3(ULCorner, westMP, BRCorner);
            Triangle t4(BLCorner, westMP, BRCorner);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (eastNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(URCorner, ULCorner, eastMP);
            Triangle t2(BRCorner, ULCorner, eastMP);
            Triangle t3(ULCorner, BRCorner, southMP);
            Triangle t4(ULCorner, BLCorner, southMP);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (eastNeighbours.size()>1 && westNeighbours.size()>1) {
            Triangle t1(URCorner, ULCorner, eastMP);
            Triangle t2(BRCorner, ULCorner, eastMP);
            Triangle t3(ULCorner, BRCorner, westMP);
            Triangle t4(BRCorner, BLCorner, westMP);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
        } else if (westNeighbours.size()>1 && southNeighbours.size()>1) {
            Triangle t1(URCorner, ULCorner, middleMP);
            Triangle t2(URCorner, BRCorner, middleMP);
            Triangle t3(BRCorner, southMP, middleMP);
            Triangle t4(BLCorner, southMP, westMP);
            Triangle t5(ULCorner, middleMP, westMP);
            Triangle t6(southMP, westMP, middleMP);
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
            triangles.push_back(t4);
            triangles.push_back(t5);
            triangles.push_back(t6);
        }
    } else if (numSmallerNeighbours==0) {
        Triangle t1(URCorner, ULCorner, BRCorner);
        Triangle t2(BRCorner, ULCorner, BLCorner);
        triangles.push_back(t1);
        triangles.push_back(t2);
    } else {
        cout <<"ERROR"<<numSmallerNeighbours<<endl;
    }
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

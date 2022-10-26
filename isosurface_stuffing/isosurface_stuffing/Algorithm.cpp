#include "Algorithm.hpp"
#include "Tiling.hpp"
#include "Isosurface.hpp"
#include "Point.hpp"
#include <iostream>
#include <cmath>

Algorithm::Algorithm(Tiling &baseTiling, Isosurface &isosurface, float alphaVal) : baseTiling(baseTiling), isosurface(isosurface) {
    allTriangles = baseTiling.getTriangles();
    alpha = alphaVal;
}

void Algorithm::execute() {
    findTrianglesOverlayingIsosurface();
    findCutPoints();
    warpPerimeterTriangles();
    clipPerimeterTriangles();
}

void Algorithm::findTrianglesOverlayingIsosurface() {
    for (int i = 0; i < allTriangles.size(); i++) {
        Triangle curTriangle = allTriangles[i];
        vector<Point> trianglePoints = curTriangle.getPoints();
        int point1Value = isosurface.evaluatePoint(trianglePoints[0]);
        int point2Value = isosurface.evaluatePoint(trianglePoints[1]);
        int point3Value = isosurface.evaluatePoint(trianglePoints[2]);
        
        if (point1Value==1 || point2Value==1 || point3Value==1) {
            processedTriangles.push_back(curTriangle);
        }
    }
}

// TODO: ITERATIVELY INTERPOLATE HERE
Cutpoint Algorithm::findCutpointBetweenPolarPoints(Point positiveVertex, Point negativeVertex) {
    float dx = positiveVertex.getX() - negativeVertex.getX();
    float dy = positiveVertex.getY() - negativeVertex.getY();
    
    float negativeVertexIsosurfaceDistance = abs(isosurface.signedDistanceFunction(negativeVertex));
    float positiveVertexIsosurfaceDistance = abs(isosurface.signedDistanceFunction(positiveVertex));
    
    float cutpointPercentageAlongSimulatedLine = negativeVertexIsosurfaceDistance / (negativeVertexIsosurfaceDistance + positiveVertexIsosurfaceDistance);
    
    float cutpointX = negativeVertex.getX() + cutpointPercentageAlongSimulatedLine*dx;
    float cutpointY = negativeVertex.getY() + cutpointPercentageAlongSimulatedLine*dy;
    
    return Cutpoint(cutpointX, cutpointY, positiveVertex, negativeVertex);
}

void Algorithm::findCutPoints() {
    vector<Triangle*> perimeterTriangles = getPerimeterTrianglesForProcessing();
    
    for (int i = 0; i < perimeterTriangles.size(); i++) {
        Triangle *curTriangle = perimeterTriangles[i];
        vector<Point> trianglePoints = curTriangle->getPoints();
        vector<vector<Point>> slicedPoints = sliceTrianglePointsBySign(trianglePoints);
        
        vector<Point> positiveVertices = slicedPoints[0];
        vector<Point> negativeVertices = slicedPoints[1];
        
        for (int posIndex = 0; posIndex < positiveVertices.size(); posIndex++) {
            for (int negIndex = 0; negIndex < negativeVertices.size(); negIndex++) {
                Cutpoint newCutpoint = findCutpointBetweenPolarPoints(positiveVertices[posIndex], negativeVertices[negIndex]);
                curTriangle->addCutpoint(newCutpoint);
            }
        }
    }
}

void Algorithm::warpPerimeterTriangles() {
    vector<Triangle*> perimeterTriangles = getPerimeterTrianglesForProcessing();
    
    for (int i = 0; i < perimeterTriangles.size(); i++) {
        Triangle *curTriangle = perimeterTriangles[i];
        vector<Point> trianglePoints = curTriangle->getPoints();
        
        for (int j = 0; j < trianglePoints.size(); j++) {
            Point curPoint = trianglePoints[j];
            
            // only warp negative vertices
            if (isosurface.evaluatePoint(curPoint)==-1) {
                
                // find all triangles sharing the negative vertex
                vector<Triangle*> trianglesSharingVertex;
                for (int k = 0; k < perimeterTriangles.size(); k++) {
                    if (perimeterTriangles[k]->doesContainVertex(curPoint)) {
                        trianglesSharingVertex.push_back(perimeterTriangles[k]);
                    }
                }
                
                // find all cutpoints bound by the negative vertex (must check all cp's of all triangles sharing negative vertex)
                vector<Cutpoint> cutpointsToConsider;
                for (int k = 0; k < trianglesSharingVertex.size(); k++) {
                    vector<Cutpoint> potentialCutpointsToConsider = trianglesSharingVertex[k]->getCutpoints();
                    for (int l = 0; l < potentialCutpointsToConsider.size(); l++) {
                        if (potentialCutpointsToConsider[l].isContainedByVertex(curPoint)) {
                            cutpointsToConsider.push_back(potentialCutpointsToConsider[l]);
                        }
                    }
                }
                
                // find cutpoint with smallest distance from negative vertex
                float lowestDistance = MAXFLOAT;
                int lowestDistanceIndex = -1;
                for (int k = 0; k < cutpointsToConsider.size(); k++) {
                    if (distanceBetweenTwoPoints(curPoint, cutpointsToConsider[k]) < lowestDistance) {
                        lowestDistance = distanceBetweenTwoPoints(curPoint, cutpointsToConsider[k]);
                        lowestDistanceIndex = k;
                    }
                }
                
                // if the distance is less than alpha, warp negative vertex to cutpoint
                if (lowestDistanceIndex != -1 && lowestDistance < alpha) {
                    Cutpoint warpingDestination = cutpointsToConsider[lowestDistanceIndex];
                    
                    for (int k = 0; k < trianglesSharingVertex.size(); k++) {
                        trianglesSharingVertex[k]->warpVertexToCutpoint(curPoint, warpingDestination);
                    }
                    
                    // get rid of all cutpoints bound by the negative vertex
                    for (int k = 0; k < cutpointsToConsider.size(); k++) {
                        for (int l = 0; l < perimeterTriangles.size(); l++) {
                            if (perimeterTriangles[l]->doesContainCutpoint(cutpointsToConsider[k])) {
                                perimeterTriangles[l]->removeCutpoint(cutpointsToConsider[k]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Algorithm::clipPerimeterTriangles() {
    vector<Triangle*> perimeterTriangles = getPerimeterTrianglesForProcessing();
    
    for (int i = 0; i < perimeterTriangles.size(); i++) {
        Triangle *curTriangle = perimeterTriangles[i];
        vector<Point> trianglePoints = curTriangle->getPoints();
        vector<vector<Point>> slicedPoints = sliceTrianglePointsBySign(trianglePoints);
        
        vector<Point> positiveVertices = slicedPoints[0];
        vector<Point> negativeVertices = slicedPoints[1];
        
        if (negativeVertices.size()>=1) {
            if (negativeVertices.size()==2) {
                Cutpoint cp1 = findCutpointBetweenPolarPoints(positiveVertices[0], negativeVertices[0]);
                Cutpoint cp2 = findCutpointBetweenPolarPoints(positiveVertices[0], negativeVertices[1]);
                
                Triangle newTriangle = Triangle(cp1, cp2, positiveVertices[0]);
                processedTriangles.push_back(newTriangle);
            } else if (negativeVertices.size()==1) {
                Cutpoint cp1 = findCutpointBetweenPolarPoints(positiveVertices[0], negativeVertices[0]);
                Cutpoint cp2 = findCutpointBetweenPolarPoints(positiveVertices[1], negativeVertices[0]);
                
                // TODO: DELAUNAY'S CONDITION
                Triangle newTriangle1 = Triangle(cp1, positiveVertices[1], positiveVertices[0]);
                Triangle newTriangle2 = Triangle(cp1, cp2, positiveVertices[1]);
                
                processedTriangles.push_back(newTriangle1);
                processedTriangles.push_back(newTriangle2);
            }
        }
    }
    filterOutNegativeTriangles();
}

void Algorithm::filterOutNegativeTriangles() {
    vector<Triangle> newProcessedTriangles;
    for (int i = 0; i < processedTriangles.size(); i++) {
        vector<Point> trianglePoints = processedTriangles[i].getPoints();
        if (isosurface.evaluatePoint(trianglePoints[0])!=-1 && isosurface.evaluatePoint(trianglePoints[1])!=-1 && isosurface.evaluatePoint(trianglePoints[2])!=-1) {
            newProcessedTriangles.push_back(processedTriangles[i]);
        }
    }
    processedTriangles = newProcessedTriangles;
}

vector<vector<Point>> Algorithm::sliceTrianglePointsBySign(vector<Point> trianglePoints) {
    int point1Value = isosurface.evaluatePoint(trianglePoints[0]);
    int point2Value = isosurface.evaluatePoint(trianglePoints[1]);
    int point3Value = isosurface.evaluatePoint(trianglePoints[2]);
    
    vector<Point> positiveVertices;
    vector<Point> negativeVertices;
    
    if (point1Value == -1) negativeVertices.push_back(trianglePoints[0]);
    if (point1Value == 1) positiveVertices.push_back(trianglePoints[0]);
    if (point2Value == -1) negativeVertices.push_back(trianglePoints[1]);
    if (point2Value == 1) positiveVertices.push_back(trianglePoints[1]);
    if (point3Value == -1) negativeVertices.push_back(trianglePoints[2]);
    if (point3Value == 1) positiveVertices.push_back(trianglePoints[2]);
    
    vector<vector<Point>> slicedPoints;
    slicedPoints.push_back(positiveVertices);
    slicedPoints.push_back(negativeVertices);
    
    return slicedPoints;
}

vector<Triangle*> Algorithm::getPerimeterTrianglesForProcessing() {
    vector<Triangle*> perimeterTriangles;
    for (int i = 0; i < processedTriangles.size(); i++) {
        Triangle *curTriangle = &processedTriangles[i];
        vector<Point> trianglePoints = curTriangle->getPoints();
        int point1Value = isosurface.evaluatePoint(trianglePoints[0]);
        int point2Value = isosurface.evaluatePoint(trianglePoints[1]);
        int point3Value = isosurface.evaluatePoint(trianglePoints[2]);
        
        if (point1Value==-1 || point2Value==-1 || point3Value==-1) {
            perimeterTriangles.push_back(curTriangle);
        }

    }
    return perimeterTriangles;
}

float Algorithm::distanceBetweenTwoPoints(Point p1, Point p2) {
    float dx = p2.getX() - p1.getX();
    float dy = p2.getY() - p1.getY();
    return sqrt(dx*dx + dy*dy);
}

vector<Triangle> Algorithm::getProcessedTriangles() {
    return processedTriangles;
}

void Algorithm::renderProcessedTriangles() {
    for (int i = 0; i < processedTriangles.size(); i++) {
        processedTriangles[i].render();
    }
}

void Algorithm::renderProcessedTriangleCutpoints() {
    for (int i = 0; i < processedTriangles.size(); i++) {
        processedTriangles[i].renderCutpoints();
    }
}


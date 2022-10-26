#include "Algorithm.hpp"
#include "Tiling.hpp"
#include "Isosurface.hpp"
#include "Point.hpp"
#include <iostream>
#include <cmath>

Algorithm::Algorithm(Tiling &baseTiling, Isosurface &isosurface) : baseTiling(baseTiling), isosurface(isosurface) {
    allTriangles = baseTiling.getTriangles();
}

void Algorithm::execute() {
    findTrianglesOverlayingIsosurface();
    findCutPoints();
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

// NEED TO ITERATIVELY INTERPOLATE HERE
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
        for (int posIndex = 0; posIndex < positiveVertices.size(); posIndex++) {
            for (int negIndex = 0; negIndex < negativeVertices.size(); negIndex++) {
                Cutpoint newCutpoint = findCutpointBetweenPolarPoints(positiveVertices[posIndex], negativeVertices[negIndex]);
                curTriangle->addCutpoint(newCutpoint);
            }
        }
    }
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


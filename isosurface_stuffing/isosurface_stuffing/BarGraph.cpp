#include "BarGraph.hpp"
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

BarGraph::BarGraph(vector<Triangle> curTriangles, int width, int height, int xOffset, int barCount) {
    triangles = curTriangles;
    screenWidth = width;
    screenHeight = height;
    xStartPos = xOffset;
    numBars = barCount;
    angleWindowPerBar = 180 / barCount;
    
    computeAngles();
    distributeGraphValues();
}

void BarGraph::computeAngles() {
    for (int i = 0; i < triangles.size(); i++) {
        Triangle curTriangle = triangles[i];
        vector<Point> points = curTriangle.getPoints();
        
        float dx1 = points[0].getX() - points[1].getX();
        float dy1 = points[0].getY() - points[1].getY();
        
        float dx2 = points[1].getX() - points[2].getX();
        float dy2 = points[1].getY() - points[2].getY();
        
        float dx3 = points[2].getX() - points[0].getX();
        float dy3 = points[2].getY() - points[0].getY();
        
        float a = sqrt(dx1*dx1 + dy1*dy1);
        float b = sqrt(dx2*dx2 + dy2*dy2);
        float c = sqrt(dx3*dx3 + dy3*dy3);
        
        float angle1 = applyCosineLaw(a, b, c);
        float angle2 = applyCosineLaw(b, c, a);
        float angle3 = applyCosineLaw(c, a, b);
                
        angles.push_back(angle1);
        angles.push_back(angle2);
        angles.push_back(angle3);
    }
}

void BarGraph::distributeGraphValues() {
    for (int i = 0; i < angles.size(); i++) {
        int key = round(angles[i]) / angleWindowPerBar;
        if (graphValues.count(key)) {
            graphValues[key] += 1;
        } else {
            graphValues[key] = 1;
        }
    }
    
    // get median value
    int graphValuesArray[numBars];
    
    int i = 0;
    for(std::map<int,int>::iterator it = graphValues.begin(); it != graphValues.end(); ++it) {
        graphValuesArray[i++] = it->second;
    }
    
    for (int count = 1; count <= numBars; count++) {
        for (int i = 0; i < numBars-1; i++) {
            if (graphValuesArray[i] > graphValuesArray[i+1]) {
                int temp = graphValuesArray[i];
                graphValuesArray[i] = graphValuesArray[i+1];
                graphValuesArray[i+1] = temp;
            }
        }
    }
    
    medianValue = graphValuesArray[numBars/2];
    
    // get maxVal of non-dwarf bar
    int maxVal = -1;
    
    for(std::map<int,int>::iterator it = graphValues.begin(); it != graphValues.end(); ++it) {
        if (it->second > maxVal && it->second <= medianValue*4) maxVal = it->second;
    }
    
    maxGraphValue = maxVal;
}

void BarGraph::drawGraphTemplate() {
    glColor3f(1, 1, 1);
    
    glBegin(GL_QUADS);
        glVertex2f(xStartPos + horizontalOffset, verticalOffset);
        glVertex2f(xStartPos + screenWidth - horizontalOffset, verticalOffset);
        glVertex2f(xStartPos + screenWidth - horizontalOffset, verticalOffset + templateThickness);
        glVertex2f(xStartPos + horizontalOffset, verticalOffset + templateThickness);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex2f(xStartPos + horizontalOffset, verticalOffset);
        glVertex2f(xStartPos + horizontalOffset + templateThickness, verticalOffset);
        glVertex2f(xStartPos + horizontalOffset + templateThickness, screenHeight - verticalOffset);
        glVertex2f(xStartPos + horizontalOffset, screenHeight - verticalOffset);
    glEnd();
}

void BarGraph::drawGraph() {
    drawGraphTemplate();
    
    glColor3f(0.5, 0.5, 0.5);
    
    float graphHeight = screenHeight - 2*verticalOffset - templateThickness;
    float graphWidth = screenWidth - 2*horizontalOffset - templateThickness;
    float valueOfVerticalPixel = graphHeight / maxGraphValue;
    float barWidth = graphWidth / numBars;
    float graphStartPosX = xStartPos + horizontalOffset + templateThickness + barWidth/2;
    float graphStartPosY = verticalOffset + templateThickness;
    
    for(std::map<int,int>::iterator it = graphValues.begin(); it != graphValues.end(); ++it) {
        bool isDwarfBar = it->second > medianValue*4;
        if (isDwarfBar) glColor3f(1, 0.5, 0.5);
        else glColor3f(0.5, 0.5, 0.5);
        
        float curBarStartPos = graphStartPosX + barWidth*(it->first);
        glBegin(GL_QUADS);
        glVertex2f(curBarStartPos, graphStartPosY);
        glVertex2f(curBarStartPos + barWidth/2, graphStartPosY);
        if (isDwarfBar) {
            glVertex2f(curBarStartPos + barWidth/2, graphStartPosY + valueOfVerticalPixel*(it->second/20));
            glVertex2f(curBarStartPos, graphStartPosY + valueOfVerticalPixel*(it->second/20));
        } else {
            glVertex2f(curBarStartPos + barWidth/2, graphStartPosY + valueOfVerticalPixel*(it->second));
            glVertex2f(curBarStartPos, graphStartPosY + valueOfVerticalPixel*(it->second));
        }
        glEnd();
    }
}

float BarGraph::applyCosineLaw(float a, float b, float c) {
    return (acos((b*b + c*c - a*a) / (2*b*c))) * (180/M_PI);
}

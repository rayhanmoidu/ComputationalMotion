//
//  RenderTriangle.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-12-13.
//

#include "RenderTriangle.hpp"
#include <time.h>
#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

RenderTriangle::RenderTriangle(vector<pair<float, float>> vertices, Triangle baseTriangle) {
    vector<int> baseIndices = baseTriangle.getIndices();
    pair<float, float> p1Pair = vertices[baseIndices[0]];
    pair<float, float> p2Pair = vertices[baseIndices[1]];
    pair<float, float> p3Pair = vertices[baseIndices[2]];
    p1 = Point(p1Pair.first, p1Pair.second);
    p2 = Point(p2Pair.first, p2Pair.second);
    p3 = Point(p3Pair.first, p3Pair.second);
    cutpoints = baseTriangle.getCutpoints();
    
    setColors();
}

void RenderTriangle::setColors() {
    colorkey1 = (float)(rand() % 100) / 100;
    colorkey2 = (float)(rand() % 100) / 100;
    colorkey3 = (float)(rand() % 100) / 100;
}

void RenderTriangle::render() {
    glColor3f(colorkey1, colorkey2, colorkey3);

    glBegin(GL_TRIANGLES);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p3.getX(), p3.getY());
    glEnd();

    renderCutpoints();
}

void RenderTriangle::renderCutpoints() {
    for (int i = 0; i < cutpoints.size(); i++) {
        Cutpoint curCutpoint = cutpoints[i];
        float xToPlot = curCutpoint.getX();
        float yToPlot = curCutpoint.getY();
        
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(xToPlot-4, yToPlot-4);
        glVertex2f(xToPlot+4, yToPlot-4);
        glVertex2f(xToPlot+4, yToPlot+4);
        glVertex2f(xToPlot-4, yToPlot+4);
        glEnd();
    }
}

float RenderTriangle::applyCosineLaw(float a, float b, float c) {
    return (acos((b*b + c*c - a*a) / (2*b*c))) * (180/M_PI);
}

vector<float> RenderTriangle::computeAngles() {
    vector<float> angles;
    
    float dx1 = p1.getX() - p2.getX();
    float dy1 = p1.getY() - p2.getY();
    
    float dx2 = p2.getX() - p3.getX();
    float dy2 = p2.getY() - p3.getY();
    
    float dx3 = p3.getX() - p1.getX();
    float dy3 = p3.getY() - p1.getY();
    
    float a = sqrt(dx1*dx1 + dy1*dy1);
    float b = sqrt(dx2*dx2 + dy2*dy2);
    float c = sqrt(dx3*dx3 + dy3*dy3);
    
    float angle1 = applyCosineLaw(a, b, c);
    float angle2 = applyCosineLaw(b, c, a);
    float angle3 = applyCosineLaw(c, a, b);
    
    angles.push_back(angle1);
    angles.push_back(angle2);
    angles.push_back(angle3);
    
    return angles;
}


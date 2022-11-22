#include "Triangle.hpp"
#include "Point.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Triangle::Triangle(Point triangleP1, Point triangleP2, Point triangleP3) {
    p1 = triangleP1;
    p2 = triangleP2;
    p3 = triangleP3;
    cutpoints = vector<Cutpoint>();
    setColors();
    doesExistVertexBetweenP1P2 = false;
    doesExistVertexBetweenP2P3 = false;
    doesExistVertexBetweenP1P3 = false;
    twins = vector<Triangle>();
}

Triangle::Triangle() {
    p1 = Point();
    p2 = Point();
    p3 = Point();
    cutpoints = vector<Cutpoint>();
    setColors();
    doesExistVertexBetweenP1P2 = false;
    doesExistVertexBetweenP2P3 = false;
    doesExistVertexBetweenP1P3 = false;
    twins = vector<Triangle>();
}

void Triangle::setColors() {
    colorkey1 = (float)(rand() % 100) / 100;
    colorkey2 = (float)(rand() % 100) / 100;
    colorkey3 = (float)(rand() % 100) / 100;
}

void Triangle::render() {
    glColor3f(colorkey1, colorkey2, colorkey3);

    glBegin(GL_TRIANGLES);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p3.getX(), p3.getY());
    glEnd();

    renderCutpoints();
}

void Triangle::renderCutpoints() {
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

void Triangle::setPoints(Point point1, Point point2, Point point3) {
    p1 = point1;
    p2 = point2;
    p3 = point3;
}

vector<Point> Triangle::getPoints() {
    vector<Point> points = vector<Point>();
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

void Triangle::addCutpoint(Cutpoint newCutpoint) {
    cutpoints.push_back(newCutpoint);
}

vector<Cutpoint> Triangle::getCutpoints() {
    return cutpoints;
}

bool Triangle::doesContainVertex(Point p) {
    return p1==p || p2==p || p3==p;
}

bool Triangle::doesContainCutpoint(Cutpoint cp) {
    for (int i = 0; i < cutpoints.size(); i++) {
        if (cutpoints[i]==cp) return true;
    }
    return false;
}

void Triangle::warpVertexToCutpoint(Point p, Cutpoint cp) {
    if (p1==p) p1 = Point(cp.getX(), cp.getY());
    if (p2==p) p2 = Point(cp.getX(), cp.getY());
    if (p3==p) p3 = Point(cp.getX(), cp.getY());
}

void Triangle::removeCutpoint(Cutpoint cp) {
    vector<Cutpoint> newCutpoints;
    for (int i = 0; i < cutpoints.size(); i++) {
        if (!(cutpoints[i]==cp)) {
            newCutpoints.push_back(cutpoints[i]);
        }
    }
    cutpoints = newCutpoints;
}

void Triangle::removeAllCutpoints() {
    cutpoints = vector<Cutpoint>();
}

bool Triangle::operator == (Triangle &obj) {
    bool doCutpointsMatch = true;
    for (int i = 0; i < cutpoints.size(); i++) {
        bool foundCurCutpoint = false;
        for (int j = 0; j < obj.cutpoints.size(); j++) {
            if (cutpoints[i]==obj.cutpoints[j]) {
                foundCurCutpoint = true;
            }
        }
        if (!foundCurCutpoint) doCutpointsMatch = false;
    }
    
    bool pointsMatch1 = (p1==obj.p1) || (p1==obj.p2) || (p1==obj.p3);
    bool pointsMatch2 = (p2==obj.p1) || (p2==obj.p2) || (p2==obj.p3);
    bool pointsMatch3 = (p3==obj.p1) || (p3==obj.p2) || (p3==obj.p3);

    
    return (pointsMatch1 && pointsMatch2 && pointsMatch3) && doCutpointsMatch;
}

bool Triangle::doTriangleVerticesMatch(Triangle t2) {
    bool pointsMatch1 = (p1==t2.p1) || (p1==t2.p2) || (p1==t2.p3);
    bool pointsMatch2 = (p2==t2.p1) || (p2==t2.p2) || (p2==t2.p3);
    bool pointsMatch3 = (p3==t2.p1) || (p3==t2.p2) || (p3==t2.p3);

    
    return (pointsMatch1 && pointsMatch2 && pointsMatch3);
}

float Triangle::applyCosineLaw(float a, float b, float c) {
    return (acos((b*b + c*c - a*a) / (2*b*c))) * (180/M_PI);
}

vector<float> Triangle::computeAngles() {
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

void Triangle::setDoesExistVertexBetweenP1P2(bool doesExist) {
    doesExistVertexBetweenP1P2 = doesExist;
}
void Triangle::setDoesExistVertexBetweenP2P3(bool doesExist) {
    doesExistVertexBetweenP2P3 = doesExist;
}
void Triangle::setDoesExistVertexBetweenP1P3(bool doesExist) {
    doesExistVertexBetweenP1P3 = doesExist;
}

bool Triangle::getDoesExistVertexBetweenP1P2() {
    return doesExistVertexBetweenP1P2;
}
bool Triangle::getDoesExistVertexBetweenP2P3() {
    return doesExistVertexBetweenP2P3;
}
bool Triangle::getDoesExistVertexBetweenP1P3() {
    return doesExistVertexBetweenP1P3;
}

void Triangle::addTwin(Triangle newTwin) {
    twins.push_back(newTwin);
}
vector<Triangle> Triangle::getTwins() {
    return twins;
}

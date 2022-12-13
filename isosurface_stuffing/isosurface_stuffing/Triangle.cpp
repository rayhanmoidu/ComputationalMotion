#include "Triangle.hpp"
#include "Point.hpp"
#include <stdlib.h>

Triangle::Triangle(int index1, int index2, int index3) {
    i1 = index1;
    i2 = index2;
    i3 = index3;
    cutpoints = vector<Cutpoint>();
}

Triangle::Triangle() {
    i1 = 0;
    i2 = 0;
    i3 = 0;
    cutpoints = vector<Cutpoint>();
}

void Triangle::setIndices(int index1, int index2, int index3) {
    i1 = index1;
    i2 = index2;
    i3 = index3;
}

vector<int> Triangle::getIndices() {
    vector<int> indices = vector<int>();
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
    return indices;
}

void Triangle::addCutpoint(Cutpoint newCutpoint) {
    cutpoints.push_back(newCutpoint);
}

vector<Cutpoint> Triangle::getCutpoints() {
    return cutpoints;
}

bool Triangle::doesContainIndex(int i) {
    return i1==i || i2==i || i3==i;
}

bool Triangle::doesContainCutpoint(Cutpoint cp) {
    for (int i = 0; i < cutpoints.size(); i++) {
        if (cutpoints[i]==cp) return true;
    }
    return false;
}

void Triangle::warpVertexToCutpoint(int oldIndex, int newIndex) {
    if (i1==oldIndex) {
        i1 = newIndex;
    }
    if (i2==oldIndex) {
        i2 = newIndex;
    }
    if (i3==oldIndex) {
        i3 = newIndex;
    }
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
    
    bool indicesMatch1 = (i1==obj.i1) || (i1==obj.i2) || (i1==obj.i3);
    bool indicesMatch2 = (i2==obj.i1) || (i2==obj.i2) || (i2==obj.i3);
    bool indicesMatch3 = (i3==obj.i1) || (i3==obj.i2) || (i3==obj.i3);

    
    return (indicesMatch1 && indicesMatch2 && indicesMatch3) && doCutpointsMatch;
}

bool Triangle::doIndicesMatch(Triangle obj) {
    bool indicesMatch1 = (i1==obj.i1) || (i1==obj.i2) || (i1==obj.i3);
    bool indicesMatch2 = (i2==obj.i1) || (i2==obj.i2) || (i2==obj.i3);
    bool indicesMatch3 = (i3==obj.i1) || (i3==obj.i2) || (i3==obj.i3);

    return (indicesMatch1 && indicesMatch2 && indicesMatch3);
}

vector<Point> Triangle::getPoints(vector<pair<float, float>> vertices) {
    pair<float, float> p1Pair = vertices[i1];
    pair<float, float> p2Pair = vertices[i2];
    pair<float, float> p3Pair = vertices[i3];
    Point p1(p1Pair.first, p1Pair.second);
    Point p2(p2Pair.first, p2Pair.second);
    Point p3(p3Pair.first, p3Pair.second);
    
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    
    return points;
}

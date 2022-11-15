#include "Tiling.hpp"

Tiling::Tiling(int width, int height, int triangleSize) {
    triangles = vector<Triangle>();
    vertices = vector<Point>();
    hBound = width;
    vBound = height;
    triangleSideLength = triangleSize;
}

vector<Triangle> Tiling::getTriangles() {
    return triangles;
}

void Tiling::render() {
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].render();
    }
}

void Tiling::addVertex(Point p) {
    bool didFind = false;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]==p) {
            didFind=true;
            break;
        }
    }
    if (!didFind) vertices.push_back(p);
}

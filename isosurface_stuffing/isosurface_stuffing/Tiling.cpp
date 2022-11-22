#include "Tiling.hpp"

Tiling::Tiling(int width, int height, int triangleSize) {
    triangles = vector<Triangle>();
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
    vertices.insert(pair<float, float>(p.getX(), p.getY()));
}

vector<Triangle> Tiling::removeTriangle(vector<Triangle> curTriangles, Triangle triangleToRemove) {
    std::vector<Triangle> newTriangles;

    for (int i = 0; i < curTriangles.size(); i++) {
        if (!curTriangles[i].doTriangleVerticesMatch(triangleToRemove)) {
            newTriangles.push_back(curTriangles[i]);
        }
    }

    return newTriangles;
}

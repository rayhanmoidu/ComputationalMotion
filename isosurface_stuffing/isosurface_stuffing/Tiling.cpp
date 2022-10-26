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

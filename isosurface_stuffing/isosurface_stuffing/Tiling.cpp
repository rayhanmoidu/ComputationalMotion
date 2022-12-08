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
    verticesSet.insert(pair<float, float>(p.getX(), p.getY()));
    vertices.push_back(pair<float, float>(p.getX(), p.getY()));
    pair<pair<float, float>, int> mapInsertion(pair<float, float>(p.getX(), p.getY()), vertices.size()-1);
    verticesToIndexInList.insert(mapInsertion);
}

int Tiling::findVertexIndex(Point p) {
    pair<float, float> key(p.getX(), p.getY());
    return verticesToIndexInList.at(key);
}

int Tiling::check_addVertex_getIndex(Point p) {
    if (verticesSet.count(pair<float, float>(p.getX(), p.getY()))) {
        return findVertexIndex(p);
    } else {
        addVertex(p);
        return int(vertices.size() - 1);
    }
}

int Tiling::addVertex_getIndex(Point p) {
    addVertex(p);
    return int(vertices.size() - 1);
}

vector<pair<float, float>> Tiling::getVertices() {
    return vertices;
}

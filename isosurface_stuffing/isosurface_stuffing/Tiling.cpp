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

void Tiling::addVertex(pair<float, float> p) {
    pair<float, float> p1(std::ceil(p.first * 10.0) / 10.0, std::ceil(p.second * 10.0) / 10.0);
    verticesSet.insert(p1);
    vertices.push_back(p);
    pair<pair<float, float>, int> mapInsertion(p1, vertices.size()-1);
    verticesToIndexInList.insert(mapInsertion);
}

int Tiling::findVertexIndex(Point p) {
    pair<float, float> key(p.getX(), p.getY());
    return verticesToIndexInList.at(key);
}

int Tiling::check_addVertex_getIndex(Point p) {
    Point p1(std::ceil(p.getX() * 10.0) / 10.0, std::ceil(p.getY() * 10.0) / 10.0);
    if (doesVertexExist(p1)) {
        return findVertexIndex(p1);
    } else {
        addVertex(pair<float, float>(p.getX(), p.getY()));
        return int(vertices.size() - 1);
    }
}
bool Tiling::doesVertexExist(Point p) {
    return verticesSet.count(pair<float, float>(p.getX(), p.getY()));
}

int Tiling::addVertex_getIndex(Point p) {
    addVertex(pair<float, float>(p.getX(), p.getY()));
    return int(vertices.size() - 1);
}

vector<pair<float, float>> Tiling::getVertices() {
    return vertices;
}

Point Tiling::getVertex(int i) {
    return Point(vertices[i].first, vertices[i].second);
}

//
//  ProvablyGoodTest.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#ifndef ProvablyGoodTriangleFactory_hpp
#define ProvablyGoodTriangleFactory_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Triangle.hpp"
#include "QuadtreeTiling.hpp"

enum CellConfiguration { ABAB, ABCB, BBCC, BBBB, ABBB, AABB, AAAA, AAAB, BBBC };

class ProvablyGoodTriangleFactory {
public:
    ProvablyGoodTriangleFactory();
    ProvablyGoodTriangleFactory(QuadtreeTiling*);
    vector<Triangle> triangulate(CellConfiguration, Point, float, float);
    void render(vector<Triangle> triangles);
private:
    vector<Triangle> triangulate_ABAB(Point, float, float);
    vector<Triangle> triangulate_ABCB(Point, float, float);
    vector<Triangle> triangulate_BBCC(Point, float, float);
    vector<Triangle> triangulate_BBBB(Point, float, float);
    vector<Triangle> triangulate_ABBB(Point, float, float);
    vector<Triangle> triangulate_AABB(Point, float, float);
    vector<Triangle> triangulate_AAAA(Point, float, float);
    vector<Triangle> triangulate_AAAB(Point, float, float);
    vector<Triangle> triangulate_BBBC(Point, float, float);
    bool verifyAngles(vector<Triangle> triangles);
    QuadtreeTiling *tiling;
};


#endif /* ProvablyGoodTriangleFactory_hpp */

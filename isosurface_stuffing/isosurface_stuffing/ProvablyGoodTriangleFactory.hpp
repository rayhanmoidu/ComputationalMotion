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

enum CellConfiguration { ABAB, ABCB, BBCC, BBBB, ABBB, AABB, AAAA, AAAB, BBBC };


class ProvablyGoodTriangleFactory {
public:
    ProvablyGoodTriangleFactory(CellConfiguration, Point, float, float);
    void render();
private:
    void triangulate_ABAB(Point, float, float);
    void triangulate_ABCB(Point, float, float);
    void triangulate_BBCC(Point, float, float);
    void triangulate_BBBB(Point, float, float);
    void triangulate_ABBB(Point, float, float);
    void triangulate_AABB(Point, float, float);
    void triangulate_AAAA(Point, float, float);
    void triangulate_AAAB(Point, float, float);
    void triangulate_BBBC(Point, float, float);
    bool verifyAngles();
    
    vector<Triangle> triangles;
};


#endif /* ProvablyGoodTriangleFactory_hpp */

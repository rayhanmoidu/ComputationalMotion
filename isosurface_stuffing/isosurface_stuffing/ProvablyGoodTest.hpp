//
//  ProvablyGoodTest.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#ifndef ProvablyGoodTest_hpp
#define ProvablyGoodTest_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Triangle.hpp"

enum CellConfiguration { ABAB, ABCB, BBCC, BBBB, ABBB, AABB };


class ProvablyGoodTest {
public:
    ProvablyGoodTest(CellConfiguration, Point, float);
    void render();
private:
    void triangulate_ABAB(Point, float);
    void triangulate_ABCB(Point, float);
    void triangulate_BBCC(Point, float);
    void triangulate_BBBB(Point, float);
    void triangulate_ABBB(Point, float);
    void triangulate_AABB(Point, float);
    bool verifyAngles();
    
    vector<Triangle> triangles;
};


#endif /* ProvablyGoodTest_hpp */

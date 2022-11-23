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

enum CellConfiguration { ABAB };


class ProvablyGoodTest {
public:
    ProvablyGoodTest(CellConfiguration, Point, float);
private:
    void triangulate_ABAB(Point, float);
    bool verifyAngles(vector<Triangle>);
};


#endif /* ProvablyGoodTest_hpp */

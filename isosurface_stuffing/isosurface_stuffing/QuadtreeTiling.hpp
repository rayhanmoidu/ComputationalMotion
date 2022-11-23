//
//  QuadtreeTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-02.
//

#ifndef QuadtreeTiling_hpp
#define QuadtreeTiling_hpp

#include <stdio.h>
#include "Quadtree.hpp"
#include "Tiling.hpp"
#include "Point.hpp"
#include <unordered_set>
#include <utility>

class QuadtreeTiling : public Tiling {
public:
    QuadtreeTiling();
    void createTiling(float, float, string, string) override;
    
protected:
    void createTilingHelper(QuadtreeNode*);
    vector<Point> findTriangleMidpointsThatAreVertices(Point, Point, Point);
    
    virtual void createTrianglesFromCell(QuadtreeNode*) = 0;
    virtual void satisfyJunctions() = 0;
};

#endif /* QuadtreeTiling_hpp */

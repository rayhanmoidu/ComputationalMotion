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

enum QuadtreeTilingType { isoscelesSingle, isoscelesDouble, equilateral, provablyGood};

class QuadtreeTiling : public Tiling {
public:
    QuadtreeTiling(Quadtree, QuadtreeTilingType);
    void createTiling(float, float, string, string) override;
private:
    void createTilingHelper(QuadtreeNode*, QuadtreeTilingType);
    void createTrianglesFromCell_isoscelesSingle(QuadtreeNode*);
    void createTrianglesFromCell_isoscelesDouble(QuadtreeNode*);
    void createTrianglesFromCell_equilateral(QuadtreeNode*);
    void createTrianglesFromCell_provablyGood(QuadtreeNode*);
};

#endif /* QuadtreeTiling_hpp */

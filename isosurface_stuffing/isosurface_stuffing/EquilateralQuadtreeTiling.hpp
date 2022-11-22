//
//  EquilateralQuadtreeTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#ifndef EquilateralQuadtreeTiling_hpp
#define EquilateralQuadtreeTiling_hpp

#include <stdio.h>
#include "QuadtreeTiling.hpp"
#include "Quadtree.hpp"
#include "ParallelogramQuadtree.hpp"

class EquilateralQuadtreeTiling : public QuadtreeTiling {
public:
    EquilateralQuadtreeTiling(ParallelogramQuadtree);
    void createTrianglesFromCell(QuadtreeNode*) override;
    void satisfyJunctions() override;
    void rebalanceQuadtree(ParallelogramQuadtree);
};

#endif /* EquilateralQuadtreeTiling_hpp */

//
//  IsoscelesSingleQuadtreeTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#ifndef IsoscelesSingleQuadtreeTiling_hpp
#define IsoscelesSingleQuadtreeTiling_hpp

#include <stdio.h>
#include "QuadtreeTiling.hpp"
#include "Quadtree.hpp"
#include "SquareQuadtree.hpp"

class IsoscelesSingleQuadtreeTiling : public QuadtreeTiling {
public:
    IsoscelesSingleQuadtreeTiling(SquareQuadtree);
    void createTrianglesFromCell(QuadtreeNode*) override;
    void satisfyJunctions() override;
};

#endif /* IsoscelesSingleQuadtreeTiling_hpp */

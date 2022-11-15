//
//  IsoscelesDoubleQuadtreeTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#ifndef IsoscelesDoubleQuadtreeTiling_hpp
#define IsoscelesDoubleQuadtreeTiling_hpp

#include <stdio.h>
#include "QuadtreeTiling.hpp"
#include "Quadtree.hpp"

class IsoscelesDoubleQuadtreeTiling : public QuadtreeTiling {
public:
    IsoscelesDoubleQuadtreeTiling(Quadtree);
    void createTrianglesFromCell(QuadtreeNode*) override;
    void satisfyJunctions() override;
};

#endif /* IsoscelesDoubleQuadtreeTiling_hpp */

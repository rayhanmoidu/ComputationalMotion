//
//  ProvablyGoodQuadtreeTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-30.
//

#ifndef ProvablyGoodQuadtreeTiling_hpp
#define ProvablyGoodQuadtreeTiling_hpp

#include <stdio.h>
#include "QuadtreeTiling.hpp"
#include "Quadtree.hpp"
#include "SquareQuadtree.hpp"
#include "ProvablyGoodTriangleFactory.hpp"

class ProvablyGoodQuadtreeTiling : public QuadtreeTiling {
public:
    ProvablyGoodQuadtreeTiling(SquareQuadtree);
    void createTrianglesFromCell(QuadtreeNode*) override;
private:
    void stronglyBalance(SquareQuadtree);
    string getSideLabel(vector<QuadtreeNode*>, QuadtreeNode*);
    bool isRotationValid(string);
    CellConfiguration getConfiguration(string);
    const string validConfigurations[9] = {"ABAB", "ABCB", "BBCC", "BBBB", "ABBB", "AABB", "AAAA", "AAAB", "BBBC"};
    
    ProvablyGoodTriangleFactory triangulator;
};
#endif /* ProvablyGoodQuadtreeTiling_hpp */

//
//  SquareQuadtree.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#ifndef SquareQuadtree_hpp
#define SquareQuadtree_hpp
#include "Quadtree.hpp"

#include <stdio.h>

class SquareQuadtree: public Quadtree {
public:
    SquareQuadtree(int, int, int, Isosurface&);
    SquareQuadtree(int, int, int, int, float (*)(float, float), int, float, float);
    
    void render() override;
    bool shouldRefine(QuadtreeNode*) override;
    void constructChildren(QuadtreeNode*) override;
    void renderHelper(QuadtreeNode*) override;
    void colorSquare(QuadtreeNode) override;
    void refineNode(QuadtreeNode*) override;
};


#endif /* SquareQuadtree_hpp */

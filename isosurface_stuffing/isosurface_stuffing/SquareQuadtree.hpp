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
    
    void render() override;
    bool shouldRefine(QuadtreeNode*) override;
    void constructChildren(QuadtreeNode*) override;
    void renderHelper(QuadtreeNode*) override;
    void colorSquare(QuadtreeNode) override;
};


#endif /* SquareQuadtree_hpp */

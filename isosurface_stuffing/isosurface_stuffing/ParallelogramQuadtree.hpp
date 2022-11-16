//
//  ParallelogramQuadtree.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-15.
//

#ifndef ParallelogramQuadtree_hpp
#define ParallelogramQuadtree_hpp

#include <stdio.h>
#include "Quadtree.hpp"
#include <cmath>

#include <stdio.h>

class ParallelogramQuadtree: public Quadtree {
public:
    ParallelogramQuadtree(int, int, int, Isosurface&);
    
    void render() override;
    bool shouldRefine(QuadtreeNode*) override;
    void constructChildren(QuadtreeNode*) override;
    void renderHelper(QuadtreeNode*) override;
    void colorSquare(QuadtreeNode) override;
    
    void renderHelper2(QuadtreeNode*, int);
    
    float getCellHeight(QuadtreeNode*);
    const float tan60 = sqrt(3);
    const float tan30 = 1/sqrt(3);
};

#endif /* ParallelogramQuadtree_hpp */

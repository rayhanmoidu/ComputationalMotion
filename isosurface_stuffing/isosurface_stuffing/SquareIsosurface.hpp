//
//  SquareIsosurface.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#ifndef SquareIsosurface_hpp
#define SquareIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"

class SquareIsosurface : public Isosurface {
public:
    SquareIsosurface(int=0, int=0, int=0, int=0, float=0);
    float signedDistanceFunction(Point) override;
private:
    int rectangleWidth;
    int rectangleHeight;
};


#endif /* SquareIsosurface_hpp */

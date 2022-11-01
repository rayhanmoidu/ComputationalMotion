//
//  RectangleIsosurface.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-01.
//

#ifndef RectangleIsosurface_hpp
#define RectangleIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"

class RectangleIsosurface : public Isosurface {
public:
    RectangleIsosurface(int, int, int, int, float);
    float signedDistanceFunction(Point) override;
private:
    int rectangleWidth;
    int rectangleHeight;
};

#endif /* RectangleIsosurface_hpp */

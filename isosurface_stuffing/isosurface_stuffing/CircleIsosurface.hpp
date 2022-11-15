//
//  CircleIsosurface.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-10-25.
//

#ifndef CircleIsosurface_hpp
#define CircleIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"

class CircleIsosurface : public Isosurface {
public:
    CircleIsosurface(int=0, int=0, int=0, float=0);
    float signedDistanceFunction(Point) override;
private:
    int radius;
};


#endif /* CircleIsosurface_hpp */

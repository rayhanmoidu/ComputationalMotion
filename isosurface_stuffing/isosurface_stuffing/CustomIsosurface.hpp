//
//  CustomIsosurface.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-12-07.
//

#ifndef CustomIsosurface_hpp
#define CustomIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"

class CustomIsosurface : public Isosurface {
public:
    CustomIsosurface(float (*)(float, float), float, float);
    float signedDistanceFunction(Point) override;
private:
    float (*customSignedDistanceFunction)(float, float);
    float originX;
    float originY;
};


#endif /* CustomIsosurface_hpp */

//
//  IsoscelesTiling.hpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-01.
//

#ifndef IsoscelesTiling_hpp
#define IsoscelesTiling_hpp

#include <stdio.h>
#include "Tiling.hpp"

class IsoscelesTiling : public Tiling {
public:
    IsoscelesTiling(int, int, int);
    void createTiling(float, float, string, string) override;
};

#endif /* IsoscelesTiling_hpp */

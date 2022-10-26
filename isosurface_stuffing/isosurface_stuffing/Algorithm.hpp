#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <stdio.h>
#include "Tiling.hpp"
#include "Isosurface.hpp"

class Algorithm {
public:
    Algorithm(Tiling&, Isosurface&);
    void execute();
    
    void renderProcessedTriangles();
    void renderProcessedTriangleCutpoints();
    
    // getters
    vector<Triangle> getProcessedTriangles();
    
private:
    Tiling &baseTiling;
    Isosurface &isosurface;
    
    vector<Triangle> allTriangles;
    vector<Triangle> processedTriangles;
    
    // ALGORITHM STEPS
    // step 1
    void findTrianglesOverlayingIsosurface();
    // step 2
    void findCutPoints();
    // step 3
    void warpPerimeterTriangles();
    
    
    // helpers
    vector<Triangle*> getPerimeterTrianglesForProcessing();
    Cutpoint findCutpointBetweenPolarPoints(Point, Point);
};

#endif /* Algorithm_hpp */

//
//  ProvablyGoodTriangleFactory.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#include "ProvablyGoodTriangleFactory.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Triangle.hpp"
#include <iostream>
#include <cmath>

using namespace std;

ProvablyGoodTriangleFactory::ProvablyGoodTriangleFactory() {
}

ProvablyGoodTriangleFactory::ProvablyGoodTriangleFactory(QuadtreeTiling *associatedTiling) {
    tiling = associatedTiling;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate(CellConfiguration configuration, Point center, float dimension, float theta) {
    if (configuration==ABAB) return triangulate_ABAB(center, dimension, theta);
    if (configuration==ABCB) return triangulate_ABCB(center, dimension, theta);
    if (configuration==BBCC) return triangulate_BBCC(center, dimension, theta);
    if (configuration==BBBB) return triangulate_BBBB(center, dimension, theta);
    if (configuration==ABBB) return triangulate_ABBB(center, dimension, theta);
    if (configuration==AABB) return triangulate_AABB(center, dimension, theta);
    if (configuration==AAAA) return triangulate_AAAA(center, dimension, theta);
    if (configuration==AAAB) return triangulate_AAAB(center, dimension, theta);
    if (configuration==BBBC) return triangulate_BBBC(center, dimension, theta);
    cout <<"should never reach here"<<endl;
    return vector<Triangle>();
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_ABAB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())/2, p3.getY());
    
    Point p11(p1.getX() + (p9.getX()-p1.getX())/2, p1.getY() - dimension/12);
    Point p12(p9.getX() + (p2.getX()-p9.getX())/2, p1.getY() - dimension/12);
    Point p13(p3.getX() + (p10.getX()-p3.getX())/2, p3.getY() + dimension/12);
    Point p14(p10.getX() + (p4.getX()-p10.getX())/2, p3.getY() + dimension/12);
    
    Point p15(p11.getX(), p13.getY() + (p11.getY()-p13.getY())/2);
    Point p16(p12.getX(), p14.getY() + (p12.getY()-p14.getY())/2);
    Point p17(p9.getX(), p10.getY() + (p9.getY()-p10.getY())/3);
    Point p18(p9.getX(), p10.getY() + (p9.getY()-p10.getY())*2/3);
        
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->check_addVertex_getIndex(p13);
    int p14Index = tiling->check_addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
        
    triangles.push_back(Triangle(p5Index, p11Index, p1Index));
    triangles.push_back(Triangle (p18Index, p9Index, p11Index));
    triangles.push_back(Triangle (p18Index, p12Index, p9Index));
    triangles.push_back(Triangle (p12Index, p2Index, p7Index));
    triangles.push_back(Triangle (p5Index, p11Index, p15Index));
    triangles.push_back(Triangle (p11Index, p18Index, p15Index));
    triangles.push_back(Triangle (p18Index, p12Index, p16Index));
    triangles.push_back(Triangle (p12Index, p16Index, p7Index));
    triangles.push_back(Triangle (p6Index, p5Index, p15Index));
    triangles.push_back(Triangle (p18Index, p15Index, p17Index));
    triangles.push_back(Triangle (p16Index, p17Index, p18Index));
    triangles.push_back(Triangle (p7Index, p8Index, p16Index));
    triangles.push_back(Triangle (p15Index, p6Index, p13Index));
    triangles.push_back(Triangle (p15Index, p17Index, p13Index));
    triangles.push_back(Triangle (p16Index, p17Index, p14Index));
    triangles.push_back(Triangle (p16Index, p8Index, p14Index));
    triangles.push_back(Triangle (p8Index, p14Index, p4Index));
    triangles.push_back(Triangle (p17Index, p10Index, p14Index));
    triangles.push_back(Triangle (p17Index, p10Index, p13Index));
    triangles.push_back(Triangle (p13Index, p3Index, p6Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_AAAB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p2.getX() - dimension/12, p4.getY() + 3*(p2.getY()-p4.getY())/4);
    Point p8(p2.getX() - dimension/12, p4.getY() + (p2.getY()-p4.getY())/4);
    
    Point p15(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/2);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())/2, p3.getY());
    
    Point p11(p1.getX() + (p9.getX()-p1.getX())/2, p1.getY() - dimension/12);
    Point p12(p9.getX() + (p2.getX()-p9.getX())/2, p1.getY() - dimension/12);
    Point p13(p3.getX() + (p10.getX()-p3.getX())/2, p3.getY() + dimension/12);
    Point p14(p10.getX() + (p4.getX()-p10.getX())/2, p3.getY() + dimension/12);
    
    
    Point p16(p11.getX(), center.getY());
    Point p17(center.getX(), center.getY() + dimension/4);
    Point p18(center.getX(), center.getY() - dimension/4);
//
    Point p19(p15.getX() - dimension/6, center.getY());
    Point p20(p16.getX() + (p15.getX() - p16.getX())*0.45, center.getY());
    Point p21(p20.getX() + (p19.getX() - p20.getX())/2, center.getY() + dimension*0.2);
    Point p22(p20.getX() + (p19.getX() - p20.getX())/2, center.getY() - dimension*0.2);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    p20.rotate(theta, center);
    p21.rotate(theta, center);
    p22.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->check_addVertex_getIndex(p13);
    int p14Index = tiling->check_addVertex_getIndex(p14);
    int p15Index = tiling->check_addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);
    int p20Index = tiling->addVertex_getIndex(p20);
    int p21Index = tiling->addVertex_getIndex(p21);
    int p22Index = tiling->addVertex_getIndex(p22);

    triangles.push_back(Triangle (p1Index, p5Index, p11Index));
    triangles.push_back(Triangle (p11Index, p5Index, p16Index));
    triangles.push_back(Triangle (p5Index, p16Index, p6Index));
    triangles.push_back(Triangle (p16Index, p6Index, p13Index));
    triangles.push_back(Triangle (p6Index, p13Index, p3Index));
    triangles.push_back(Triangle (p11Index, p17Index, p9Index));
    triangles.push_back(Triangle (p11Index, p17Index, p16Index));
    triangles.push_back(Triangle (p17Index, p16Index, p20Index));
    triangles.push_back(Triangle (p16Index, p20Index, p18Index));
    triangles.push_back(Triangle (p18Index, p16Index, p13Index));
    triangles.push_back(Triangle (p10Index, p13Index, p18Index));
    triangles.push_back(Triangle (p9Index, p17Index, p12Index));
    triangles.push_back(Triangle (p12Index, p2Index, p7Index));
    triangles.push_back(Triangle (p15Index, p7Index, p19Index));
    triangles.push_back(Triangle (p19Index, p15Index, p8Index));
    triangles.push_back(Triangle (p4Index, p8Index, p14Index));
    triangles.push_back(Triangle (p18Index, p14Index, p10Index));
    triangles.push_back(Triangle (p18Index, p14Index, p22Index));
    triangles.push_back(Triangle (p14Index, p22Index, p8Index));
    triangles.push_back(Triangle (p20Index, p22Index, p18Index));
    triangles.push_back(Triangle (p20Index, p19Index, p22Index));
    triangles.push_back(Triangle (p22Index, p19Index, p8Index));
    triangles.push_back(Triangle (p20Index, p19Index, p21Index));
    triangles.push_back(Triangle (p21Index, p19Index, p7Index));
    triangles.push_back(Triangle (p21Index, p7Index, p12Index));
    triangles.push_back(Triangle (p21Index, p12Index, p17Index));
    triangles.push_back(Triangle (p21Index, p20Index, p17Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_AAAA(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/2);
    Point p6(p2.getX(), p3.getY() + (p1.getY()-p3.getY())/2);
    Point p7(p1.getX() + dimension/12, p4.getY() + (p2.getY()-p4.getY())*3/4);
    Point p8(p1.getX() + dimension/12, p4.getY() + (p2.getY()-p4.getY())/4);
    Point p15(p2.getX() - dimension/12, p4.getY() + (p2.getY()-p4.getY())*3/4);
    Point p16(p2.getX() - dimension/12, p4.getY() + (p2.getY()-p4.getY())/4);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())/2, p3.getY());
    
    Point p11(p1.getX() + (p9.getX()-p1.getX())/2, p1.getY() - dimension/12);
    Point p12(p9.getX() + (p2.getX()-p9.getX())/2, p1.getY() - dimension/12);
    Point p13(p3.getX() + (p10.getX()-p3.getX())/2, p3.getY() + dimension/12);
    Point p14(p10.getX() + (p4.getX()-p10.getX())/2, p3.getY() + dimension/12);
    
    Point p17(center.getX(), center.getY());
    
    Point p18(p5.getX() + dimension/6, p5.getY());
    Point p19(p9.getX(), p9.getY() - dimension/6);
    Point p20(p6.getX() - dimension/6, p6.getY());
    Point p21(p10.getX(), p10.getY() + dimension/6);
    
    float offset = (dimension/2)*0.4;
    
    Point p22(center.getX() - offset, center.getY() - offset);
    Point p23(center.getX() - offset, center.getY() + offset);
    Point p24(center.getX() + offset, center.getY() + offset);
    Point p25(center.getX() + offset, center.getY() - offset);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    p20.rotate(theta, center);
    p21.rotate(theta, center);
    p22.rotate(theta, center);
    p23.rotate(theta, center);
    p24.rotate(theta, center);
    p25.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->check_addVertex_getIndex(p13);
    int p14Index = tiling->check_addVertex_getIndex(p14);
    int p15Index = tiling->check_addVertex_getIndex(p15);
    int p16Index = tiling->check_addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);
    int p20Index = tiling->addVertex_getIndex(p20);
    int p21Index = tiling->addVertex_getIndex(p21);
    int p22Index = tiling->addVertex_getIndex(p22);
    int p23Index = tiling->addVertex_getIndex(p23);
    int p24Index = tiling->addVertex_getIndex(p24);
    int p25Index = tiling->addVertex_getIndex(p25);
        
    triangles.push_back(Triangle(p1Index, p7Index, p11Index));
    triangles.push_back(Triangle (p12Index, p2Index, p15Index));
    triangles.push_back(Triangle (p3Index, p8Index, p13Index));
    triangles.push_back(Triangle (p4Index, p14Index, p16Index));
    triangles.push_back(Triangle (p5Index, p7Index, p18Index));
    triangles.push_back(Triangle (p7Index, p18Index, p23Index));
    triangles.push_back(Triangle (p7Index, p11Index, p23Index));
    triangles.push_back(Triangle (p11Index, p23Index, p19Index));
    triangles.push_back(Triangle (p11Index, p19Index, p9Index));
    triangles.push_back(Triangle (p9Index, p19Index, p12Index));
    triangles.push_back(Triangle (p19Index, p12Index, p24Index));
    triangles.push_back(Triangle (p12Index, p24Index, p15Index));
    triangles.push_back(Triangle (p15Index, p24Index, p20Index));
    triangles.push_back(Triangle (p15Index, p20Index, p6Index));
    triangles.push_back(Triangle (p6Index, p20Index, p16Index));
    triangles.push_back(Triangle (p16Index, p20Index, p25Index));
    triangles.push_back(Triangle (p25Index, p16Index, p14Index));
    triangles.push_back(Triangle (p21Index, p25Index, p14Index));
    triangles.push_back(Triangle (p21Index, p14Index, p10Index));
    triangles.push_back(Triangle (p13Index, p10Index, p21Index));
    triangles.push_back(Triangle (p21Index, p13Index, p22Index));
    triangles.push_back(Triangle (p22Index, p13Index, p8Index));
    triangles.push_back(Triangle (p8Index, p18Index, p22Index));
    triangles.push_back(Triangle (p8Index, p18Index, p5Index));
    triangles.push_back(Triangle (p18Index, p23Index, p17Index));
    triangles.push_back(Triangle (p17Index, p23Index, p19Index));
    triangles.push_back(Triangle (p24Index, p19Index, p17Index));
    triangles.push_back(Triangle (p24Index, p17Index, p20Index));
    triangles.push_back(Triangle (p20Index, p17Index, p25Index));
    triangles.push_back(Triangle (p25Index, p21Index, p17Index));
    triangles.push_back(Triangle (p22Index, p17Index, p21Index));
    triangles.push_back(Triangle (p22Index, p17Index, p18Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_BBBB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/3, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())*2/3, p1.getY());
    
    Point p11(p1.getX() + (p2.getX()-p1.getX())/3, p3.getY());
    Point p12(p3.getX() + (p4.getX()-p3.getX())*2/3, p3.getY());
    
    Point p17(p5.getX() + (p7.getX()-p5.getX())/4, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p18(p5.getX() + (p7.getX()-p5.getX())*3/4, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p19(p5.getX() + (p7.getX()-p5.getX())/2, p6.getY());
    Point p20(p5.getX() + (p7.getX()-p5.getX())/2, p5.getY());

    Point p13(p5.getX() + (p20.getX()-p5.getX())*0.35, p17.getY() + (p9.getY()-p17.getY())*0.5);
    Point p14(p20.getX() + (p7.getX()-p20.getX())*0.65, p17.getY() + (p9.getY()-p17.getY())*0.5);
    Point p15(p5.getX() + (p20.getX()-p5.getX())*0.35, p17.getY() - (p9.getY()-p17.getY())*0.5);
    Point p16(p20.getX() + (p7.getX()-p20.getX())*0.65, p17.getY() - (p9.getY()-p17.getY())*0.5);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    p20.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->addVertex_getIndex(p13);
    int p14Index = tiling->addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);
    int p20Index = tiling->addVertex_getIndex(p20);
    
    
    triangles.push_back(Triangle (p1Index, p5Index, p13Index));
    triangles.push_back(Triangle (p1Index, p9Index, p13Index));
    triangles.push_back(Triangle (p13Index, p9Index, p20Index));
    triangles.push_back(Triangle (p20Index, p9Index, p10Index));
    triangles.push_back(Triangle (p20Index, p10Index, p14Index));
    triangles.push_back(Triangle (p10Index, p14Index, p2Index));
    triangles.push_back(Triangle (p2Index, p14Index, p7Index));
    triangles.push_back(Triangle (p5Index, p13Index, p17Index));
    triangles.push_back(Triangle (p13Index, p17Index, p20Index));
    triangles.push_back(Triangle (p19Index, p20Index, p17Index));
    triangles.push_back(Triangle (p20Index, p19Index, p18Index));
    triangles.push_back(Triangle (p18Index, p8Index, p7Index));
    triangles.push_back(Triangle (p16Index, p18Index, p8Index));
    triangles.push_back(Triangle (p5Index, p17Index, p6Index));
    triangles.push_back(Triangle (p16Index, p19Index, p18Index));
    triangles.push_back(Triangle (p17Index, p15Index, p19Index));
    triangles.push_back(Triangle (p6Index, p17Index, p15Index));
    triangles.push_back(Triangle (p6Index, p3Index, p15Index));
    triangles.push_back(Triangle (p3Index, p11Index, p15Index));
    triangles.push_back(Triangle (p11Index, p19Index, p12Index));
    triangles.push_back(Triangle (p12Index, p19Index, p16Index));
    triangles.push_back(Triangle (p16Index, p12Index, p4Index));
    triangles.push_back(Triangle (p19Index, p11Index, p15Index));
    triangles.push_back(Triangle (p20Index, p14Index, p18Index));
    triangles.push_back(Triangle (p14Index, p18Index, p7Index));
    triangles.push_back(Triangle (p16Index, p8Index, p4Index));
    
    
        
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_BBBC(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX() - dimension/6, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/3, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())*2/3, p1.getY());
    
    Point p11(p1.getX() + (p2.getX()-p1.getX())/3, p3.getY());
    Point p12(p3.getX() + (p4.getX()-p3.getX())*2/3, p3.getY());
    
    Point p13(p5.getX() + (p7.getX() - p5.getX()) / 3, center.getY() + dimension/8);
    Point p14(p5.getX() + (p7.getX() - p5.getX()) / 3, center.getY() - dimension/8);
    
    Point p15(p5.getX() + (p7.getX() - p5.getX()) / 2, center.getY());
    Point p16(center.getX(), center.getY() + dimension/4);
    Point p17(center.getX(), center.getY() - dimension/4);
    
    Point p18(p5.getX() + (p7.getX()-p5.getX())*3/4, center.getY());
    Point p19(center.getX() + dimension/4, center.getY() + dimension*0.325);
    Point p6(center.getX() + dimension/4, center.getY() - dimension*0.325);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->addVertex_getIndex(p13);
    int p14Index = tiling->addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);

    triangles.push_back(Triangle (p1Index, p5Index, p13Index));
    triangles.push_back(Triangle (p5Index, p13Index, p14Index));
    triangles.push_back(Triangle (p5Index, p14Index, p3Index));
    triangles.push_back(Triangle (p3Index, p14Index, p11Index));
    triangles.push_back(Triangle (p1Index, p9Index, p13Index));
    triangles.push_back(Triangle (p9Index, p13Index, p16Index));
    triangles.push_back(Triangle (p16Index, p9Index, p10Index));
    triangles.push_back(Triangle (p19Index, p16Index, p10Index));
    triangles.push_back(Triangle (p19Index, p10Index, p2Index));
    triangles.push_back(Triangle (p19Index, p2Index, p7Index));
    triangles.push_back(Triangle (p7Index, p19Index, p18Index));
    triangles.push_back(Triangle (p18Index, p8Index, p7Index));
    triangles.push_back(Triangle (p6Index, p18Index, p8Index));
    triangles.push_back(Triangle (p4Index, p8Index, p6Index));
    triangles.push_back(Triangle (p4Index, p6Index, p12Index));
    triangles.push_back(Triangle (p6Index, p17Index, p12Index));
    triangles.push_back(Triangle (p11Index, p17Index, p12Index));
    triangles.push_back(Triangle (p14Index, p17Index, p11Index));
    triangles.push_back(Triangle (p13Index, p14Index, p15Index));
    triangles.push_back(Triangle (p13Index, p15Index, p16Index));
    triangles.push_back(Triangle (p15Index, p16Index, p18Index));
    triangles.push_back(Triangle (p16Index, p18Index, p19Index));
    triangles.push_back(Triangle (p6Index, p17Index, p18Index));
    triangles.push_back(Triangle (p15Index, p17Index, p18Index));
    triangles.push_back(Triangle (p14Index, p15Index, p17Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_BBCC(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX() + (p2.getX()-p1.getX())/3, p1.getY());
    Point p6(p1.getX() + (p2.getX()-p1.getX())*2/3, p1.getY());
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    Point p9(p1.getX() - dimension/6, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p10(p3.getX() + (p4.getX()-p3.getX())/2, p3.getY()-dimension/6);
    
    Point p11(p9.getX() + (p7.getX()-p9.getX())/3,  p7.getY());
    Point p12(p9.getX() + (p7.getX()-p9.getX())/3, p10.getY() + (p5.getY()-p10.getY())/3);
    Point p13(p9.getX() + (p7.getX()-p9.getX())*2/3, p10.getY() + (p5.getY()-p10.getY())/3);
    
    Point p14(p2.getX() - (p2.getX()-p1.getX())*0.45, p2.getY() - (p2.getY()-p4.getY())*0.45);
    Point p15(p14.getX(), p1.getY() + (p14.getY()-p1.getY())/2);
    Point p16(p14.getX() + (p2.getX()-p14.getX())/2, p14.getY());
    Point p17(p2.getX() - (p2.getX()-p1.getX())*0.25, p2.getY() - (p2.getY()-p4.getY())*0.25);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->addVertex_getIndex(p11);
    int p12Index = tiling->addVertex_getIndex(p12);
    int p13Index = tiling->addVertex_getIndex(p13);
    int p14Index = tiling->addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);

    triangles.push_back(Triangle (p1Index, p5Index, p11Index));
    triangles.push_back(Triangle (p5Index, p6Index, p15Index));
    triangles.push_back(Triangle (p6Index, p2Index, p17Index));
    triangles.push_back(Triangle (p9Index, p11Index, p1Index));
    triangles.push_back(Triangle (p15Index, p11Index, p14Index));
    triangles.push_back(Triangle (p15Index, p17Index, p14Index));
    triangles.push_back(Triangle (p17Index, p14Index, p16Index));
    triangles.push_back(Triangle (p17Index, p16Index, p7Index));
    triangles.push_back(Triangle (p9Index, p11Index, p12Index));
    triangles.push_back(Triangle (p11Index, p12Index, p14Index));
    triangles.push_back(Triangle (p14Index, p16Index, p13Index));
    triangles.push_back(Triangle (p13Index, p8Index, p16Index));
    triangles.push_back(Triangle (p9Index, p3Index, p12Index));
    triangles.push_back(Triangle (p3Index, p12Index, p10Index));
    triangles.push_back(Triangle (p12Index, p13Index, p10Index));
    triangles.push_back(Triangle (p10Index, p13Index, p4Index));
    triangles.push_back(Triangle (p4Index, p13Index, p8Index));
    triangles.push_back(Triangle (p5Index, p11Index, p15Index));
    triangles.push_back(Triangle (p6Index, p15Index, p17Index));
    triangles.push_back(Triangle (p2Index, p17Index, p7Index));
    triangles.push_back(Triangle (p7Index, p16Index, p8Index));
    triangles.push_back(Triangle (p12Index, p13Index, p14Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_ABCB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());
    Point p10(p3.getX() + (p4.getX()-p3.getX())/2, p3.getY() - dimension/6);
    
    Point p11(p1.getX() + (p9.getX()-p1.getX())/2, p1.getY() - dimension/12);
    Point p12(p9.getX() + (p2.getX()-p9.getX())/2, p1.getY() - dimension/12);
    Point p13(p11.getX() + (p9.getX()-p11.getX())/2, p4.getY() + (p8.getY() - p4.getY())/2);
    Point p14(p9.getX() + (p12.getX()-p9.getX())/2, p4.getY() + (p8.getY() - p4.getY())/2);
    
    Point p15(p11.getX(), p13.getY() + (p11.getY()-p13.getY())/2);
    Point p16(p12.getX(), p14.getY() + (p12.getY()-p14.getY())/2);
    Point p17(p9.getX(), p3.getY() + (p9.getY()-p10.getY())*2/3);
    Point p18(p13.getX() + (p14.getX()-p13.getX())/2, p13.getY() + (p17.getY()-p13.getY())/2);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->addVertex_getIndex(p13);
    int p14Index = tiling->addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
        
    triangles.push_back(Triangle(p1Index, p5Index, p11Index));
    triangles.push_back(Triangle (p11Index, p9Index, p17Index));
    triangles.push_back(Triangle (p9Index, p12Index, p17Index));
    triangles.push_back(Triangle (p12Index, p2Index, p7Index));
    triangles.push_back(Triangle (p5Index, p11Index, p15Index));
    triangles.push_back(Triangle (p11Index, p17Index, p15Index));
    triangles.push_back(Triangle (p17Index, p12Index, p16Index));
    triangles.push_back(Triangle (p12Index, p16Index, p7Index));
    triangles.push_back(Triangle (p6Index, p5Index, p15Index));
    triangles.push_back(Triangle (p18Index, p15Index, p17Index));
    triangles.push_back(Triangle (p16Index, p17Index, p18Index));
    triangles.push_back(Triangle (p7Index, p8Index, p16Index));
    triangles.push_back(Triangle (p15Index, p6Index, p13Index));
    triangles.push_back(Triangle (p15Index, p18Index, p13Index));
    triangles.push_back(Triangle (p16Index, p18Index, p14Index));
    triangles.push_back(Triangle (p16Index, p8Index, p14Index));
    triangles.push_back(Triangle (p8Index, p14Index, p4Index));
    triangles.push_back(Triangle (p18Index, p13Index, p14Index));
    triangles.push_back(Triangle (p13Index, p10Index, p14Index));
    triangles.push_back(Triangle (p13Index, p3Index, p6Index));
    triangles.push_back(Triangle (p13Index, p10Index, p3Index));
    triangles.push_back(Triangle (p14Index, p4Index, p10Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_ABBB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p2.getX(), p4.getY() + 2*(p2.getY()-p4.getY())/3);
    Point p8(p2.getX(), p4.getY() + (p2.getY()-p4.getY())/3);
    
    
    Point p9(p1.getX() + (p2.getX()-p1.getX())/4, p1.getY() - dimension/12);
    Point p10(p1.getX() + (p2.getX()-p1.getX())*3/4, p1.getY() - dimension/12);
    
    
    Point p11(p1.getX() + (p2.getX()-p1.getX())/3, p3.getY());
    Point p12(p3.getX() + (p4.getX()-p3.getX())*2/3, p3.getY());
    Point p13(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());

    
    Point p17(p5.getX() + (p7.getX()-p5.getX())/4, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p18(p5.getX() + (p7.getX()-p5.getX())*3/4, p3.getY() + (p1.getY()-p3.getY())/2);
    Point p19(p5.getX() + (p7.getX()-p5.getX())/2, p6.getY());
    Point p20(p5.getX() + (p7.getX()-p5.getX())/2, p5.getY());

    Point p15(p5.getX() + (p20.getX()-p5.getX())*0.35, p17.getY() - (p1.getY()-p17.getY())*0.5);
    Point p16(p20.getX() + (p7.getX()-p20.getX())*0.65, p17.getY() - (p1.getY()-p17.getY())*0.5);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    p20.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->check_addVertex_getIndex(p13);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);
    int p20Index = tiling->addVertex_getIndex(p20);
    

    triangles.push_back(Triangle (p1Index, p9Index, p5Index));
    triangles.push_back(Triangle (p13Index, p9Index, p20Index));
    triangles.push_back(Triangle (p20Index, p13Index, p10Index));
    triangles.push_back(Triangle (p2Index, p10Index, p7Index));
    triangles.push_back(Triangle (p5Index, p9Index, p17Index));
    triangles.push_back(Triangle (p20Index, p9Index, p17Index));
    triangles.push_back(Triangle (p20Index, p18Index, p10Index));
    triangles.push_back(Triangle (p18Index, p7Index, p10Index));
    triangles.push_back(Triangle (p19Index, p20Index, p17Index));
    triangles.push_back(Triangle (p20Index, p19Index, p18Index));
    triangles.push_back(Triangle (p18Index, p8Index, p7Index));
    triangles.push_back(Triangle (p16Index, p18Index, p8Index));
    triangles.push_back(Triangle (p5Index, p17Index, p6Index));
    triangles.push_back(Triangle (p16Index, p19Index, p18Index));
    triangles.push_back(Triangle (p17Index, p15Index, p19Index));
    triangles.push_back(Triangle (p6Index, p17Index, p15Index));
    triangles.push_back(Triangle (p6Index, p3Index, p15Index));
    triangles.push_back(Triangle (p3Index, p11Index, p15Index));
    triangles.push_back(Triangle (p11Index, p19Index, p12Index));
    triangles.push_back(Triangle (p12Index, p19Index, p16Index));
    triangles.push_back(Triangle (p16Index, p12Index, p4Index));
    triangles.push_back(Triangle (p19Index, p11Index, p15Index));
    triangles.push_back(Triangle (p16Index, p8Index, p4Index));
    
    return triangles;
}

vector<Triangle> ProvablyGoodTriangleFactory::triangulate_AABB(Point center, float dimension, float theta) {
    vector<Triangle> triangles;
    
    Point p1(center.getX() - dimension / 2, center.getY() + dimension / 2);
    Point p2(center.getX() + dimension / 2, center.getY() + dimension / 2);
    Point p3(center.getX() - dimension / 2, center.getY() - dimension / 2);
    Point p4(center.getX() + dimension / 2, center.getY() - dimension / 2);
    
    Point p5(p1.getX(), p3.getY() + 2*(p1.getY()-p3.getY())/3);
    Point p6(p1.getX(), p3.getY() + (p1.getY()-p3.getY())/3);
    Point p7(p3.getX()+ (p4.getX()-p3.getX())/3, p3.getY());
    Point p8(p3.getX()+ (p4.getX()-p3.getX())*2/3, p3.getY());
    
    Point p9(p2.getX() - dimension/12, p2.getY() - (p2.getY()-p4.getY())/4);
    Point p10(p2.getX() - dimension/12, p2.getY() - (p2.getY()-p4.getY())*3/4);

    Point p11(p1.getX() + (p2.getX()-p1.getX())/4, p1.getY() - dimension/12);
    Point p12(p1.getX() + (p2.getX()-p1.getX())*3/4, p1.getY() - dimension/12);
    
    Point p13(p1.getX() + (p2.getX()-p1.getX())/2, p1.getY());
    Point p14(p2.getX(), p2.getY()-(p2.getY()-p4.getY())/2);
    
    Point p15(p11.getX(), p11.getY() - (p11.getY()-p7.getY())/3);
    Point p16(p11.getX(), p2.getY() - (p2.getY()-p4.getY())*3/4);
    Point p17(p11.getX() + (p10.getX() - p11.getX())/2, p2.getY() - (p2.getY()-p4.getY())*3/4);
    
    Point p18(center.getX(), center.getY());
    Point p19(p18.getX(), p13.getY() - dimension/6);
    Point p20(p14.getX() - dimension/6, p18.getY());
    Point p21(p18.getX() + (p14.getX()-p18.getX())*0.4, p18.getY() + (p13.getY()-p18.getY())*0.4);
    
    p1.rotate(theta, center);
    p2.rotate(theta, center);
    p3.rotate(theta, center);
    p4.rotate(theta, center);
    p5.rotate(theta, center);
    p6.rotate(theta, center);
    p7.rotate(theta, center);
    p8.rotate(theta, center);
    p9.rotate(theta, center);
    p10.rotate(theta, center);
    p11.rotate(theta, center);
    p12.rotate(theta, center);
    p13.rotate(theta, center);
    p14.rotate(theta, center);
    p15.rotate(theta, center);
    p16.rotate(theta, center);
    p17.rotate(theta, center);
    p18.rotate(theta, center);
    p19.rotate(theta, center);
    p20.rotate(theta, center);
    p21.rotate(theta, center);
    
    int p1Index = tiling->check_addVertex_getIndex(p1);
    int p2Index = tiling->check_addVertex_getIndex(p2);
    int p3Index = tiling->check_addVertex_getIndex(p3);
    int p4Index = tiling->check_addVertex_getIndex(p4);
    int p5Index = tiling->check_addVertex_getIndex(p5);
    int p6Index = tiling->check_addVertex_getIndex(p6);
    int p7Index = tiling->check_addVertex_getIndex(p7);
    int p8Index = tiling->check_addVertex_getIndex(p8);
    int p9Index = tiling->check_addVertex_getIndex(p9);
    int p10Index = tiling->check_addVertex_getIndex(p10);
    int p11Index = tiling->check_addVertex_getIndex(p11);
    int p12Index = tiling->check_addVertex_getIndex(p12);
    int p13Index = tiling->check_addVertex_getIndex(p13);
    int p14Index = tiling->check_addVertex_getIndex(p14);
    int p15Index = tiling->addVertex_getIndex(p15);
    int p16Index = tiling->addVertex_getIndex(p16);
    int p17Index = tiling->addVertex_getIndex(p17);
    int p18Index = tiling->addVertex_getIndex(p18);
    int p19Index = tiling->addVertex_getIndex(p19);
    int p20Index = tiling->addVertex_getIndex(p20);
    int p21Index = tiling->addVertex_getIndex(p21);
    
    triangles.push_back(Triangle (p1Index, p5Index, p11Index));
    triangles.push_back(Triangle (p11Index, p5Index, p15Index));
    triangles.push_back(Triangle (p5Index, p15Index, p6Index));
    triangles.push_back(Triangle (p6Index, p15Index, p16Index));
    triangles.push_back(Triangle (p6Index, p16Index, p3Index));
    triangles.push_back(Triangle (p3Index, p16Index, p7Index));
    triangles.push_back(Triangle (p7Index, p17Index, p16Index));
    triangles.push_back(Triangle (p8Index, p17Index, p7Index));
    triangles.push_back(Triangle (p8Index, p10Index, p17Index));
    triangles.push_back(Triangle (p8Index, p10Index, p4Index));
    triangles.push_back(Triangle (p11Index, p13Index, p19Index));
    triangles.push_back(Triangle (p15Index, p19Index, p18Index));
    triangles.push_back(Triangle (p15Index, p16Index, p18Index));
    triangles.push_back(Triangle (p16Index, p17Index, p18Index));
    triangles.push_back(Triangle (p20Index, p17Index, p18Index));
    triangles.push_back(Triangle (p20Index, p17Index, p10Index));
    triangles.push_back(Triangle (p10Index, p14Index, p20Index));
    triangles.push_back(Triangle (p13Index, p12Index, p19Index));
    triangles.push_back(Triangle (p19Index, p21Index, p18Index));
    triangles.push_back(Triangle (p18Index, p21Index, p20Index));
    triangles.push_back(Triangle (p21Index, p20Index, p9Index));
    triangles.push_back(Triangle (p9Index, p20Index, p14Index));
    triangles.push_back(Triangle (p12Index, p21Index, p9Index));
    triangles.push_back(Triangle (p11Index, p19Index, p15Index));
    triangles.push_back(Triangle (p21Index, p19Index, p12Index));
    triangles.push_back(Triangle (p12Index, p2Index, p9Index));
    
    return triangles;
}


//void ProvablyGoodTriangleFactory::render(vector<Triangle> triangles) {
//    for (int i = 0; i < triangles.size(); i++) triangles[i].render();
//}

//bool ProvablyGoodTriangleFactory::verifyAngles(vector<Triangle> triangles) {
//    vector<float> angles;
//    for (int i = 0; i < triangles.size(); i++) {
//        vector<float> curTriangleAngles = triangles[i].computeAngles();
//        angles.insert( angles.end(), curTriangleAngles.begin(), curTriangleAngles.end() );
//    }
//
//    bool isCorrect = true;
//    for (int i = 0; i < angles.size(); i++) {
//        if (angles[i] > 89.9) {
//            cout<<"ERROR " <<angles[i]<<" "<<i<<endl;
//            isCorrect = false;
//            break;
//        }
//    }
//    return isCorrect;
//}


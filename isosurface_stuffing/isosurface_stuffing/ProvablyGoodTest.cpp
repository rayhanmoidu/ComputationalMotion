//
//  ProvablyGoodTest.cpp
//  isosurface_stuffing
//
//  Created by Rayhan Moidu on 2022-11-23.
//

#include "ProvablyGoodTest.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Triangle.hpp"
#include <iostream>

using namespace std;

inline bool isEqual(double x, double y)
{
  const double epsilon = 1e-5;
  return std::abs(x - y) <= epsilon * std::abs(x);
}


ProvablyGoodTest::ProvablyGoodTest(CellConfiguration configuration, Point center, float dimension) {
    if (configuration==ABAB) triangulate_ABAB(center, dimension);
    if (configuration==ABCB) triangulate_ABCB(center, dimension);
    if (configuration==BBCC) triangulate_BBCC(center, dimension);
    if (configuration==BBBB) triangulate_BBBB(center, dimension);
    if (configuration==ABBB) triangulate_ABBB(center, dimension);
    if (configuration==AABB) triangulate_AABB(center, dimension);
}

void ProvablyGoodTest::triangulate_ABAB(Point center, float dimension) {
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
        
    triangles.push_back(Triangle(p1, p5, p11));
    triangles.push_back(Triangle (p11, p9, p18));
    triangles.push_back(Triangle (p9, p12, p18));
    triangles.push_back(Triangle (p12, p2, p7));
    triangles.push_back(Triangle (p5, p11, p15));
    triangles.push_back(Triangle (p11, p18, p15));
    triangles.push_back(Triangle (p18, p12, p16));
    triangles.push_back(Triangle (p12, p16, p7));
    triangles.push_back(Triangle (p6, p5, p15));
    triangles.push_back(Triangle (p18, p15, p17));
    triangles.push_back(Triangle (p16, p17, p18));
    triangles.push_back(Triangle (p7, p8, p16));
    triangles.push_back(Triangle (p15, p6, p13));
    triangles.push_back(Triangle (p15, p17, p13));
    triangles.push_back(Triangle (p16, p17, p14));
    triangles.push_back(Triangle (p16, p8, p14));
    triangles.push_back(Triangle (p8, p14, p4));
    triangles.push_back(Triangle (p17, p10, p14));
    triangles.push_back(Triangle (p17, p10, p13));
    triangles.push_back(Triangle (p13, p3, p6));
        
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}

void ProvablyGoodTest::triangulate_BBBB(Point center, float dimension) {
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

    triangles.push_back(Triangle(p1, p5, p13));
    triangles.push_back(Triangle (p1, p9, p13));
    triangles.push_back(Triangle (p13, p9, p20));
    triangles.push_back(Triangle (p20, p9, p10));
    triangles.push_back(Triangle (p20, p10, p14));
    triangles.push_back(Triangle (p10, p14, p2));
    triangles.push_back(Triangle (p2, p14, p7));
    triangles.push_back(Triangle (p5, p13, p17));
    triangles.push_back(Triangle (p13, p17, p20));
    triangles.push_back(Triangle (p19, p20, p17));
    triangles.push_back(Triangle (p20, p19, p18));
    triangles.push_back(Triangle (p18, p8, p7));
    triangles.push_back(Triangle (p16, p18, p8));
    triangles.push_back(Triangle (p5, p17, p6));
    triangles.push_back(Triangle (p16, p19, p18));
    triangles.push_back(Triangle (p17, p15, p19));
    triangles.push_back(Triangle (p6, p17, p15));
    triangles.push_back(Triangle (p6, p3, p15));
    triangles.push_back(Triangle (p3, p11, p15));
    triangles.push_back(Triangle (p11, p19, p12));
    triangles.push_back(Triangle (p12, p19, p16));
    triangles.push_back(Triangle (p16, p12, p4));
    triangles.push_back(Triangle (p19, p11, p15));
    triangles.push_back(Triangle (p20, p14, p18));
    triangles.push_back(Triangle (p14, p18, p7));
    triangles.push_back(Triangle (p16, p8, p4));
        
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}

void ProvablyGoodTest::triangulate_BBCC(Point center, float dimension) {
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
        
    triangles.push_back(Triangle(p1, p5, p11));
    triangles.push_back(Triangle (p5, p6, p15));
    triangles.push_back(Triangle (p6, p2, p17));
    triangles.push_back(Triangle (p9, p11, p1));
    triangles.push_back(Triangle (p15, p11, p14));
    triangles.push_back(Triangle (p15, p17, p14));
    triangles.push_back(Triangle (p17, p14, p16));
    triangles.push_back(Triangle (p17, p16, p7));
    triangles.push_back(Triangle (p9, p11, p12));
    triangles.push_back(Triangle (p11, p12, p14));
    triangles.push_back(Triangle (p14, p16, p13));
    triangles.push_back(Triangle (p13, p8, p16));
    triangles.push_back(Triangle (p9, p3, p12));
    triangles.push_back(Triangle (p3, p12, p10));
    triangles.push_back(Triangle (p12, p13, p10));
    triangles.push_back(Triangle (p10, p13, p4));
    triangles.push_back(Triangle (p4, p13, p8));
    
    triangles.push_back(Triangle (p5, p11, p15));
    triangles.push_back(Triangle (p6, p15, p17));
    triangles.push_back(Triangle (p2, p17, p7));
    triangles.push_back(Triangle (p7, p16, p8));
    triangles.push_back(Triangle (p12, p13, p14));
        
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}

void ProvablyGoodTest::triangulate_ABCB(Point center, float dimension) {
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
        
    triangles.push_back(Triangle(p1, p5, p11));
    triangles.push_back(Triangle (p11, p9, p17));
    triangles.push_back(Triangle (p9, p12, p17));
    triangles.push_back(Triangle (p12, p2, p7));
    triangles.push_back(Triangle (p5, p11, p15));
    triangles.push_back(Triangle (p11, p17, p15));
    triangles.push_back(Triangle (p17, p12, p16));
    triangles.push_back(Triangle (p12, p16, p7));
    triangles.push_back(Triangle (p6, p5, p15));
    triangles.push_back(Triangle (p18, p15, p17));
    triangles.push_back(Triangle (p16, p17, p18));
    triangles.push_back(Triangle (p7, p8, p16));
    triangles.push_back(Triangle (p15, p6, p13));
    triangles.push_back(Triangle (p15, p18, p13));
    triangles.push_back(Triangle (p16, p18, p14));
    triangles.push_back(Triangle (p16, p8, p14));
    triangles.push_back(Triangle (p8, p14, p4));
    triangles.push_back(Triangle (p18, p13, p14));
    triangles.push_back(Triangle (p13, p10, p14));
    triangles.push_back(Triangle (p13, p3, p6));
    triangles.push_back(Triangle (p13, p10, p3));
    triangles.push_back(Triangle (p14, p4, p10));
        
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}

void ProvablyGoodTest::triangulate_ABBB(Point center, float dimension) {
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

    triangles.push_back(Triangle (p1, p9, p5));
    triangles.push_back(Triangle (p13, p9, p20));
    triangles.push_back(Triangle (p20, p13, p10));
    triangles.push_back(Triangle (p2, p10, p7));
    triangles.push_back(Triangle (p5, p9, p17));
    triangles.push_back(Triangle (p20, p9, p17));
    triangles.push_back(Triangle (p20, p18, p10));
    triangles.push_back(Triangle (p18, p7, p10));
    triangles.push_back(Triangle (p19, p20, p17));
    triangles.push_back(Triangle (p20, p19, p18));
    triangles.push_back(Triangle (p18, p8, p7));
    triangles.push_back(Triangle (p16, p18, p8));
    triangles.push_back(Triangle (p5, p17, p6));
    triangles.push_back(Triangle (p16, p19, p18));
    triangles.push_back(Triangle (p17, p15, p19));
    triangles.push_back(Triangle (p6, p17, p15));
    triangles.push_back(Triangle (p6, p3, p15));
    triangles.push_back(Triangle (p3, p11, p15));
    triangles.push_back(Triangle (p11, p19, p12));
    triangles.push_back(Triangle (p12, p19, p16));
    triangles.push_back(Triangle (p16, p12, p4));
    triangles.push_back(Triangle (p19, p11, p15));
    triangles.push_back(Triangle (p16, p8, p4));
        
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}

void ProvablyGoodTest::triangulate_AABB(Point center, float dimension) {
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
    
//
    triangles.push_back(Triangle(p1, p5, p11));
    triangles.push_back(Triangle (p11, p5, p15));
    triangles.push_back(Triangle (p5, p15, p6));
    triangles.push_back(Triangle (p6, p15, p16));
    triangles.push_back(Triangle (p6, p16, p3));
    triangles.push_back(Triangle (p3, p16, p7));
    triangles.push_back(Triangle (p7, p17, p16));
    triangles.push_back(Triangle (p8, p17, p7));
    triangles.push_back(Triangle (p8, p10, p17));
    triangles.push_back(Triangle (p8, p10, p4));
    
    triangles.push_back(Triangle (p11, p13, p19));
    triangles.push_back(Triangle (p15, p19, p18));
    triangles.push_back(Triangle (p15, p16, p18));
    triangles.push_back(Triangle (p16, p17, p18));
    triangles.push_back(Triangle (p20, p17, p18));
    triangles.push_back(Triangle (p20, p17, p10));
    triangles.push_back(Triangle (p10, p14, p20));
    triangles.push_back(Triangle (p13, p12, p19));
    triangles.push_back(Triangle (p19, p21, p18));
    triangles.push_back(Triangle (p18, p21, p20));
    triangles.push_back(Triangle (p21, p20, p9));
    triangles.push_back(Triangle (p9, p20, p14));
    triangles.push_back(Triangle (p12, p21, p9));
    triangles.push_back(Triangle(p11, p19, p15));
    triangles.push_back(Triangle(p21, p19, p12));
    triangles.push_back(Triangle (p12, p2, p9));
//
    bool isVerified = verifyAngles();
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}


void ProvablyGoodTest::render() {
    for (int i = 0; i < triangles.size(); i++) triangles[i].render();
}

bool ProvablyGoodTest::verifyAngles() {
    vector<float> angles;
    for (int i = 0; i < triangles.size(); i++) {
        vector<float> curTriangleAngles = triangles[i].computeAngles();
        angles.insert( angles.end(), curTriangleAngles.begin(), curTriangleAngles.end() );
    }
    
    bool isCorrect = true;
    for (int i = 0; i < angles.size(); i++) {
        if (angles[i] > 89.9) {
            cout<<"ERROR " <<angles[i]<<" "<<i<<endl;
            isCorrect = false;
            break;
        }
    }
    return isCorrect;
}

#include <cmath>  /* for std::abs(double) */


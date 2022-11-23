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

ProvablyGoodTest::ProvablyGoodTest(CellConfiguration configuration, Point center, float dimension) {
    if (configuration==ABAB) triangulate_ABAB(center, dimension);
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
    
    Triangle t1(p1, p5, p11);
    Triangle t2(p11, p9, p18);
    Triangle t3(p9, p12, p18);
    Triangle t4(p12, p2, p7);
    Triangle t5(p5, p11, p15);
    Triangle t6(p11, p18, p15);
    Triangle t7(p18, p12, p16);
    Triangle t8(p12, p16, p7);
    Triangle t9(p6, p5, p15);
    Triangle t10(p18, p15, p17);
    Triangle t11(p16, p17, p18);
    Triangle t12(p7, p8, p16);
    Triangle t13(p15, p6, p13);
    Triangle t14(p15, p17, p13);
    Triangle t15(p16, p17, p14);
    Triangle t16(p16, p8, p14);
    Triangle t17(p8, p14, p4);
    Triangle t18(p17, p10, p14);
    Triangle t19(p17, p10, p13);
    Triangle t20(p13, p3, p6);

    t1.render();
    t2.render();
    t3.render();
    t4.render();
    t5.render();
    t6.render();
    t7.render();
    t8.render();
    t9.render();
    t10.render();
    t11.render();
    t12.render();
    t13.render();
    t14.render();
    t15.render();
    t16.render();
    t17.render();
    t18.render();
    t19.render();
    t20.render();
    
    vector<Triangle> triangles;
    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
    triangles.push_back(t5);
    triangles.push_back(t6);
    triangles.push_back(t7);
    triangles.push_back(t8);
    triangles.push_back(t9);
    triangles.push_back(t10);
    triangles.push_back(t11);
    triangles.push_back(t12);
    triangles.push_back(t13);
    triangles.push_back(t14);
    triangles.push_back(t15);
    triangles.push_back(t16);
    triangles.push_back(t17);
    triangles.push_back(t18);
    triangles.push_back(t19);
    triangles.push_back(t20);
    
    bool isVerified = verifyAngles(triangles);
    if (!isVerified) cout <<"Oh no... not all acute"<<endl;
    else cout<<"All acute!"<<endl;
}
bool ProvablyGoodTest::verifyAngles(vector<Triangle> triangles) {
    vector<float> angles;
    for (int i = 0; i < triangles.size(); i++) {
        vector<float> curTriangleAngles = triangles[i].computeAngles();
        angles.insert( angles.end(), curTriangleAngles.begin(), curTriangleAngles.end() );
    }
    
    bool isCorrect = true;
    for (int i = 0; i < angles.size(); i++) {
        if (angles[i] >=90) {
            isCorrect = false;
            break;
        }
    }
    return isCorrect;
}



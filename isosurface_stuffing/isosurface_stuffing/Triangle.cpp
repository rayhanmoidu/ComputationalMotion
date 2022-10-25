#include "Triangle.hpp"
#include "Point.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Triangle::Triangle(Point triangleP1, Point triangleP2, Point triangleP3) {
    p1 = triangleP1;
    p2 = triangleP2;
    p3 = triangleP3;
    cutpoints = vector<Cutpoint>();
    setColors();
}

Triangle::Triangle() {
    p1 = Point();
    p2 = Point();
    p3 = Point();
    cutpoints = vector<Cutpoint>();
    setColors();
}

void Triangle::setColors() {
    colorkey1 = (float)(rand() % 100) / 100;
    colorkey2 = (float)(rand() % 100) / 100;
    colorkey3 = (float)(rand() % 100) / 100;
}

void Triangle::render() {


    glColor3f(colorkey1, colorkey2, colorkey3);

    glBegin(GL_TRIANGLES);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p3.getX(), p3.getY());
    glEnd();
}

void Triangle::setPoints(Point point1, Point point2, Point point3) {
    p1 = point1;
    p2 = point2;
    p3 = point3;
}

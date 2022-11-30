#include "Point.hpp"
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

using namespace std;

Point::Point(float pointX, float pointY) {
    x = pointX;
    y = pointY;
}

void Point::rotate(float theta, Point center) {
//        cout <<"centerx "<<center.getX()<<endl;
//        cout <<"centery "<<center.getY()<<endl;
        cout <<"before x "<<x<<endl;
        cout <<"before y "<<y<<endl;
//    cout << theta << endl;
//    cout << round(cos(theta)) <<" "<<round(sin(theta))<<endl;
//    cout <<(this->getY()-center.getY())<<endl;
//    cout <<(this->getX()-center.getX())<<endl;
    float oldX = this->getX();
    float oldY = this->getY();
    x = round(cos(theta)) * (oldX-center.getX()) - round(sin(theta)) * (oldY-center.getY()) + center.getX();
    y = round(sin(theta)) * (oldX-center.getX()) + round(cos(theta)) * (oldY-center.getY()) + center.getY();
        cout <<"after x "<<x<<endl;
        cout <<"after y "<<y<<endl;
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

void Point::setX(float xVal) {
    x = xVal;
}

void Point::setY(float yVal) {
    y = yVal;
}

bool Point::operator == (Point &obj) {
    return obj.x == x && obj.y == y;
}

int getCanvasCoordinate(int coordinateToTransform) {
    return coordinateToTransform*2;
}

void Point::plot(int threshold) {
    glBegin(GL_QUADS);
    glVertex2f(this->getX() - threshold, this->getY() - threshold);
    glVertex2f(this->getX() + threshold, this->getY() - threshold);
    glVertex2f(this->getX() + threshold, this->getY() + threshold);
    glVertex2f(this->getX() - threshold, this->getY() + threshold);
    glEnd();
}

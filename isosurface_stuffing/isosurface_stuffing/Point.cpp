#include "Point.hpp"
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Point::Point(float pointX, float pointY) {
    x = pointX;
    y = pointY;
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

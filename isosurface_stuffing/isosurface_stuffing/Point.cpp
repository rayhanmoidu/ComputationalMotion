#include "Point.hpp"
#include <cmath>

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

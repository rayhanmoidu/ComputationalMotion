#include "Cutpoint.hpp"
#include "Point.hpp"

Cutpoint::Cutpoint(float pointX, float pointY, Point boundingPoint1, Point boundingPoint2) {
    x = pointX;
    y = pointY;
    bound1 = boundingPoint1;
    bound2 = boundingPoint2;
}

bool Cutpoint::operator == (Cutpoint &obj) {
    return obj.x == x && obj.y == y && obj.bound1 == bound1 && obj.bound2 == bound2;
}

bool Cutpoint::isContainedByVertex(Point p) {
    return bound1==p || bound2==p;
}



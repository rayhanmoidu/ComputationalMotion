#include "Isosurface.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

Isosurface::Isosurface(int width, int height, float threshold) {
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = threshold;
}

void Isosurface::render() {
    glColor3f(1, 0.41, 0.76);
    for (int i = 1; i <= screenWidth; i++) {
        for (int j = 1; j <= screenHeight; j++) {
            float distance = signedDistanceFunction(Point(i, j));
            if (distance > -renderingThreshold && distance < renderingThreshold) {
                glBegin(GL_QUADS);
                glVertex2f(i, j);
                glVertex2f(i+1, j);
                glVertex2f(i+1, j+1);
                glVertex2f(i, j+1);
                glEnd();
            }
        }
    }
}

int Isosurface::evaluatePoint(Point p) {
    if (signedDistanceFunction(p)==0) return 0;
    if (signedDistanceFunction(p)>0) return -1;
    return 1;
}

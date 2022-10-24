#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class Canvas {
    public:
        Canvas(int screenWidth, int screenHeight, char* windowTitle);
    
        void initCanvas();
        void drawTestShape();
        int getCoordinateOnCanvas(int coordinateToTransform);
    
        // getters
        GLFWwindow* getWindow();
        int getHeight();
        int getWidth();

    private:
        int width;
        int height;
        string title;
        GLFWwindow *window;
};



#endif

from cmath import sqrt
from operator import truediv
from pickle import FALSE
import OpenGL
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import point
import triangle
import random
import decimal
import math

# next steps
# convert this into cpp


screenWidth = 500
screenHeight = 500
triangleSideLength = 40
circleRadius = 200
circleOffset = circleRadius + ((500 - (2 * circleRadius)) / 2)

w,h= screenWidth,screenHeight

vertices = []
triangles = []
trianglesToConsider = []
perimeterTriangles = []

def createNewEquilateralTriangles(curX, curY, key, orientation):
    if curX <screenWidth and curY<screenHeight:
        point1 = point.Point(curX, curY)
        point2 = point.Point(curX+triangleSideLength, curY)
        if orientation=="normal":
            point3 = point.Point(curX+triangleSideLength+(triangleSideLength/2), curY+ (math.sqrt(3)/2*triangleSideLength))
            point4 = point.Point(curX+(triangleSideLength/2), curY+ (math.sqrt(3)/2*triangleSideLength))
        else:
            point3 = point.Point(curX+(triangleSideLength/2), curY+ (math.sqrt(3)/2*triangleSideLength))
            point4 = point.Point(curX-(triangleSideLength/2), curY+ (math.sqrt(3)/2*triangleSideLength))

        vertices.append(point1)
        vertices.append(point2)
        vertices.append(point3)
        vertices.append(point4)

        if orientation !="normal":
            triangle1 = triangle.Triangle(point1, point2, point3)
            triangle2 = triangle.Triangle(point1, point4, point3)
        else:
            triangle1 = triangle.Triangle(point1, point2, point4)
            triangle2 = triangle.Triangle(point2, point4, point3)

        triangles.append(triangle1)
        triangles.append(triangle2)

        if orientation=="normal":
            oppositekey="inverted"
        else:
            oppositekey="normal"

        if key=="up":
            createNewEquilateralTriangles(point4.x, point4.y, "up", oppositekey)
        
        if key=="right":
            createNewEquilateralTriangles(point2.x, point2.y, "right", orientation)

        if key=="all":
            createNewEquilateralTriangles(point2.x, point2.y, "right", orientation)
            createNewEquilateralTriangles(point3.x, point3.y, "all", oppositekey)
            createNewEquilateralTriangles(point4.x, point4.y, "up", oppositekey)


def createNewIscocelesTriangles(curX, curY, key, orientation):

    if curX <screenWidth and curY<screenHeight:
        
        point1 = point.Point(curX, curY)
        point2 = point.Point(curX+triangleSideLength, curY)
        point3 = point.Point(curX+triangleSideLength, curY+triangleSideLength)
        point4 = point.Point(curX, curY+triangleSideLength)

        vertices.append(point1)
        vertices.append(point2)
        vertices.append(point3)
        vertices.append(point4)

        if orientation =="normal":
            triangle1 = triangle.Triangle(point1, point2, point3)
            triangle2 = triangle.Triangle(point1, point4, point3)
        else:
            triangle1 = triangle.Triangle(point1, point2, point4)
            triangle2 = triangle.Triangle(point2, point4, point3)

        triangles.append(triangle1)
        triangles.append(triangle2)

        if orientation=="normal":
            oppositekey="inverted"
        else:
            oppositekey="normal"

        if key=="up":
            createNewIscocelesTriangles(point4.x, point4.y, "up", oppositekey)
        
        if key=="right":
            createNewIscocelesTriangles(point2.x, point2.y, "right", oppositekey)

        if key=="all":
            createNewIscocelesTriangles(point2.x, point2.y, "right", oppositekey)
            createNewIscocelesTriangles(point3.x, point3.y, "all", "normal")
            createNewIscocelesTriangles(point4.x, point4.y, "up", oppositekey)
    return


def setupTriangles():
    createNewIscocelesTriangles(0, 0, "all", "normal")

def drawTriangle(tri: triangle.Triangle):
    glBegin(GL_QUADS)
    glVertex2f(tri.point1.x, tri.point1.y) # Coordinates for the bottom left point
    glVertex2f(tri.point1.x, tri.point1.y) # Coordinates for the bottom right point
    glVertex2f(tri.point2.x, tri.point2.y) # Coordinates for the top left point
    glVertex2f(tri.point3.x, tri.point3.y) # Coordinates for the top left point
    glEnd()

def drawTriangles():
    for tri in trianglesToConsider:
        colorkey1 = decimal.Decimal(random.randrange(0, 100))/100
        colorkey2 = decimal.Decimal(random.randrange(0, 100))/100
        colorkey3 = decimal.Decimal(random.randrange(0, 100))/100
        glColor3f(colorkey1, colorkey2, colorkey3)
        drawTriangle(tri)

def isInsideCircleForDrawing(x, y):
    computedVal = (x-circleOffset)*(x-circleOffset) + (y-circleOffset)*(y-circleOffset)
    threshold = 200
    radiusSquared = circleRadius*circleRadius
    if computedVal > radiusSquared-threshold and computedVal < radiusSquared+threshold:
        return True
    return False

def isVertexInsideCircle(x, y):
    computedVal = (x-circleOffset)*(x-circleOffset) + (y-circleOffset)*(y-circleOffset)
    radiusSquared = circleRadius*circleRadius
    if computedVal==radiusSquared:
        return 0
    if computedVal<radiusSquared:
        return 1
    return -1


def drawCircle():
    for i in range(1, 500):
        for j in range(1, 500):
            if (isInsideCircleForDrawing(i, j)):
                glBegin(GL_QUADS)
                glVertex2f(i, j) # Coordinates for the bottom left point
                glVertex2f(i+1, j) # Coordinates for the bottom left point
                glVertex2f(i+1, j+1) # Coordinates for the bottom left point
                glVertex2f(i, j+1) # Coordinates for the bottom left point
                
                glEnd()

def filterTriangles():
    for triangle in triangles:
        isInside1 = isVertexInsideCircle(triangle.point1.x, triangle.point1.y)
        isInside2 = isVertexInsideCircle(triangle.point2.x, triangle.point2.y)
        isInside3 = isVertexInsideCircle(triangle.point3.x, triangle.point3.y)
        if isInside1==1 or isInside2==1 or isInside3==1:
            trianglesToConsider.append(triangle)
            if isInside1==-1 or isInside2==-1 or isInside3==-1:
                perimeterTriangles.append(triangle)


def findCutPoints():
    for tri in perimeterTriangles:
        isInside1 = isVertexInsideCircle(tri.point1.x, tri.point1.y)
        isInside2 = isVertexInsideCircle(tri.point2.x, tri.point2.y)
        isInside3 = isVertexInsideCircle(tri.point3.x, tri.point3.y)

        negativeVertices = []
        positiveVertices = []
        if isInside1==-1:
            negativeVertices.append(tri.point1)
        if isInside1==1:
            positiveVertices.append(tri.point1)
        if isInside2==-1:
            negativeVertices.append(tri.point2)
        if isInside2==1:
            positiveVertices.append(tri.point2)
        if isInside3==-1:
            negativeVertices.append(tri.point3)
        if isInside3==1:
            positiveVertices.append(tri.point3)

        for posVertex in positiveVertices:
            for negVertex in negativeVertices:

                slope=0

                x1=0
                x2=0
                y1=0
                y2=0

                # undefined slope
                if posVertex.x - negVertex.x==0:
                    x1 = posVertex.x
                    x2 = posVertex.x

                    a = 1
                    b = -2*circleOffset
                    c = circleOffset*circleOffset + (x1-circleOffset)*(x1-circleOffset) - circleRadius*circleRadius

                    discriminant = b*b - 4*a*c

                    if (2*a*c!=0 and discriminant>=0):
                        y1 = ((-1)*b + math.sqrt(discriminant)) / (2*a)
                        y2 = ((-1)*b - math.sqrt(discriminant)) / (2*a)
                    
                # defined slope
                if (posVertex.x - negVertex.x)!=0:
                    slope = (posVertex.y - negVertex.y) / (posVertex.x - negVertex.x)
                    yIntercept = posVertex.y - (slope*posVertex.x)

                    # (x-d)^2 + (y-h)^2 = r^2
                    # y = mx + b

                    # a = 1 + m^2
                    a = 1 + (slope*slope)
                    # b = -2d + 2m(b-h)
                    b = (-2 * circleOffset) + (2 * slope * (yIntercept - circleOffset))
                    # c = -r^2 + d^2 + (b-h)^2
                    c = circleOffset*circleOffset + (yIntercept-circleOffset)*(yIntercept-circleOffset) - circleRadius*circleRadius

                    discriminant = b*b - 4*a*c

                    if (2*a*c!=0 and discriminant>=0):
                        x1 = ((-1)*b + math.sqrt(discriminant)) / (2*a)
                        x2 = ((-1)*b - math.sqrt(discriminant)) / (2*a)

                    y1 = slope*x1 + yIntercept
                    y2 = slope*x2 + yIntercept


                if (x1 >= posVertex.x and x1 <= negVertex.x) or (x1 >= negVertex.x and x1 <= posVertex.x):
                    if (y1 >= posVertex.y and y1 <= negVertex.y) or (y1 >= negVertex.y and y1 <= posVertex.y):
                        glBegin(GL_QUADS)
                        glVertex2f(x1-2, y1-2) # Coordinates for the bottom left point
                        glVertex2f(x1+2, y1-2) # Coordinates for the bottom left point
                        glVertex2f(x1+2, y1+2) # Coordinates for the bottom left point
                        glVertex2f(x1-2, y1+2) # Coordinates for the bottom left point
                        glEnd()
                
                if (x2 >= posVertex.x and x2 <= negVertex.x) or (x2 >= negVertex.x and x2 <= posVertex.x):
                    if (y2 >= posVertex.y and y2 <= negVertex.y) or (y2 >= negVertex.y and y2 <= posVertex.y):
                        glBegin(GL_QUADS)
                        glVertex2f(x2-2, y2-2) # Coordinates for the bottom left point
                        glVertex2f(x2+2, y2-2) # Coordinates for the bottom left point
                        glVertex2f(x2+2, y2+2) # Coordinates for the bottom left point
                        glVertex2f(x2-2, y2+2) # Coordinates for the bottom left point
                        glEnd()


def iterate():
    glViewport(0, 0, 500, 500)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, 500, 0.0, 500, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    drawTriangles()
    glColor3f(1.0, 0, 3.0)
    drawCircle()
    glColor3f(3.0, 3.0, 1.0)
    findCutPoints()
    glutSwapBuffers()

glutInit()
setupTriangles()
filterTriangles()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(500, 500)
glutInitWindowPosition(0, 0)
wind = glutCreateWindow("OpenGL Coding Practice")
glutDisplayFunc(showScreen)
# glutIdleFunc()
glutMainLoop()
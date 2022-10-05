from cmath import inf, sqrt
from operator import truediv
from pickle import FALSE
import OpenGL
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from cutpoint import Cutpoint
import point
import triangle
import random
import decimal
import math

# next steps
# reread article and make sure about step 4 of algo
# try with equilateral triangle


screenWidth = 500
screenHeight = 500
triangleSideLength = 17
circleRadius = 200
circleOffset = circleRadius + ((500 - (2 * circleRadius)) / 2)

w,h= screenWidth,screenHeight

vertices = []
triangles = []
trianglesToConsider = []
perimeterTriangles = []
cutpoints = []

def distanceFromIsoSurface(x, y):
    return distanceFromBox(x, y)

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
    createNewEquilateralTriangles(0, 0, "all", "normal")

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

def distanceFromCircle(x, y):
    length = math.sqrt((x-250)*(x-250) + (y-250)*(y-250))
    return length - circleRadius

def distanceFromBox(x, y):
    newX = x - 250
    newY = y - 250

    boxWidth = 200
    boxHeight = 200

    px = abs(newX) - boxWidth
    py = abs(newY) - boxHeight

    toSquareX = px
    toSquareY = py

    if ((px==0 and py<0) or (py==0 and px < 0)):
        return 0
    elif (px < 0 and py < 0):
        return max(px, py)
    elif px < 0:
        return py
    elif py < 0:
        return px
    else:
        return math.sqrt(toSquareX*toSquareX + toSquareY*toSquareY)

def distanceFromEquilateralTriangle(x, y):
    k = math.sqrt(2)

    newX = abs(x-250) - 250
    newY = (y-250) + 250/k

    if (newX + k*newY > 0):
        newX = (newX - k*newY) / 500
        newY = (-k*newX - newY) / 500
    
    newX = newX - min(max( newX , -500 ), 0 )

    length = math.sqrt(newX*newX + newY*newY)

    if newY>=0:
        return -length
    elif newY==0:
        return 0
    else:
        return length



def isVertexInsideIsosurface(x, y):
    if (distanceFromIsoSurface(x, y)==0):
        return 0
    elif distanceFromIsoSurface(x, y)>0:
        return -1
    else:
        return 1


def drawIsosurface():
    threshold = 0.5
    for i in range(1, 500):
        for j in range(1, 500):
            if (distanceFromIsoSurface(i, j)>-threshold and distanceFromIsoSurface(i, j)<threshold):
                glBegin(GL_QUADS)
                glVertex2f(i, j) # Coordinates for the bottom left point
                glVertex2f(i+1, j) # Coordinates for the bottom left point
                glVertex2f(i+1, j+1) # Coordinates for the bottom left point
                glVertex2f(i, j+1) # Coordinates for the bottom left point
                
                glEnd()

def filterTriangles():
    for triangle in triangles:
        isInside1 = isVertexInsideIsosurface(triangle.point1.x, triangle.point1.y)
        isInside2 = isVertexInsideIsosurface(triangle.point2.x, triangle.point2.y)
        isInside3 = isVertexInsideIsosurface(triangle.point3.x, triangle.point3.y)
        if isInside1==1 or isInside2==1 or isInside3==1:
            trianglesToConsider.append(triangle)
            if isInside1==-1 or isInside2==-1 or isInside3==-1:
                perimeterTriangles.append(triangle)

def moreIdealFindCutPointsHelper(posVertex: point.Point, negVertex: point.Point):
    retValX = 0
    retValY = 0

    x1 = negVertex.x
    x2 = posVertex.x
    y1 = negVertex.y
    y2 = posVertex.y

    dx = x2 - x1
    dy = y2 - y1

    a = abs(distanceFromIsoSurface(x1, y1))
    b = abs(distanceFromIsoSurface(x2, y2))
    cutPointPercentage = a / (a + b)

    retValX = x1 + cutPointPercentage*dx
    retValY = y1 + cutPointPercentage*dy

    return point.Point(retValX, retValY)



def findCutPoints():
    for tri in perimeterTriangles:
        isInside1 = isVertexInsideIsosurface(tri.point1.x, tri.point1.y)
        isInside2 = isVertexInsideIsosurface(tri.point2.x, tri.point2.y)
        isInside3 = isVertexInsideIsosurface(tri.point3.x, tri.point3.y)

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
                newCutPoint = moreIdealFindCutPointsHelper(posVertex, negVertex)
                newCutPointObj = Cutpoint(newCutPoint.x, newCutPoint.y, posVertex, negVertex)
                tri.cutpoints.append(newCutPointObj)

                # cutpoints.append(newCutPointObj)

def plotCutPoints():
    for triangle in perimeterTriangles:
        cutpoints.extend(triangle.cutpoints)

    for cutpoint in cutpoints:
        xToPlot = cutpoint.x
        yToPlot = cutpoint.y
        print("REMAINING CP", xToPlot, yToPlot)
        glBegin(GL_QUADS)
        glVertex2f(xToPlot-2, yToPlot-2) # Coordinates for the bottom left point
        glVertex2f(xToPlot+2, yToPlot-2) # Coordinates for the bottom left point
        glVertex2f(xToPlot+2, yToPlot+2) # Coordinates for the bottom left point
        glVertex2f(xToPlot-2, yToPlot+2) # Coordinates for the bottom left point
        glEnd()

def distanceBetweenTwoPoints(point1: point.Point, point2: point.Point):
    return math.sqrt((point2.x - point1.x)*(point2.x - point1.x) + (point2.y - point1.y)*(point2.y - point1.y))

def trimCutPoints():
    for triangle in perimeterTriangles:
        points = [triangle.point1, triangle.point2, triangle.point3]
        for curPoint in points:
            if (isVertexInsideIsosurface(curPoint.x, curPoint.y)==-1):
                trianglesSharingVertex = []
                for tri in perimeterTriangles:
                    if tri.doesContainVertex(curPoint):
                        trianglesSharingVertex.append(tri)
                cutPointsToConsider = []
                for tri in trianglesSharingVertex:
                    potentialCutpoints = tri.cutpoints
                    for potentialCutpoint in potentialCutpoints:
                        if (potentialCutpoint.isContainedByVertex(curPoint)):
                            cutPointsToConsider.append(potentialCutpoint)
                
                lowestDistance = inf 
                lowestDistanceIndex = -1
                for i in range(0, len(cutPointsToConsider)):
                    if (distanceBetweenTwoPoints(curPoint, point.Point(cutPointsToConsider[i].x, cutPointsToConsider[i].y)) < lowestDistance):
                        lowestDistanceIndex = i
                        lowestDistance = distanceBetweenTwoPoints(curPoint, point.Point(cutPointsToConsider[i].x, cutPointsToConsider[i].y))
                if lowestDistanceIndex!=-1:
                    cutPointToWarpTo = cutPointsToConsider[lowestDistanceIndex]
                    # print("Wrapping to ", cutPointToWarpTo.x, cutPointToWarpTo.y)

                    for tri in trianglesSharingVertex:
                        tri.wrapVertexToCutpoint(curPoint.x, curPoint.y, cutPointToWarpTo)

                for cutPointToRemove in cutPointsToConsider:
                    for tritri in perimeterTriangles:
                        if tritri.doesContainCutpoint(cutPointToRemove):
                            tritri.removeCutpoint(cutPointToRemove)



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

    findCutPoints()
    trimCutPoints()
    drawTriangles()
    glColor3f(1.0, 0, 3.0)
    drawIsosurface()
    glColor3f(3.0, 3.0, 1.0)
    plotCutPoints()

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
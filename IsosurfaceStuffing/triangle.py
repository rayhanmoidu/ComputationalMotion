from operator import truediv
import point
import cutpoint

class Triangle():
    def __init__(self, point1: point.Point, point2: point.Point, point3: point.Point):
        self.point1 = point1
        self.point2 = point2
        self.point3 = point3
        self.cutpoints = []

    def doesContainCutpoint(self, cutpoint: cutpoint):
        for testCutpoint in self.cutpoints:
            if (testCutpoint.x == cutpoint.x and testCutpoint.y == cutpoint.y):
                return True
            else:
                return False
    
    def doesContainVertex(self, vertex: point):
        if self.point1.x == vertex.x and self.point1.y == vertex.y:
            return True
        if self.point2.x == vertex.x and self.point2.y == vertex.y:
            return True
        if self.point3.x == vertex.x and self.point3.y == vertex.y:
            return True
        return False

    def wrapVertexToCutpoint(self, originalVertexX: float, originalVertexY: float, cutpoint: cutpoint):
        print("wrapping", originalVertexX, originalVertexY)
        if self.point1.x == originalVertexX and self.point1.y == originalVertexY:
            print("found")
            self.point1 = point.Point(cutpoint.x, cutpoint.y)
            # self.point1.x += (cutpoint.x - self.point1.x)
            # self.point1.y += (cutpoint.y - self.point1.y)
            return
        elif self.point2.x == originalVertexX and self.point2.y == originalVertexY:
            print("found")
            self.point2 = point.Point(cutpoint.x, cutpoint.y)
            return
        elif self.point3.x == originalVertexX and self.point3.y == originalVertexY:
            print("found")
            self.point3 = point.Point(cutpoint.x, cutpoint.y)
            return

    def removeCutpoint(self, cutpoint: cutpoint):
        for testCutpoint in self.cutpoints:
            if (testCutpoint.x == cutpoint.x and testCutpoint.y == cutpoint.y):
                self.cutpoints.remove(testCutpoint)
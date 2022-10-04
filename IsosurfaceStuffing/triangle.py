import point

class Triangle():
    def __init__(self, point1: point.Point, point2: point.Point, point3: point.Point):
        self.point1 = point1
        self.point2 = point2
        self.point3 = point3
        self.cutpoints = []
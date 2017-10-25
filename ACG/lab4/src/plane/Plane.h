#ifndef LAB4_PLANE_H
#define LAB4_PLANE_H


#include "../point/Point.h"

class Plane {
    Point points[4];
    float A1, A2, A3;
public:
    void setPoints(Point &point1, Point &point2, Point &point3, Point &point4);
    Point* getPoints();

    Point getMaxPoint();
    Point getLowPoint();
    float getZValue(int x, int y);
};


#endif

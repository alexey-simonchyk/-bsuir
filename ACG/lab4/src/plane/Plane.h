#ifndef LAB4_PLANE_H
#define LAB4_PLANE_H


#include "../point/Point.h"

class Plane {
    Point points[4];
    Point rotationPoints[4];
    double A, B, C, D;
public:
    Plane *hole;
    bool withHole = false;
    void setPoints(Point point1, Point point2, Point point3, Point point4);
    Point* getPoints();
    void setHole(Plane* plane);

    Point getMaxPoint(int windowWidth, int windowHeight);
    Point getLowPoint(int windowWidth, int windowHeight);
    double getZValue(double x, double y);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    void calculatePlane();
    void makeProjection(int k, int windowWidth, int windowHeight);

    void rotateAxis(double x, double y, double z, double angle);
};


#endif

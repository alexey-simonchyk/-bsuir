#ifndef LAB3_RECTANGLE_H
#define LAB3_RECTANGLE_H


#include "Point.h"

class Rectangle {
    Point points[4];
    int depthValue;
public:
    void setPoints(Point points[]);
    Point *getPoints();
    void rotate(double angle);
    void move(int x, int y);
    void setDepth(int value);
    int getDepth();

    Point getMaxPoint();
    Point getLowPoint();
};


#endif

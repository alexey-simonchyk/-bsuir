#ifndef LAB3_RECTANGLE_H
#define LAB3_RECTANGLE_H


#include "Point.h"

class Rectangle {
    Point points[4];
public:
    void setPoints(Point points[]);
    Point *getPoints();
    void rotate(double angle);
    void move(int x, int y);
};


#endif

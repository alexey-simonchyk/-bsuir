#ifndef LAB4_LINE_H
#define LAB4_LINE_H


#include "../point/Point.h"

class Line {
Point point1, point2;
public:
    Line(Point point1, Point point2);
    void drawLine();

};


#endif //LAB4_LINE_H

#include "Plane.h"

void Plane::setPoints(Point &point1, Point &point2, Point &point3, Point &point4) {
    this->points[0] = point1;
    this->points[1] = point2;
    this->points[2] = point3;
    this->points[3] = point4;
    this->A1 = (points[1].y - points[0].y) * (points[2].z - points[0].z) - (points[2].y - points[0].y) * (points[1].z - points[0].z);
    this->A2 = -((points[1].x - points[0].x) * (points[2].z - points[0].z) - (points[2].x - points[0].x) * (points[1].z - points[0].z));
    this->A3 = (points[1].x - points[0].x) * (points[2].y - points[0].y) - (points[2].x - points[0].x) * (points[1].y - points[0].y);
}

Point *Plane::getPoints() {
    return this->points;
}

Point Plane::getMaxPoint() {
    Point max = {.x = this->points[0].x, .y = this->points[0].y, .z = this->points[0].z};
    for (int i = 1; i < 4; i++) {
        if (max.x < this->points[i].x) {
            max.x = this->points[i].x;
        }
        if (max.y < this->points[i].y) {
            max.y = this->points[i].y;
        }
    }
    return max;
}

Point Plane::getLowPoint() {
    Point min = {.x = this->points[0].x, .y = this->points[0].y, .z = this->points[0].z};
    for (int i = 1; i < 4; i++) {
        if (min.x > this->points[i].x) {
            min.x = this->points[i].x;
        }
        if (min.y > this->points[i].y) {
            min.y = this->points[i].y;
        }
    }
    return min;
}

float Plane::getZValue(int x, int y) {
    float z = ((points[0].x - x) * this->A1 + (points[0].y - y) * this->A2) / this->A3 + points[0].z;
    return z;
}



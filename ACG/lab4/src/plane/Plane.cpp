#include <math.h>
#include "Plane.h"

void Plane::setPoints(Point point1, Point point2, Point point3, Point point4) {
    this->points[0] = point1;
    this->points[1] = point2;
    this->points[2] = point3;
    this->points[3] = point4;
    this->rotationPoints[0] = point1;
    this->rotationPoints[1] = point2;
    this->rotationPoints[2] = point3;
    this->rotationPoints[3] = point4;
    this->calculatePlane();
}

Point *Plane::getPoints() {
    return this->points;
}

Point Plane::getMaxPoint(int windowWidth, int windowHeight) {
    Point max = {.x = this->points[0].x, .y = this->points[0].y, .z = this->points[0].z};
    for (int i = 1; i < 4; i++) {
        if (max.x < this->points[i].x) {
            max.x = this->points[i].x;
        }
        if (max.y < this->points[i].y) {
            max.y = this->points[i].y;
        }
    }
    max.x += windowWidth / 2;
    max.y += windowHeight / 2;
    return max;
}

Point Plane::getLowPoint(int windowWidth, int windowHeight) {
    Point min = {.x = this->points[0].x, .y = this->points[0].y, .z = this->points[0].z};
    for (int i = 1; i < 4; i++) {
        if (min.x > this->points[i].x) {
            min.x = this->points[i].x;
        }
        if (min.y > this->points[i].y) {
            min.y = this->points[i].y;
        }
    }
    min.x += windowWidth / 2;
    min.y += windowHeight / 2;
    return min;
}

double Plane::getZValue(double x, double y) {
    double z;
    if (C == 0) {
        double z = points[0].z;
        for (int i = 1; i < 4; i++) {
            if (z < points[i].z) {
                z = points[i].z;
            }
        }
        return z;
    }
    z = -1 * (A * round(x) + B * round(y) + D) / C;
    return round(z);
}

void Plane::rotateX(double angle) {
    if (withHole) {
        hole->rotateX(angle);
    }
    angle *= 3.14159265 / 180;
    for (int i = 0; i < 4; i++) {
        double y = rotationPoints[i].y, z = rotationPoints[i].z;
        double tempY = cos(angle) * y - sin(angle) * z;
        double tempZ = sin(angle) * y + cos(angle) * z;
        points[i].y = round(tempY);
        points[i].z = round(tempZ);
        rotationPoints[i].y = tempY;
        rotationPoints[i].z = tempZ;

    }
    this->calculatePlane();
}

void Plane::rotateY(double angle) {
    if (withHole) {
        hole->rotateY(angle);
    }
    angle *= 3.14159265 / 180;
    for (int  i = 0; i < 4; i++) {
        double x = rotationPoints[i].x, z = rotationPoints[i].z;
        double tempX = cos(angle) * x - sin(angle) * z;
        double tempZ = sin(angle) * x + cos(angle) * z;
        points[i].x = round(tempX);
        points[i].z = round(tempZ);
        rotationPoints[i].x = tempX;
        rotationPoints[i].z = tempZ;
    }
    this->calculatePlane();
}

void Plane::rotateZ(double angle) {
    if (withHole) {
        hole->rotateZ(angle);
    }
    angle *= 3.14159265 / 180;
    for (int i = 0; i < 4; i++) {
        double x = rotationPoints[i].x, y = rotationPoints[i].y;
        double tempX = cos(angle) * x - sin(angle) * y;
        double tempY = sin(angle) * x + cos(angle) * y;
        points[i].x = round(tempX);
        points[i].y = round(tempY);
        rotationPoints[i].x = tempX;
        rotationPoints[i].y = tempY;
    }
    this->calculatePlane();
}

void Plane::calculatePlane() {
    double y1 = round(points[0].y), y2 = round(points[1].y), y3 = round(points[2].y);
    double x1 = round(points[0].x), x2 = round(points[1].x), x3 = round(points[2].x);
    double z1 = round(points[0].z), z2 = round(points[1].z), z3 = round(points[2].z);

    A = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    B = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
    C = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    D = -1 * (x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
}

void Plane::setHole(Plane *plane) {
    this->hole = plane;
    this->withHole = true;
}


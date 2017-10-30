#include "Plane.h"
#include <cmath>

void Plane::setPoints(Point point1, Point point2, Point point3, Point point4) {
    this->points[0] = point1;
    this->points[1] = point2;
    this->points[2] = point3;
    this->points[3] = point4;
    this->rotationPoints[0] = point1;
    this->rotationPoints[1] = point2;
    this->rotationPoints[2] = point3;
    this->rotationPoints[3] = point4;
}

Point *Plane::getPoints() {
    return this->points;
}

Point *Plane::getRotationPoints() {
    return this->rotationPoints;
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
        if (max.z < this->points[i].z) {
            max.z = this->points[i].z;
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
        if (min.z > this->points[i].z) {
            min.z = this->points[i].z;
        }
    }
    min.x += windowWidth / 2;
    min.y += windowHeight / 2;
    return min;
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
}

void Plane::setHole(Plane *plane) {
    this->hole = plane;
    this->withHole = true;
}

void Plane::rotateAxis(double rx, double ry, double rz, double angle) {
    if (withHole) {
        hole->rotateAxis(rx, ry, rz, angle);
    }
    angle *= 3.14159265 / 180;
    double temp = 1 - cos(angle);
    for (int i = 0; i < 4; i++) {
        double x = rotationPoints[i].x , y = rotationPoints[i].y, z = rotationPoints[i].z;
        double tempX = x * (rx * rx * temp + cos(angle)) + y * (rx * ry * temp - rz * sin(angle)) + z * (rx * rz * temp + ry * sin(angle));
        double tempY = x * (rx * ry * temp + rz * sin(angle)) + y * (ry * ry * temp + cos(angle)) + z * (ry * rz * temp - rx * sin(angle));
        double tempZ = x * (rx * rz * temp - ry * sin(angle)) + y * (ry * rz * temp + rx * sin(angle)) + z * (rz *  rz * temp + cos(angle));
        rotationPoints[i].x = tempX;
        rotationPoints[i].y = tempY;
        rotationPoints[i].z = tempZ;
    }

}

void Plane::makeProjection(int k, int windowWidth, int windowHeight) {
    if (withHole) {
        hole->makeProjection(k, windowWidth, windowHeight);
    }
    for (int i = 0; i < 4; i++) {
        points[i].y = int(round(round(rotationPoints[i].y) * k / (round(rotationPoints[i].z) + k)));
        points[i].x = int(round(round(rotationPoints[i].x) * k / (round(rotationPoints[i].z) + k)));
    }
}

void Plane::shiftCoordinates(double x, double y, double z) {
    if (withHole) {
        this->hole->shiftCoordinates(x, y, z);
    }
    for (int  i = 0; i < 4; i++) {
        rotationPoints[i].x += x;
        rotationPoints[i].y += y;
        rotationPoints[i].z += z;
        points[i].x = round(rotationPoints[i].x);
        points[i].y = round(rotationPoints[i].y);
        points[i].z = round(rotationPoints[i].z);
    }
}


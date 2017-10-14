#include <cmath>
#include "Rectangle.h"

void Rectangle::setPoints(Point *points) {
    for (int i = 0; i < 4; i++) {
        this->points[i] = points[i];
    }
}

Point *Rectangle::getPoints() {
    return this->points;
}

void Rectangle::rotate(double angle) {
    angle *= 3.14159265 / 180;
    Point center;
    center.x = (this->points[0].x + this->points[2].x) / 2;
    center.y = (this->points[0].y + this->points[2].y) / 2;

    for (auto &point : this->points) {
        int x1 = point.x - center.x;
        int y1 = point.y - center.y;

        point.x = int(round(x1 * cos(angle) - y1 * sin(angle))) + center.x;
        point.y = int(round(x1 * sin(angle) + y1 * cos(angle))) + center.y;
    }
}

void Rectangle::move(int x, int y) {
    for (auto &point: this->points) {
        point.x += x;
        point.y += y;
    }
}

int Rectangle::getDepth() {
    return this->depthValue;
}

void Rectangle::setDepth(int value) {
    this->depthValue = value;
}

Point Rectangle::getMaxPoint() {
    Point max = {.x = this->points[0].x, .y = this->points[0].y};
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

Point Rectangle::getLowPoint() {
    Point min = {.x = this->points[0].x, .y = this->points[0].y};
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

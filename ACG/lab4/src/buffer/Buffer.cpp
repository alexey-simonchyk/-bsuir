#include <cmath>
#include "Buffer.h"

void Buffer::clearTempBuffer() {
    for (int i = 0; i <= this->height; i++) {
        for (int j = 0; j <= this->width; j++) {
            this->temp_buffer[i][j] = BACKGROUND_BUFFER;
        }
    }
}

void Buffer::initBuffer(int screenHeight, int screenWidth) {
    if (this->height > 0 && this->width > 0) {
        for (int i = 0; i <= this->height; i++) {
            delete this->buffer[i];
            delete this->temp_buffer[i];
        }
        delete this->buffer;
        delete this->temp_buffer;
    }

    this->height = screenHeight - 1;
    this->width = screenWidth - 1;
    this->buffer = new double*[screenHeight];
    this->temp_buffer = new double*[screenHeight];

    for (int i = 0; i < screenHeight; i++) {
        this->buffer[i] = new double[screenWidth];
        this->temp_buffer[i] = new double[screenWidth];
    }
    this->clearBuffer();
    this->clearTempBuffer();
}

void Buffer::clearBuffer() {
    for (int i = 0; i <= this->height; i++) {
        for (int j = 0; j <= this->width; j++) {
            this->buffer[i][j] = BACKGROUND_BUFFER;
        }
    }
}

void Buffer::fillPlaneInTempBuffer(Point min, Point max, Plane &plane) {

    Point startPoint = {.x = -1, .y = -1, .z = -1};

    min.x = min.x < 0 ? 0 : min.x;
    min.y = min.y < 0 ? 0 : min.y;
    max.x = max.x < 0 ? 0 : max.x;
    max.y = max.y < 0 ? 0 : max.y;
    for (int i = int(round(min.y)); i <= max.y && i <= this->height; i++) {
        startPoint.x = -1;
        for (int j = int(round(min.x)); j <= max.x && j <= this->width; j++) {
            double temp = this->temp_buffer[i][j];

            if (temp != BACKGROUND_BUFFER && startPoint.x != -1) {
                for (int k = int(round(startPoint.x + 1)); k < j; k++) {
                    double z = plane.getZValue(k - (this->width + 1) / 2, i - (this->height + 1) / 2);
                    this->temp_buffer[i][k] = z;
                }
            }
            if (temp != BACKGROUND_BUFFER) {
                startPoint.set(j, i, 0);
            }
        }
    }
}

void Buffer::setTempBuffer(int x, int y, double z) {
    this->temp_buffer[y][x] = z;
}

void Buffer::shiftToMainBuffer() {
    for (int i = 0; i <= this->height; i++) {
        for (int j = 0; j <= this->width; j++) {
            if (this->buffer[i][j] > this->temp_buffer[i][j]) {
                this->buffer[i][j] = this->temp_buffer[i][j];
            }
        }
    }
}

double Buffer::getValue(int x, int y) {
    return this->buffer[y][x];
}

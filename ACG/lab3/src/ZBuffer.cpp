#include "ZBuffer.h"
#include "Point.h"


void ZBuffer::initBuffer(int screenHeight, int screenWidth) {
    if (this->height > 0 && this->width > 0) {
        for (int i = 0; i <= this->height; i++) {
            delete this->buffer[i];
        }
        delete this->buffer;
    }
    this->height = screenHeight - 1;
    this->width = screenWidth - 1;
    this->buffer = new int*[screenHeight];
    for (int i = 0; i < screenHeight; i++) {
        this->buffer[i] = new int[screenWidth];
    }
    this->clearBuffer();
}

int ZBuffer::getValue(int x, int y) {
    return this->buffer[y][x];
}

void ZBuffer::setValue(int x, int y, int value) {
    if (this->buffer[y][x] == 0) {
        this->buffer[y][x] = value;
    }
}

void ZBuffer::clearBuffer() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->buffer[i][j] = 0;
        }
    }
}

void ZBuffer::fillRectInBuffer(int xMin, int yMin, int xMax, int yMax, int value) {
    Point startPoint = {.x = -1, .y = -1};

    xMin = xMin < 0 ? 0 : xMin;
    yMin = yMin < 0 ? 0 : yMin;
    xMax = xMax < 0 ? 0 : xMax;
    yMax = yMax < 0 ? 0 : yMax;

    for (int i = yMin; i <= yMax && i <= this->height; i++) {
        startPoint.x = -1;
        for (int j = xMin; j <= xMax && j <= this->width; j++) {
            int temp = this->buffer[i][j];

            if (temp != 0 && startPoint.x != -1) {
                for (int k = startPoint.x + 1; k < j; k++) {
                    this->buffer[i][k] = value;
                }
                startPoint.x = j;
                startPoint.y = i;
            } else if (temp != 0) {
                startPoint.x = j;
                startPoint.y = i;
            }
        }
    }
}

#ifndef LAB4_BUFFER_H
#define LAB4_BUFFER_H


#include "../plane/Plane.h"
#define BACKGROUND_BUFFER 15000

class Buffer {
    int height = 0, width = 0;
    float **buffer{};
    float **temp_buffer{};
public:
    void fillPlaneInTempBuffer(Point min, Point max, Plane &plane);
    void setTempBuffer(int x, int y, float z);
    void clearTempBuffer();
    void initBuffer(int screenHeight, int screenWidth);
    void clearBuffer();
    void shiftToMainBuffer();
    float getValue(int x, int y);
};


#endif //LAB4_BUFFER_H

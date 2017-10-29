#ifndef LAB4_BUFFER_H
#define LAB4_BUFFER_H


#include "../plane/Plane.h"
#define BACKGROUND_BUFFER 15000
#define HOLE 15001

class Buffer {
    int height = 0, width = 0;
    double **buffer{};
    double **temp_buffer{};
public:
    void fillPlaneInTempBuffer(Point min, Point max, Plane &plane);
    void fillHoleInTempBuffer(Point min, Point max, Plane &plane);
    void setTempBuffer(int x, int y, double z);
    void clearTempBuffer();
    void initBuffer(int screenHeight, int screenWidth);
    void clearBuffer();
    void shiftToMainBuffer();
    double getValue(int x, int y);

};


#endif //LAB4_BUFFER_H

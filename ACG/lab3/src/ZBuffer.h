#ifndef LAB3_ZBUFFER_H
#define LAB3_ZBUFFER_H


class ZBuffer {
    int height = 0, width = 0;
public:
    int **buffer{};
    void initBuffer(int screenHeight, int screenWidth);
    int getValue(int x, int y);
    void setValue(int x, int y, int value);
    void clearBuffer();
    void fillRectInBuffer(int xMin, int yMin, int xMax, int yMax, int value);
};


#endif

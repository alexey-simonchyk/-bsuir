#ifndef LAB3_ANIMATION_H
#define LAB3_ANIMATION_H

#include "Rectangle.h"

#define NUMBER_STEPS 30
#define X_DISTANCE 65
#define Y_DISTANCE 65

class Animation {
    int dx = 0, dy = 0;
    int dAngle = 0;
    int numberSteps = 0;
    bool playAnimation = true;
public:
    bool isPlayAnimation();
    void init(Rectangle *rectangles);
    void animate(Rectangle *rectangles);
};


#endif

#include <cmath>
#include "Animation.h"

void Animation::init(Rectangle *rectangles) {
    Point centerOne = rectangles[0].getCenter();
    Point centerTwo = rectangles[1].getCenter();

    dx = (int)round((centerTwo.x - centerOne.x - X_DISTANCE) / ( NUMBER_STEPS * 2 ));
    dy = (int)round((centerTwo.y - centerOne.y - Y_DISTANCE) / ( NUMBER_STEPS * 2));
    dAngle = (int)round(90 / NUMBER_STEPS);
}

bool Animation::isPlayAnimation() {
    return this->playAnimation;
}

void Animation::animate(Rectangle *rectangles) {
    rectangles[0].move(dx, dy);
    rectangles[0].rotate(dAngle);

    rectangles[1].move(-dx, -dy);
    rectangles[1].rotate(-dAngle);
    numberSteps++;
    if (numberSteps == NUMBER_STEPS) {
        playAnimation = false;
    }
}

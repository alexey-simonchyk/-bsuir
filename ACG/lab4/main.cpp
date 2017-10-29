#include <SDL2/SDL.h>
#include <iostream>
#include "src/point/Point.h"
#include "src/plane/Plane.h"
#include "src/buffer/Buffer.h"
#include <list>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 800

int windowWidth = DEFAULT_WINDOW_WIDTH;
int windowHeight = DEFAULT_WINDOW_HEIGHT;

#define NUMBER_PLANES 10
#define DASH_STEP 8
#define ROTATION_ANGLE 2
#define REACTION_TIME 35
#define DRAW_INVISIBLE false

Buffer *buffer = nullptr;

void drawLineInZBuffer(Point startPoint, Point endPoint, Plane &plane, bool hole);
void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, Plane &plane);
void draw(SDL_Renderer *renderer, Plane *planes, int numberPlains);


int main(int argc, char* argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);

    buffer = new Buffer();
    buffer->initBuffer(windowHeight, windowWidth);

    window = SDL_CreateWindow(
            "Lab 4",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight,
            SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    int L = 360;
    int H = L/3;
    int W = L/4;
    W /= 2;
    H /= 2;
    L /= 2;
    Point x1 = {.x = -W, .y = -H, .z = -L};
    Point x2 = {.x = -W, .y = -H, .z = L};
    Point x3 = {.x = W, .y = -H, .z = L};
    Point x4 = {.x = W, .y = -H, .z = -L};

    Point x5 = {.x = -W, .y = H, .z = -L};
    Point x6 = {.x = -W, .y = H, .z = L};
    Point x7 = {.x = W, .y = H, .z = L};
    Point x8 = {.x = W, .y = H, .z = -L};

    W /= 2;
//    W /= 3;
    H /= 2;
//    H /= 12;
    Point x9 = {.x = -W, .y = -H, .z = -L};
    Point x10 = {.x = -W, .y = -H, .z = L};
    Point x11 = {.x = W, .y = -H, .z = L};
    Point x12 = {.x = W, .y = -H, .z = -L};

    Point x13 = {.x = -W, .y = H, .z = -L};
    Point x14 = {.x = -W, .y = H, .z = L};
    Point x15 = {.x = W, .y = H, .z = L};
    Point x16 = {.x = W, .y = H, .z = -L};

    Plane plane1, plane2, plane3, plane4, plane5, plane6, plane7, plane8, plane9, plane10;
    Plane hole1, hole2;

    hole1.setPoints(x9, x12, x16, x13);
    hole2.setPoints(x10, x11, x15, x14);

    plane3.setHole(&hole1);
    plane5.setHole(&hole2);

    plane1.setPoints(x1, x2, x3, x4);
    plane2.setPoints(x5, x6, x7, x8);
    plane3.setPoints(x1, x4, x8, x5);
    plane4.setPoints(x1, x5, x6, x2);
    plane5.setPoints(x3, x2, x6, x7);
    plane6.setPoints(x3, x4, x8, x7);

    plane7.setPoints(x9, x10, x11, x12);
    plane8.setPoints(x13, x14, x15, x16);
    plane9.setPoints(x9, x10, x14, x13);
    plane10.setPoints(x12, x11, x15, x16);

    Plane planes[NUMBER_PLANES] = {
            plane1, plane2, plane3, plane4, plane5, plane6, plane7, plane8, plane9, plane10
    };

    for (auto &plane : planes) {
        plane.rotateX(25);
        plane.rotateY(25);
        plane.rotateZ(1);
    }

    draw(renderer, planes, NUMBER_PLANES);

    int lastTime = 0, currentTime;
    int xMouse, previousMouseX = 0, yMouse, previousMouseY = 0;
    bool mousePressedLeft = false, mousePressedRight = false;

    bool check = true;
    while(check) {
        SDL_Event event{};
        currentTime = SDL_GetTicks();



        while(SDL_PollEvent(&event) && check) {
            SDL_GetMouseState(&xMouse,&yMouse);
            if (currentTime - lastTime > REACTION_TIME && (mousePressedLeft || mousePressedRight)) {
                lastTime = currentTime;
                int dx = previousMouseX - xMouse;
                int dy = previousMouseY - yMouse;
                if (mousePressedRight) {
                    if (dx > 0) {
                        for (auto &plane : planes) {
                            plane.rotateZ(-ROTATION_ANGLE);
                        }
                    } else if (dx < 0) {
                        for (auto &plane : planes) {
                            plane.rotateZ(ROTATION_ANGLE);
                        }
                    }
                } else {
                    if (dx > 0) {
                        for (auto &plane : planes) {
                            plane.rotateY(-ROTATION_ANGLE);
                        }
                    } else if (dx < 0) {
                        for (auto &plane : planes) {
                            plane.rotateY(ROTATION_ANGLE);
                        }
                    }

                    if (dy > 0) {
                        for (auto &plane : planes) {
                            plane.rotateX(-ROTATION_ANGLE);
                        }
                    } else if (dy < 0) {
                        for (auto &plane : planes) {
                            plane.rotateX(ROTATION_ANGLE);
                        }
                    }
                }


                draw(renderer, planes, NUMBER_PLANES);
            }
            previousMouseX = xMouse;
            previousMouseY = yMouse;
            switch(event.type) {
                case SDL_QUIT:
                    check = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        buffer->initBuffer(windowHeight, windowWidth);
                        // draw here
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (!mousePressedLeft && !mousePressedRight) {
                            mousePressedLeft = true;
                        }
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        if (!mousePressedLeft && !mousePressedRight) {
                            mousePressedRight = true;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mousePressedLeft = false;
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        mousePressedRight = false;
                    }
                    break;
                default:
                    continue;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void draw(SDL_Renderer *renderer, Plane *planes, int numberPlains) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    buffer->clearBuffer();
    for (int i = 0; i < numberPlains; i++) {
        Plane plane = planes[i];
        Point *points = plane.getPoints();

        buffer->clearTempBuffer();
        for (int j = 0; j < 4; j++) {
            drawLineInZBuffer(points[j], points[(j + 1) % 4], plane, false);
        }
        buffer->fillPlaneInTempBuffer(plane.getLowPoint(windowWidth, windowHeight), plane.getMaxPoint(windowWidth, windowHeight), plane);
        /* fill hole in plane*/
        if (plane.withHole) {
            points = plane.hole->getPoints();
            for (int j = 0; j < 4; j++) {
                drawLineInZBuffer(points[j], points[(j + 1) % 4], plane, true);
            }
        }
        buffer->fillHoleInTempBuffer(plane.getLowPoint(windowWidth, windowHeight), plane.getMaxPoint(windowWidth, windowHeight), plane);
        buffer->shiftToMainBuffer();
    }

    SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
    for (int i = 0; i < numberPlains; i++) {
        Plane plane = planes[i];
        Point *points = plane.getPoints();
        for (int j = 0; j < 4; j++) {
           drawLine(renderer, points[j], points[(j + 1) % 4], plane);
        }
    }
    SDL_RenderPresent(renderer);

}

void drawLineInZBuffer(Point startPoint, Point endPoint, Plane &plane, bool hole) {
    int dx = abs(int(round(endPoint.x - startPoint.x)));
    int dy = abs(int(round(endPoint.y - startPoint.y)));
    int sx = endPoint.x >= startPoint.x ? 1 : -1;
    int sy = endPoint.y >= startPoint.y ? 1 : -1;

    double z = startPoint.z, dz;
    if (dy <= dx) {
        dz = (endPoint.z - startPoint.z) / dx;
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        double x = startPoint.x + sx, y = startPoint.y;
        for (int i = 1; i <= dx; i++) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else {
                d += d1;
            }
            z += dz;
            if (!hole) {
                buffer->setTempBuffer(int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), z);
            } else {
                buffer->setTempBuffer(int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), 15001); // 15001 hole line value
            }
            x += sx;
        }
    } else {
        dz = (endPoint.z - startPoint.z) / dy;
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        double x = startPoint.x, y = startPoint.y + sy;
        for (int i = 1; i <= dy; i++) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else {
                d += d1;
            }
            z += dz;
            if (!hole) {
                buffer->setTempBuffer(int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), z);
            } else {
                buffer->setTempBuffer(int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), 15001);
            }
            y += sy;
        }
    }
}

void drawPoint(SDL_Renderer *renderer, int x, int y, bool &dashLine, int &dashStep, double depth) {
    double temp = buffer->getValue(x, y);
    bool check = temp < depth  && abs(static_cast<int>(round(temp - depth))) > 2;
    dashLine = check;
    if (dashLine) {
        if (DRAW_INVISIBLE) {
            if (dashStep % DASH_STEP == 0 || dashStep % DASH_STEP == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
            dashStep++;
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
        SDL_RenderDrawPoint(renderer, x , y);
    }
}

void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, Plane &plane) {
    bool dashLine = false;
    int dashStep = 0;
    int dx = abs(int(round(endPoint.x - startPoint.x)));
    int dy = abs(int(round(endPoint.y - startPoint.y)));
    int sx = endPoint.x >= startPoint.x ? 1 : -1;
    int sy = endPoint.y >= startPoint.y ? 1 : -1;

    double z = startPoint.z, dz;
    if (dy <= dx) {
        dz = (endPoint.z - startPoint.z) / dx;
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        double x = startPoint.x + sx, y = startPoint.y;
        for (int i = 1; i <= dx; i++) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else {
                d += d1;
            }
            z += dz;
            drawPoint(renderer, int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), dashLine, dashStep, z);
            x += sx;
        }
    } else {
        dz = (endPoint.z - startPoint.z) / dy;
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        double x = startPoint.x, y = startPoint.y + sy;
        for (int i = 1; i <= dy; i++) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else {
                d += d1;
            }
            z += dz;
            drawPoint(renderer, int(round(x + windowWidth / 2)), int(round(y + windowHeight / 2)), dashLine, dashStep, z);
            y += sy;
        }
    }
}
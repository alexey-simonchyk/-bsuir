#include <SDL2/SDL.h>
#include "src/Point.h"
#include "src/Rectangle.h"
#include "src/ZBuffer.h"
#include "src/Animation.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

#define ROTATE_ANGLE 2
#define DASH_STEP 5

void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, int depth);
void drawRectangle(SDL_Renderer *renderer, Rectangle &rectangle);
void update(SDL_Renderer *renderer, Rectangle &firstRectangle, Rectangle &secondRectangle);
ZBuffer zBuffer;

int windowWidth = DEFAULT_WINDOW_WIDTH;
int windowHeight = DEFAULT_WINDOW_HEIGHT;

int main(int argc, char* argv[]) {

    bool mousePressed = false;
    Animation animation;
    int xMouse, yMouse, xMousePrev = 0, yMousePrev = 0;
    Rectangle *currentRectangle = nullptr;
    SDL_Window *window;
    SDL_Renderer *renderer;



    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "Epicycloid",
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

    Point points[4] = {
        {.x = 50, .y = 50},
        {.x = 150, .y = 50},
        {.x = 150, .y = 250},
        {.x = 50, .y = 250}
    };

    Point points_1[4] = {
            {.x = 400, .y = 300},
            {.x = 500, .y = 300},
            {.x = 500, .y = 500},
            {.x = 400, .y = 500}
    };

    zBuffer.initBuffer(DEFAULT_WINDOW_HEIGHT + 1, DEFAULT_WINDOW_WIDTH + 1);

    Rectangle rectangle;
    rectangle.setPoints(points);
    rectangle.setDepth(2);

    Rectangle rectangle2;
    rectangle2.setPoints(points_1);
    rectangle2.setDepth(3);

    Rectangle rectangles[2] = {rectangle, rectangle2};
    animation.init(rectangles);

    update(renderer, rectangles[0], rectangles[1]);

    bool check = true;
    int lastTime = 0, currentTime;

    while(check) {
        SDL_Event event{};
        currentTime = SDL_GetTicks();

        if (animation.isPlayAnimation()) {
            if (currentTime - lastTime > 50) {
                animation.animate(rectangles);
                update(renderer, rectangles[0], rectangles[1]);
                lastTime = currentTime;
            }
        }

        if (mousePressed) {
            SDL_GetMouseState(&xMouse,&yMouse);

            int dx = xMouse - xMousePrev;
            int dy = yMouse - yMousePrev;

            xMousePrev = xMouse;
            yMousePrev = yMouse;

            if (currentTime - lastTime > 50) {
                currentRectangle->rotate(ROTATE_ANGLE);
                lastTime = currentTime;
            }

            currentRectangle->move(dx, dy);
            update(renderer, rectangles[0], rectangles[1]);
        }


        while(SDL_PollEvent(&event) && check) {
            switch(event.type) {
                case SDL_QUIT:
                    check = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        zBuffer.initBuffer(windowHeight + 1, windowWidth + 1);
                        update(renderer, rectangles[0], rectangles[1]);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (mousePressed) {
                            mousePressed = false;
                        } else {
                            if (!animation.isPlayAnimation()) {
                                SDL_GetMouseState(&xMouse,&yMouse);
                                int temp = zBuffer.getValue(xMouse, yMouse);
                                if (temp > 1) {
                                    for (auto &tempRect : rectangles) {
                                        if (temp == tempRect.getDepth()) {
                                            mousePressed = true;
                                            xMousePrev = xMouse;
                                            yMousePrev = yMouse;
                                            currentRectangle = &tempRect;
                                        }
                                    }
                                }
                            }

                        }

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


void drawPoint(SDL_Renderer *renderer, int x, int y, bool &dashLine, int &dashStep, int depth) {
    if (x < 0 || y < 0 || x >= windowWidth || y >= windowHeight) {
        return;
    }
    dashLine = zBuffer.getValue(x, y) > 0;
    if (dashLine) {
        if (dashStep % DASH_STEP == 0 || dashStep % DASH_STEP == 1) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
        dashStep++;
    } else {
        SDL_RenderDrawPoint(renderer, x, y);
        zBuffer.setValue(x, y, depth);
    }
}


void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, int depth) {
    bool dashLine = false;
    int dashStep = 0;
    int dx = abs(endPoint.x - startPoint.x);
    int dy = abs(endPoint.y - startPoint.y);
    int sx = endPoint.x >= startPoint.x ? 1 : -1;
    int sy = endPoint.y >= startPoint.y ? 1 : -1;

    if (dy <= dx) {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        SDL_RenderDrawPoint(renderer, startPoint.x, startPoint.y);
        for (int x = startPoint.x + sx, y = startPoint.y, i = 1; i <= dx; i++, x += sx) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else {
                d += d1;
            }
            drawPoint(renderer, x, y, dashLine, dashStep, depth);
        }
    } else {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        SDL_RenderDrawPoint(renderer, startPoint.x, startPoint.y);
        for (int x = startPoint.x, y = startPoint.y + sy, i = 1; i <= dy; i++, y += sy) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else {
                d += d1;
            }
            drawPoint(renderer, x, y, dashLine, dashStep, depth);
        }
    }
}

void drawRectangle(SDL_Renderer *renderer, Rectangle &rectangle) {

    for (int i = 0; i < 4; i++) {
        drawLine(renderer, rectangle.getPoints()[i], rectangle.getPoints()[(i + 1) % 4], rectangle.getDepth());
    }
    Point min = rectangle.getLowPoint();
    Point max = rectangle.getMaxPoint();
    zBuffer.fillRectInBuffer(min.x, min.y, max.x, max.y, rectangle.getDepth());

}

void update(SDL_Renderer *renderer, Rectangle &firstRectangle, Rectangle &secondRectangle) {
    zBuffer.clearBuffer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (firstRectangle.getDepth() > secondRectangle.getDepth()) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawRectangle(renderer, secondRectangle);

        SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
        drawRectangle(renderer, firstRectangle);
    } else {
        SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
        drawRectangle(renderer, firstRectangle);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawRectangle(renderer, secondRectangle);

    }



    SDL_RenderPresent(renderer);
}
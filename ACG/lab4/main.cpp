#include <SDL2/SDL.h>
#include "src/point/Point.h"
#include "src/plane/Plane.h"
#include "src/buffer/Buffer.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

int windowWidth = DEFAULT_WINDOW_WIDTH;
int windowHeight = DEFAULT_WINDOW_HEIGHT;
#define DASH_STEP 5

Buffer *buffer = nullptr;

void drawLineInZBuffer(Point startPoint, Point endPoint, Plane &plane);
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
    Point x1 = {.x = 100, .y = 100, .z = 100};
    Point x2 = {.x = 150, .y = 50, .z = 200};
    Point x3 = {.x = 250, .y = 50, .z = 200};
    Point x4 = {.x = 200, .y = 100, .z = 100};
    Point x5 = {.x = 100, .y = 200, .z = 100};
    Point x6 = {.x = 150, .y = 150, .z = 200};
    Point x7 = {.x = 250, .y = 150, .z = 200};
    Point x8 = {.x = 200, .y = 200, .z = 100};
    Plane plane1;
    Plane plane2;
    Plane plane3;
    Plane plane4;
    Plane plane5;
    Plane plane6;

    plane1.setPoints(x1, x2, x3, x4);
    plane2.setPoints(x5, x6, x7, x8);
    plane3.setPoints(x1, x4, x8, x5);
    plane4.setPoints(x1, x2, x6, x5);
    plane5.setPoints(x2, x3, x7, x6);
    plane6.setPoints(x3, x4, x8, x7);

    Plane planes[6] = {
            plane1,  plane2, plane3, plane4, plane5, plane6
    };

    draw(renderer, planes, 6);

    bool check = true;
    while(check) {
        SDL_Event event{};

        while(SDL_PollEvent(&event) && check) {
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
                        // mouse pressed left
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
    for (int i = 0; i < numberPlains; i++) {
        Plane plane = planes[i];
        Point *points = plane.getPoints();

        buffer->clearTempBuffer();
        for (int j = 0; j < 4; j++) {
            drawLineInZBuffer(points[j], points[(j + 1) % 4], plane);
        }
        buffer->fillPlaneInTempBuffer(plane.getLowPoint(), plane.getMaxPoint(), plane);
        buffer->shiftToMainBuffer();


    }

    for (int i = 0; i < numberPlains; i++) {
        Plane plane = planes[i];
        Point *points = plane.getPoints();
        for (int j = 0; j < 4; j++) {
            drawLine(renderer, points[j], points[(j + 1) % 4], plane);
        }
    }
    SDL_RenderPresent(renderer);

}

void drawLineInZBuffer(Point startPoint, Point endPoint, Plane &plane) {
    int dx = abs(endPoint.x - startPoint.x);
    int dy = abs(endPoint.y - startPoint.y);
    int sx = endPoint.x >= startPoint.x ? 1 : -1;
    int sy = endPoint.y >= startPoint.y ? 1 : -1;

    if (dy <= dx) {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        for (int x = startPoint.x + sx, y = startPoint.y, i = 1; i <= dx; i++, x += sx) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else {
                d += d1;
            }
            buffer->setTempBuffer(x, y, plane.getZValue(x, y));
        }
    } else {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        for (int x = startPoint.x, y = startPoint.y + sy, i = 1; i <= dy; i++, y += sy) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else {
                d += d1;
            }
            buffer->setTempBuffer(x, y, plane.getZValue(x, y));
        }
    }
}

void drawPoint(SDL_Renderer *renderer, int x, int y, bool &dashLine, int &dashStep, float depth) {
    if (x < 0 || y < 0 || x >= windowWidth || y >= windowHeight) {
        return;
    }
    float temp = buffer->getValue(x, y);
    dashLine = temp < depth;
    if (dashLine) {
        if (dashStep % DASH_STEP == 0 || dashStep % DASH_STEP == 1) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
        dashStep++;
    } else {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, Plane &plane) {
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
            drawPoint(renderer, x, y, dashLine, dashStep, plane.getZValue(x, y));
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
            drawPoint(renderer, x, y, dashLine, dashStep, plane.getZValue(x, y));
        }
    }
}
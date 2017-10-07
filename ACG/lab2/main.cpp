#include <cstdio>
#include <cmath>
#include "SDL.h"
#include <array>

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define NUMBER_ANGLES 4
#define ROTATION_ANGLE 0.1


struct Point {
    int x;
    int y;
};
void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint);
void drawFigure(SDL_Renderer *renderer, std::array<Point, NUMBER_ANGLES> points, double angle);
std::array<Point, NUMBER_ANGLES> getPoints(int windowWidth);

int main(int argc, char* argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "Lab 2",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight,
            SDL_WINDOW_RESIZABLE
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);


    drawFigure(renderer, getPoints(windowWidth), ROTATION_ANGLE);
    SDL_RenderPresent(renderer);

    bool check = true;
    while(check) {
        SDL_Event event;

        while(SDL_PollEvent(&event) && check) {
            switch(event.type) {
                case SDL_QUIT:
                    check = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                        SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
                        drawFigure(renderer, getPoints(windowWidth), ROTATION_ANGLE);
                        SDL_RenderPresent(renderer);
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

void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint) {
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
            SDL_RenderDrawPoint(renderer, x, y);
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
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void drawFigure(SDL_Renderer *renderer, std::array<Point, NUMBER_ANGLES> points, double angle) {
    const int steps = 5; // number steps here!!!
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < points.size(); j++) {
            drawLine(renderer, points[j], points[(j + 1) % points.size()]);
        }

        for (int j = 0; j < points.size(); j++) {
            points[j].x = int ((1 - angle) * points[j].x + angle * points[(j + 1) % points.size()].x);
            points[j].y = int((1 - angle) * points[j].y + angle * points[(j + 1) % points.size()].y);
        }
    }
}

std::array<Point, NUMBER_ANGLES> getPoints(int windowWidth) {
    int temp = ( windowWidth / 2) / 6;
    std::array<Point, NUMBER_ANGLES> points;
    Point point ={.x = temp * 1, .y = temp * 1};
    points[0] = point;
    point ={.x = temp * 3, .y = temp * 1};
    points[1] = point;
    point ={.x = temp * 3, .y = temp * 3};
    points[2] = point;
    point ={.x = temp * 1, .y = temp * 3};
    points[3] = point;
    return points;
}

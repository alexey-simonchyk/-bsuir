#include <SDL2/SDL.h>
#include "src/Point.h"
#include "src/Rectangle.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define DASH_STEP 5

void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, bool dashLine);
void drawRectangle(SDL_Renderer *renderer, Rectangle &rectangle);

int main(int argc, char* argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

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

    Point points[4];
    points[0] = {.x = 160, .y = 110};
    points[1] = {.x = 350, .y = 110};
    points[2] = {.x = 350, .y = 300};
    points[3] = {.x = 160, .y = 300};

    Rectangle rectangle;
    rectangle.setPoints(points);
    drawRectangle(renderer, rectangle);
    SDL_RenderPresent(renderer);

    bool check = true;
    int frame = 0;
    while(check) {
        SDL_Event event{};

        if (frame >= 90000) {
            frame = 0;
            rectangle.rotate(4);
            drawRectangle(renderer, rectangle);
            SDL_RenderPresent(renderer);
        } else {
            frame++;
        }
        while(SDL_PollEvent(&event) && check) {
            switch(event.type) {
                case SDL_QUIT:
                    check = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

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


void drawLine(SDL_Renderer *renderer, Point startPoint, Point endPoint, bool dashLine) {
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
            if (dashLine) {
                if (dashStep % DASH_STEP == 0 || dashStep % DASH_STEP == 1) {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
                dashStep++;
            } else {
                SDL_RenderDrawPoint(renderer, x, y);
            }
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
            if (dashLine) {
                if (dashStep % DASH_STEP == 0 || dashStep % DASH_STEP == 1) {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
                dashStep++;
            } else {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void drawRectangle(SDL_Renderer *renderer, Rectangle &rectangle) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);
    for (int i = 0; i < 4; i++) {
        drawLine(renderer, rectangle.getPoints()[i], rectangle.getPoints()[(i + 1) % 4], false);
    }
}
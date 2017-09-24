#include <cstdio>
#include <cmath>
#include "SDL.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

struct Point {
    int x;
    int y;
};

void drawEpicycloid(SDL_Renderer *renderer, int windowWidth, int windowHeight);
Point epicycloid(double angle, int first_radius, int second_radius);
void drawAxis(SDL_Renderer *renderer, int windowWidth, int windowHeight);


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

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    drawAxis(renderer, windowWidth, windowHeight);
    drawEpicycloid(renderer, windowWidth, windowHeight);
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
                        drawAxis(renderer, windowWidth, windowHeight);
                        drawEpicycloid(renderer, windowWidth, windowHeight);
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

void drawEpicycloid(SDL_Renderer *renderer, int windowWidth, int windowHeight) {
    int first_radius = 3;
    int second_radius = 1;

    int temp = windowHeight < windowWidth ? windowHeight / 2: windowWidth / 2;
    temp /= 2;
    temp = temp / (first_radius + second_radius);

    int number_steps = 100000;
    double angle = 0;
    double delta = 0.5;

    SDL_SetRenderDrawColor(renderer, 51, 191, 16, 255);

    for (int i = 0; i < number_steps; i++) {
        Point point = epicycloid(angle, temp * first_radius, temp * second_radius);
        angle += delta;
        SDL_RenderDrawPoint(renderer, point.x + windowWidth / 2, point.y + windowHeight / 2);
    }
}

void drawAxis(SDL_Renderer *renderer, int windowWidth, int windowHeight) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, windowWidth / 2, 0, windowWidth / 2, windowHeight);
    SDL_RenderDrawLine(renderer, 0, windowHeight / 2, windowWidth, windowHeight / 2);
}

Point epicycloid(double angle, int first_radius, int second_radius) {
    double x_coordinate;
    double y_coordinate;
    x_coordinate = (first_radius + second_radius) * cos(angle) - second_radius * cos((first_radius + second_radius) * angle / second_radius);
    y_coordinate = (first_radius + second_radius) * sin(angle) - second_radius * sin((first_radius + second_radius) * angle / second_radius);
    Point point = {.x = (int)x_coordinate, .y = (int)y_coordinate};
    return point;
}
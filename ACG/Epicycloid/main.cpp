#include <cstdio>
#include <cmath>
#include "SDL.h"

struct Point {
    double x;
    double y;
};

int main(int argc, char* argv[]) {

    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "Epicycloid",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Delay(3000);

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

Point epicycloid(double angle, int radius_first, int radius_second) {
    double x_coordinate;
    double y_coordinate;
    x_coordinate = (radius_first + radius_second) * cos(angle) - radius_second * cos((radius_first + radius_second) * angle / radius_second);
    y_coordinate = (radius_first + radius_second) * sin(angle) - radius_second * sin((radius_first + radius_second) * angle / radius_second);
    Point point = {.x = x_coordinate, .y = y_coordinate};
    return point;
}
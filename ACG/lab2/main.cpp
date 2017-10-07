#include <cstdio>
#include <cmath>
#include "SDL.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480


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
    // draw here
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
                        // draw here
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
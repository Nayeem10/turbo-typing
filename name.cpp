#include <SDL2/SDL.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    SDL_Window* win = SDL_CreateWindow("SDL Graph Example", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Event loop flag
    int quit = 0;

    // Event structure
    SDL_Event e;

    // Example points to plot (these would typically come from your data)
    SDL_Point points[] = {
        {50, 400}, {100, 300}, {150, 200}, {200, 100}, {250, 150},
        {300, 250}, {350, 350}, {400, 300}, {450, 200}, {500, 100}
    };
    int pointCount = sizeof(points) / sizeof(points[0]);
    processPoints(points, pointCount, {50,400}, 500, 400);

    // Main event loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer with a white background
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        // Draw the graph
        drawGraph(ren, points, pointCount, {255, 0, 0}, {50, 400}, 500, 400);

        // Present the renderer
        SDL_RenderPresent(ren);
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

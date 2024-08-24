/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int screen_width  = 640;
const int screen_height = 480;

int main(int argc, char* args[]) {
    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screen_surface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        } else {
            // Get window surface
            screen_surface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screen_surface, NULL,
                         SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

#include <SDL2/SDL.h>
#include "../headers/constants.h"
#include "../headers/windowManager.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Window* get_window() {return window;};
SDL_Renderer* get_renderer() {return renderer;};


void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL\n");
        return FALSE;
    }

    SDL_Window* window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if(!window)
    {
        fprintf(stderr, "Error creating SDL Window. \n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer)
    {
        fprintf(stderr, "Error creating SDL Rendrer");
        return FALSE;
    }
    
    return TRUE;
}


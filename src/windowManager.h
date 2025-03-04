#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window* get_window();
SDL_Renderer* get_renderer();

void destroy_window();
int initialize_window(void);

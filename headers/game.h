#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

void set_game_is_running(int _game_is_running);
int get_game_is_running();
int get_last_frame_time();

void setup();
void process_input();
void update();
void render();
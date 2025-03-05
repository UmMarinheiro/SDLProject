#include <SDL2/SDL_config_unix.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include "../include/constants.h"
#include "../include/game.h"
#include "../include/snake.h"

#define speed 100
extern int game_is_running;
extern SDL_Renderer* renderer;

int last_frame_time = 0;

char w = 0,a = 0,s = 0,d = 0;

snake_part snake[] = 
{
    {100,36, 10},
    {100,34, 10},
    {100,32, 10},
    {100,30, 10},
    {100,28, 10},
    {100,26, 10},
    {100,24, 10},
    {100,22, 10},
    {100,20, 10},
    {100,18, 10},
    {100,16, 10},
    {100,14, 10},
    {100,12, 10},
    {100,10, 10}
};
int snake_size = sizeof(snake)/sizeof(snake_part);

void setup()
{
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) game_is_running = FALSE;
            if (event.key.keysym.sym == SDLK_w) w = TRUE;
            if (event.key.keysym.sym == SDLK_a) a = TRUE;
            if (event.key.keysym.sym == SDLK_s) s = TRUE;
            if (event.key.keysym.sym == SDLK_d) d = TRUE;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w) w = FALSE;
            if (event.key.keysym.sym == SDLK_a) a = FALSE;
            if (event.key.keysym.sym == SDLK_s) s = FALSE;
            if (event.key.keysym.sym == SDLK_d) d = FALSE;
    }
}

void update()
{
    /*--Limit framerate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME) SDL_Delay(time_to_wait);*/

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time  = SDL_GetTicks();

    move_snake(snake, snake_size, 0, 
        snake[0].x + speed * (d - a) * delta_time,
        snake[0].y + speed * (s - w) * delta_time);
}

void render()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < snake_size; i++)
    {
        SDL_Rect part_rect = 
        {
            (int)snake[i].x,
            (int)snake[i].y,
            2*(int)snake[i].radius,
            2*(int)snake[i].radius
        };

        SDL_SetRenderDrawColor(renderer, 255, (int)((i+1)*(255/(float)snake_size)), 0, 255);
        SDL_RenderFillRect(renderer, &part_rect);  
    }

    SDL_RenderPresent(renderer);
}

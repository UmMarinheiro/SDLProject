#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include "../include/constants.h"
#include "../include/game.h"
#include "../include/snake.h"

#define SPEED 200

#define SNAKE_SIZE 20
#define SNAKE_RADIUS 5

extern int game_is_running;
extern SDL_Renderer* renderer;

int last_frame_time = 0;

char w = 0,a = 0,s = 0,d = 0;

snake_part snake[SNAKE_SIZE];

void setup()
{
    for(int i = 0; i < SNAKE_SIZE; i++)
    {
        snake[i] = (snake_part){100, 2*SNAKE_RADIUS*i, SNAKE_RADIUS};
    }
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

    move_snake(snake, SNAKE_SIZE, 0, 
        snake[0].x + SPEED * (d - a) * delta_time,
        snake[0].y + SPEED * (s - w) * delta_time);
}

void render()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < SNAKE_SIZE; i++)
    {
        SDL_Rect part_rect = 
        {
            (int)snake[i].x-(int)snake[i].radius,
            (int)snake[i].y-(int)snake[i].radius,
            2*(int)snake[i].radius,
            2*(int)snake[i].radius
        };

        SDL_SetRenderDrawColor(renderer,
         255,
         (int)((i+1)*(255/(float)SNAKE_SIZE)),
         255-(int)((i+1)*(255/(float)SNAKE_SIZE)), 255);
        SDL_RenderFillRect(renderer, &part_rect);  
    }

    SDL_RenderPresent(renderer);
}

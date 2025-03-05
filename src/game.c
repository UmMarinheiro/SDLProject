#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include "../include/constants.h"
#include "../include/game.h"

extern int game_is_running;
extern SDL_Renderer* renderer;

int last_frame_time = 0;

struct ball 
{
    float x;
    float y;
    float width;
    float height;
} ball;

char w = 0,a = 0,s = 0,d = 0;

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
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

    ball.y += 50 * (s - w) * delta_time; 
    ball.x += 50 * (d - a) * delta_time; 
}

void render()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_Rect ball_rect = 
    {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

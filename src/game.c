#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include "../headers/constants.h"
#include "../headers/game.h"
#include "../headers/windowManager.h"

int game_is_running = FALSE;
int last_frame_time = 0;

void set_game_is_running(int _game_is_running) {game_is_running = _game_is_running;};
int get_game_is_running() {return game_is_running;};
int get_last_frame_time() {return last_frame_time;};

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
    /*--Limitar a framerate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME) SDL_Delay(time_to_wait);*/

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time  = SDL_GetTicks();

    ball.y += 50 * (s - w) * delta_time; 
    ball.x += 50 * (d - a) * delta_time; 
}

void render()
{
    SDL_SetRenderDrawColor(get_renderer(),0,0,0,255);
    SDL_RenderClear(get_renderer());

    SDL_Rect ball_rect = 
    {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };

    SDL_SetRenderDrawColor(get_renderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(get_renderer(), &ball_rect);

    SDL_RenderPresent(get_renderer());
}

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include "../include/constants.h"
#include "../include/game.h"
#include "../include/snake.h"

#define SPEED 200

#define SNAKE_SIZE 20
#define SNAKE_RADIUS 10

extern int game_is_running;

int last_frame_time = 0;

char w = 0,a = 0,s = 0,d = 0;

snake_part snake[SNAKE_SIZE];

void print_snake_directions()
{
    for(int i = 0; i < SNAKE_SIZE; i++)
    {
        printf("%d: (%f,%f)\n", i, snake[i].forwad_x, snake[i].forwad_y);
    }
}
void render_snake_directions(SDL_Renderer* renderer)
{
    for (int i = 0; i < SNAKE_SIZE; i++){
        
        SDL_SetRenderDrawColor(renderer,
         255*(i%2),
         255*((i+1)%2),
         0, 255);
        
        
        SDL_RenderDrawLine(renderer, (int)snake[i].x, (int)snake[i].y, 
        (int)(snake[i].x + 2*snake[i].radius*snake[i].forwad_x), ((int)snake[i].y + 2*snake[i].radius*snake[i].forwad_y)); 
    }
}

void setup()
{
    for(int i = 0; i < SNAKE_SIZE; i++)
    {
        snake[i] = (snake_part){100, 2*SNAKE_RADIUS*i, 0, -1, SNAKE_RADIUS};
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
    //Limit framerate
    //'int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    //'if(time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME) SDL_Delay(time_to_wait);

    //print_snake_directions();

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time  = SDL_GetTicks();

    float walk_dir_x = (d - a);
    float walk_dir_y = (s - w);

    char stoped = !(walk_dir_x || walk_dir_y);

    move_snake(snake, SNAKE_SIZE, 
        snake[0].x + SPEED * delta_time * walk_dir_x,
        snake[0].y + SPEED * delta_time * walk_dir_y,
        stoped?snake[0].forwad_x:walk_dir_x,
        stoped?snake[0].forwad_y:walk_dir_y
    );
}

void render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    //render_snake_directions(renderer);

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
         255*(i%2),
         (int)((i+1)*(255/(float)SNAKE_SIZE)),
         255-(int)((i+1)*(255/(float)SNAKE_SIZE)), 255);
        SDL_RenderFillRect(renderer, &part_rect);  
    }

    SDL_RenderPresent(renderer);
}

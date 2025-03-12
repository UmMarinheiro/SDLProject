#include "../include/snake.h"
#include <math.h>
#include <stdio.h>

extern int game_is_running;

void stick_part_to(const snake_part *fix, snake_part *join)
{
    float vector_x = join -> x - fix -> x;
    float vector_y = join -> y - fix -> y;

    int desired_distance = join -> radius + fix -> radius;
    float vector_size = sqrt(vector_x*vector_x + vector_y*vector_y);

    vector_x /= vector_size;
    vector_y /= vector_size;

    float spine_cos = (-vector_x)*(fix->forwad_x) + (-vector_y)*(fix->forwad_y);
    
    if(spine_cos < -0.5f) 
    {
        printf("(%f,%f) (%f,%f)\n",-vector_x,-vector_y,fix->forwad_x,fix->forwad_y);
        printf("Quebrei a coluna com um cosseno de %f :(\n",spine_cos);
        game_is_running = 0;
    }
    join -> forwad_x = -vector_x;
    join -> forwad_y = -vector_y;

    join -> x = fix -> x + desired_distance*vector_x;
    join -> y = fix -> y + desired_distance*vector_y;
}
void move_snake(snake_part snake[], int snake_size, int index, float x, float y, float forwad_x, float forwad_y)
{
    snake[index].x = x;
    snake[index].y = y;

    snake[index].forwad_x = forwad_x;
    snake[index].forwad_y = forwad_y;

    for(int i = index; i < snake_size-1; i++) stick_part_to(&snake[i],&snake[i+1]);
    for(int i = index; i > 0; i--) stick_part_to(&snake[i],&snake[i-1]);
}

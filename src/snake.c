#include "../include/snake.h"
#include <math.h>
#include <stdio.h>

void update_snake_part_left(snake_part snake[], int snake_size, int index, float x, float y)
{   
    snake[index].x = x;
    snake[index].y = y;

    if(index - 1 < 0) return;
    int next_index = index - 1;

    float vector_x = snake[next_index].x - x;
    float vector_y = snake[next_index].y - y;

    float vector_size = sqrt(vector_x*vector_x + vector_y*vector_y);
    printf("%f\n",vector_size);
    int desired_distance = snake[index].radius + snake[next_index].radius;

    vector_x *= desired_distance/vector_size;
    vector_y *= desired_distance/vector_size;

    update_snake_part_left(snake, snake_size, next_index, x + vector_x, y + vector_y);
}

void update_snake_part_right(snake_part snake[], int snake_size, int index, float x, float y)
{
    snake[index].x = x;
    snake[index].y = y;

    if(index + 1 >= snake_size) return;
    int next_index = index + 1;

    float vector_x = snake[next_index].x - x;
    float vector_y = snake[next_index].y - y;

    float vector_size = sqrt(vector_x*vector_x + vector_y*vector_y);
    int desired_distance = snake[index].radius + snake[next_index].radius;

    vector_x *= desired_distance/vector_size;
    vector_y *= desired_distance/vector_size;

    update_snake_part_right(snake, snake_size, next_index, x + vector_x, y + vector_y);
}

void move_snake(snake_part snake[], int snake_size, int index, float x, float y)
{
    snake[index].x = x;
    snake[index].y = y;

    update_snake_part_left(snake,snake_size,index,x,y);
    update_snake_part_right(snake,snake_size,index,x,y);
}

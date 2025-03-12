#include "../include/snake.h"
#include <math.h>

void stick_part_to(const snake_part *fix, snake_part *join)
{
    float vector_x = join -> x - fix -> x;
    float vector_y = join -> y - fix -> y;

    int desired_distance = join -> radius + fix -> radius;
    float vector_size = sqrt(vector_x*vector_x + vector_y*vector_y);

    vector_x *= desired_distance/vector_size;
    vector_y *= desired_distance/vector_size;

    join -> x = fix -> x + vector_x;
    join -> y = fix -> y + vector_y;
}
void move_snake(snake_part snake[], int snake_size, int index, float x, float y)
{
    snake[index].x = x;
    snake[index].y = y;

    for(int i = index; i < snake_size-1; i++) stick_part_to(&snake[i],&snake[i+1]);
    for(int i = index; i > 1; i--) stick_part_to(&snake[i],&snake[i-1]);
}

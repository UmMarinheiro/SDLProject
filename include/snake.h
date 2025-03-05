#pragma once

typedef struct snake_part_
{
    float x,y;
    int radius;
} snake_part;

void move_snake(snake_part snake[], int snake_size, int index, float x, float y);
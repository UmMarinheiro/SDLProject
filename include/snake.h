#pragma once

typedef struct snake_part_
{
    float x,y;
    float forwad_x,forwad_y;
    int radius;
} snake_part;

void move_snake(snake_part snake[], int snake_size, 
    float _x, float _y, float _forwad_x, float _forwad_y);
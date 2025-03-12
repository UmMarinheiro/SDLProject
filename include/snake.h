#pragma once

typedef struct snake_part_
{
    float x,y;
    float forwad_x,forwad_y;
    int radius;
} snake_part;

void move_snake(snake_part snake[], int snake_size, int index, float x, float y, float forwad_x, float forwad_y);
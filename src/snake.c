#include "../include/snake.h"
#include <math.h>

#define M_PI 3.14159265358979323846
#define MAX_ANGLE M_PI/2.f

extern int game_is_running;

void stick_part_to(const snake_part *fix, snake_part *to_join)
{
    float vector_x = (fix -> x) - (to_join -> x);
    float vector_y = (fix -> y) - (to_join -> y);
    
    int desired_distance = (to_join -> radius) + (fix -> radius);
    float vector_size = sqrt(vector_x*vector_x + vector_y*vector_y);

    vector_x /= vector_size;
    vector_y /= vector_size;

    float spine_cos = (vector_x)*(fix->forwad_x) + (vector_y)*(fix->forwad_y);
    
    if(spine_cos < cos(MAX_ANGLE)) 
    {
        float cross = (fix->forwad_x)*(vector_y) - (vector_x)*(fix->forwad_y);

        if(cross > 0) 
        {
            vector_x = cos(MAX_ANGLE)*(fix->forwad_x) - sin(MAX_ANGLE)*(fix->forwad_y);
            vector_y = sin(MAX_ANGLE)*(fix->forwad_x) + cos(MAX_ANGLE)*(fix->forwad_y);

            //printf("Estou quebrado no sentido horário...\n");
        }
        else if(cross < 0)
        {
            vector_x = cos(-MAX_ANGLE)*(fix->forwad_x) - sin(-MAX_ANGLE)*(fix->forwad_y);
            vector_y = sin(-MAX_ANGLE)*(fix->forwad_x) + cos(-MAX_ANGLE)*(fix->forwad_y);
        }
    }
    to_join -> forwad_x = vector_x;
    to_join -> forwad_y = vector_y;

    to_join -> x = (fix -> x) - desired_distance * (vector_x);
    to_join -> y = (fix -> y) - desired_distance * (vector_y);
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

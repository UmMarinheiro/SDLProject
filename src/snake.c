#include "../include/snake.h"
#include <math.h>

#define M_PI 3.14159265358979323846
#define MAX_ANGLE M_PI/2.f

extern int game_is_running;

void stick_part_to(const snake_part *fix, snake_part *to_join)
{
    // join_dir = fix.pos - to_join.pos
    float join_dir_x = (fix -> x) - (to_join -> x);
    float join_dir_y = (fix -> y) - (to_join -> y);
    
    float join_dir_norm = sqrt(join_dir_x*join_dir_x + join_dir_y*join_dir_y);

    // join_dir = join_dir/||join_dir||
    join_dir_x /= join_dir_norm;
    join_dir_y /= join_dir_norm;
    // join_dir is now a versor

    // float join_dot_forwad = join_dir * fix.forward
    float join_dot_forwad = (join_dir_x)*(fix->forwad_x) + (join_dir_y)*(fix->forwad_y);
    
    if(join_dot_forwad < cos(MAX_ANGLE)) 
    {
        // float cross_z = (fix.forwad x vector).z
        float cross_z = (fix->forwad_x)*(join_dir_y) - (fix->forwad_y)*(join_dir_x);

        if(cross_z > 0) 
        {
            // to_join = rotate(fix.forward, MAX_ANGLE)
            join_dir_x = cos(MAX_ANGLE)*(fix->forwad_x) - sin(MAX_ANGLE)*(fix->forwad_y);
            join_dir_y = sin(MAX_ANGLE)*(fix->forwad_x) + cos(MAX_ANGLE)*(fix->forwad_y);
        }
        else if(cross_z < 0)
        {
            // to_join = rotate(fix.forward, -MAX_ANGLE)
            join_dir_x = cos(-MAX_ANGLE)*(fix->forwad_x) - sin(-MAX_ANGLE)*(fix->forwad_y);
            join_dir_y = sin(-MAX_ANGLE)*(fix->forwad_x) + cos(-MAX_ANGLE)*(fix->forwad_y);
        }
    }
    // to_join.forward = join_dir
    to_join -> forwad_x = join_dir_x;
    to_join -> forwad_y = join_dir_y;

    int desired_distance = (to_join -> radius) + (fix -> radius);

    // to_join.pos = fix.pos - join_dir
    to_join -> x = (fix -> x) - desired_distance * (join_dir_x);
    to_join -> y = (fix -> y) - desired_distance * (join_dir_y);
}
void move_snake(snake_part snake[], int snake_size, 
    float _x, float _y, float _forwad_x, float _forwad_y)
{
    // snake[0].pos = _pos
    snake[0].x = _x;
    snake[0].y = _y;

    // snake[0].forwad = _forwad
    snake[0].forwad_x = _forwad_x;
    snake[0].forwad_y = _forwad_y;

    for(int i = 0; i < snake_size-1; i++) 
        stick_part_to(&snake[i],&snake[i+1]);
}

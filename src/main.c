#include "../include/game.h"
#include "../include/windowManager.h"
#include "../include/constants.h"

int game_is_running = FALSE;

int main()
{
    game_is_running = initialize_window();

    setup();

    while (game_is_running)
    {
        process_input();
        update();
        render(renderer);
    }

    destroy_window();

    return 0;
}
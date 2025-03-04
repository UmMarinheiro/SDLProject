#include "./game.h"
#include "./windowManager.h"

int main()
{
    set_game_is_running(initialize_window());

    setup();

    while (get_game_is_running())
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
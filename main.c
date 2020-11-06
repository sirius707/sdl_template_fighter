#include "common.h"

#include "init.h"
#include "render.h"
#include "input.h"
#include "game.h"


//2d fighting game

void init();
void deinit();



int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    memset(players, 0, sizeof(CHARACTER)*NUMBER_OF_PLAYERS);
    players[0].x = 100;
    players[0].y = 200;

    prog.fps = 60;
    sdl_init();

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();

    while(1){

        s_input();
        s_game_p1_logic();
        s_game_physics();
        s_render_total();
        s_cap_framerate(&then, &remaining_time);
    }

    sdl_deinit();
	return 0;
}




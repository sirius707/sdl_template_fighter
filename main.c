#include "common.h"

#include "init.h"
#include "render.h"
#include "input.h"
#include "game.h"


//2d fighting game



int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    memset(players, 0, sizeof(CHARACTER)*NUMBER_OF_PLAYERS);
    players[0].x = 100;
    players[0].y = 20;
    players[0].width = 70;
    players[0].height = 100;
    players[0].control = PLAYER_ONE;
    players[0].enum_player_state = IDLE;

    init();

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    while(1){

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        s_input();

        s_game_player_logic();
        s_game_physics();
        prog.delta_time = (double)((NOW - LAST)/ (double)SDL_GetPerformanceFrequency() );//temporary until a fix is found
        s_render_total();

        s_cap_framerate(&then, &remaining_time, prog.fps);
        printf("%d state=%d vel_y = %f, pos_y = %f, dt = %f\r", players[0].grounded, players[0].enum_player_state, players[0].vel_y, players[0].y, prog.delta_time);
    }

    deinit();
	return 0;
}




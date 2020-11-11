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
    s_render_init();

    players[0].x = 100;
    players[0].y = 20;
    players[0].width = 100;
    players[0].height = 150;
    players[0].control = PLAYER_ONE;
    players[0].enum_player_state = IDLE;

    prog.fps = 60;
    prog.enum_game_state = RUNNING;
    prog.delta_time = 1.0f/prog.fps;//temporary, this shuold be true delta, updated every frame
    sdl_init();

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();
    while(1){

        s_input();

        s_game_player_logic();
        s_game_physics();

        s_render_total();
        prog.delta_time = s_cap_framerate(&then, &remaining_time, prog.fps)/10.0f;
        prog.delta_time = 1;//temporary until a fix is found
        printf("%d state=%d vel_y = %f, pos_y = %f, dt = %f\r", players[0].grounded, players[0].enum_player_state, players[0].vel_y, players[0].y, prog.delta_time);
    }

    sdl_deinit();
	return 0;
}




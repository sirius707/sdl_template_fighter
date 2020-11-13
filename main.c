#include "common.h"

#include "init.h"
#include "render.h"
#include "input.h"
#include "game.h"


//2d fighting game
// data oriented and data driven


int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    memset(entities, 0, sizeof(CHARACTER)*NUMBER_OF_PLAYERS);
    entities[0].x = 100;
    entities[0].y = 20;
    entities[0].width = 70;
    entities[0].height = 100;
    entities[0].control = PLAYER_ONE;
    entities[0].enum_player_state = FALL;
    entities[0].hp = 100;
    entities[0].can_attack = true;
    entities[0].flipped = false;

    entities[1].x = 250;
    entities[1].y = 20;
    entities[1].width = 70;
    entities[1].height = 100;
    entities[1].control = PLAYER_TWO;
    entities[1].enum_player_state = FALL;
    entities[1].hp = 50;
    entities[1].can_attack = true;
    entities[1].flipped = true;

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
        //printf("action a:%d, %d state=%d vel_y = %f, pos_y = %f, dt = %f\r", entities[0].action_control[ACTION_A], entities[0].grounded, entities[0].enum_player_state, entities[0].vel_y, entities[0].y, prog.delta_time);
        printf("%03d %03d\r", entities[0].hp, entities[1].hp);


    }

    deinit();
	return 0;
}




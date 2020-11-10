#include "game.h"

extern CHARACTER players[];

void s_game_physics(void)
{
    //players
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){

        //gravity
        players[i].vel_y += G * prog.delta_time;

        //i don't think we will need velocity in a fighting game
        //but what about jumping?
        players[i].dy += prog.delta_time * players[i].vel_y;
        players[i].dx += prog.delta_time * players[i].vel_x;

        //collision detection
        if(players[i].y + players[i].height + players[i].dy < GROUND_HEIGHT)players[i].y += players[i].dy;
        else{
            players[i].y = GROUND_HEIGHT - players[i].height;
            players[i].vel_y = 0;
        }

        players[i].x += players[i].dx;

    }
}

void s_game_p1_logic(void)
{
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = prog.keyboard[SDLK_RIGHT] + (-prog.keyboard[SDLK_LEFT]);
    players[0].dx = movement_direction * DEFAULT_XSPD;

    if(prog.keyboard[SDLK_UP]){
            puts("jump");
            players[0].vel_y += -100.0;
            prog.keyboard[SDLK_SPACE] = 0;
    }
}

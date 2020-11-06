#include "game.h"

extern CHARACTER players[];

void s_game_physics(void)
{
    //players
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        players[i].x += players[i].dx;
        players[i].y += players[i].dy;
    }
}

void s_game_p1_logic(void)
{
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = prog.keyboard[SDLK_RIGHT] + (-prog.keyboard[SDLK_LEFT]);
    players[0].dx = movement_direction;
}

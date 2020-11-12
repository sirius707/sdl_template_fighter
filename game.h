#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"//SDL, structs

#define GROUND_HEIGHT 400
#define G 5.5f
#define DEFAULT_WALKSPD 90.0f
#define DEFAULT_RUNSPD 5.0f
#define DEFAULT_JMPSPD 700.0f
#define DEFAULT_FALLSPD 20.7f

#define DEFAULT_MAX_JMPHEIGHT 290.f

void s_game_physics(void);

void s_game_p1_logic(void);//logic of player 1, test function, will remove later
void s_game_player_logic(void);
void s_game_player_fsm(CHARACTER *player);
void s_game_get_input(CHARACTER *player);
void s_game_shift_player_state(CHARACTER *player, PLAYER_STATE state);//change state and animation

#endif

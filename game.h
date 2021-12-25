 /******************************************************************************
 *
 * Module: Game Logic Routines
 *
 * Description: functions and data used in handling game logic
 *
 *******************************************************************************/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"//SDL
#include "structs.h"//structs


#define GROUND_HEIGHT 400
#define G 5.5f
#define DEFAULT_WALKSPD 120.0f
#define DEFAULT_RUNSPD 5.0f
#define DEFAULT_JMPSPD 700.0f
#define DEFAULT_FALLSPD 20.7f

#define PARRY_WINDOW 0.43

#define ON_HIT_DELAY 0.2 //time to wait if a player hits or gets hit, pause for a while
#define PARRY_DELAY 0.09
#define NORMAL_DELAY 0.09


#define DEFAULT_MAX_JMPHEIGHT 290.f

void s_game_player_logic(void);
void s_game_player_fsm(CHARACTER *player);
void s_game_get_input(void);
void s_game_get_player_input(CHARACTER *player);
void s_game_clear_action_keys();
void s_game_process_attacks(CHARACTER *player);
void s_game_shift_player_state(CHARACTER *player, PLAYER_STATE state);//change state and animation
void s_game_cache_state(CHARACTER *player);
void s_game_goto_cached_state(CHARACTER *player);

void s_game_player_jump(CHARACTER *player);//go to jump state
void s_game_player_attack(CHARACTER *player);// go to attack state
void s_game_player_crouch(CHARACTER *player);


ATK_INFO *s_game_get_current_attack(CHARACTER *player);

#endif

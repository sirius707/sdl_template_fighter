#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "common.h"//SDL, structs

#define GROUND_HEIGHT 400
#define G 5.5f
#define DEFAULT_WALKSPD 120.0f
#define DEFAULT_RUNSPD 5.0f
#define DEFAULT_JMPSPD 700.0f
#define DEFAULT_FALLSPD 20.7f

#define PARRY_WINDOW 0.2f

#define DEFAULT_MAX_JMPHEIGHT 290.f

void s_game_player_logic(void);
void s_game_player_fsm(CHARACTER *player);
void s_game_get_input(CHARACTER *player);
void s_game_animate(CHARACTER *player);
void s_game_process_attacks(CHARACTER *player);
void s_game_shift_player_state(CHARACTER *player, PLAYER_STATE state);//change state and animation
void s_game_cache_state(CHARACTER *player);
void s_game_goto_cached_state(CHARACTER *player);
void s_game_player_jump(CHARACTER *player);
ATK_INFO *s_game_get_current_attack(CHARACTER *player);

#endif

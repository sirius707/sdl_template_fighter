#include "common.h"//redundant? it still compiles if i don't include this

typedef struct PROGRAM{
	SDL_Renderer *renderer;
	SDL_Window *window;

	int keyboard[MAX_KEYBOARD_KEYS];

    GAME_STATE enum_game_state;

    uint8_t fps;
    float delta_time;//??unused

}PROGRAM;


typedef struct CHARACTER{
   float x;float width;
   float y;float height;
   float vel_x;float dx;
   float vel_y;float dy;

   bool flipped;

   PLAYER_STATE enum_player_state;
   bool grounded;
   bool can_attack;

   CONTROLLER control;//AI or p1 or p2
   bool movement_control[4];//movement keys. updated by keyboard input or AI depending on control
   bool action_control[2];//action keys. updated by keyboard input or AI depnding on control

   uint8_t hp;
}CHARACTER;//todo:create 2 characters


typedef struct{

}ATK_INFO;//todo:create attack queue

PROGRAM prog;
CHARACTER players[NUMBER_OF_PLAYERS];

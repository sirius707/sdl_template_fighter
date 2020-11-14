#include "common.h"//redundant? it still compiles if i don't include this

typedef struct PROGRAM{
	SDL_Renderer *renderer;
	SDL_Window *window;

	int keyboard[MAX_KEYBOARD_KEYS];

    GAME_STATE enum_game_state;

    uint8_t fps;
    float delta_time;//??unused

}PROGRAM;


typedef struct FRAME{
    bool active;
    uint8_t column;
    uint8_t row;
    uint8_t data;
}ANIMATION_FRAME;

typedef struct ANIMATION{
    char name[20];
    ANIMATION_FRAME frames[MAX_SEQUENCES][MAX_FRAMES];
    uint8_t transition_table[MAX_SEQUENCES][MAX_CHARACTER_STATES];//for when a sequence is interrupted by a state
    uint8_t default_states[MAX_CHARACTER_STATES];//index is player state, value is sequence, default to this if there is nothing in transition table
    SDL_Texture *sprite_sheet;
}ANIMATION;


typedef struct CHARACTER{
   float x;float width;
   float y;float height;
   float vel_x;float dx;
   float vel_y;float dy;

   bool flipped;
   struct CHARACTER *enemy;//we need this so we can flip the sprite to "look at the enemy"

   ANIMATION *ptr_animation;
   uint8_t current_squence;
   uint8_t current_frame;
   bool animation_end;//only true when current frame goes beyond the last frame, i.e when current frame.active = false
   uint8_t frame_counter;//temporary frame counter that will be used to simulate animation, until we implement animation

   PLAYER_STATE enum_player_state;
   PLAYER_STATE cache_state;//temporary state that will be use to store current state if we shift to attack state, attack state is responsible for returning us to the cached state
   bool grounded;
   bool can_attack;

   CONTROLLER control;//AI or p1 or p2
   bool movement_control[4];//movement keys. updated by keyboard input or AI depending on control
   bool action_control[4];//action keys. updated by keyboard input or AI depnding on control

   uint8_t hp;
}CHARACTER;//todo:create 2 characters


typedef struct{

}ATK_INFO;//todo:create attack queue


PROGRAM prog;
CHARACTER entities[NUMBER_OF_PLAYERS];
ANIMATION animations[NUMBER_OF_ANIMATIONS];

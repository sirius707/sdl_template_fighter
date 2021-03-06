#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "common.h"

typedef struct PROGRAM{
	SDL_Renderer *renderer;
	SDL_Window *window;

	int keyboard[MAX_KEYBOARD_KEYS];

    GAME_STATE enum_game_state;

    uint8_t fps;
    float delta_time;//??unused

}PROGRAM;

typedef struct INPUT{
    bool p1_movement[4];
    bool p2_movement[4];
    bool ai_movement[4];
    bool p1_action[4];
    bool p2_action[4];
    bool ai_action[4];


}INPUT;

typedef struct{
    //hitbox
    float x, y;
    float width, height;

    float target_dx;//displace victim
    float target_dy;//displace victim

    uint8_t damage;

    ATTACK_TYPE type;
}ATK_INFO;//todo:create attack queue

typedef struct FRAME{
    bool active;
    uint32_t x;
    uint32_t y;
    uint8_t data;
}ANIMATION_FRAME;

typedef struct ANIMATION{
    char name[20];
    ANIMATION_FRAME frames[MAX_SEQUENCES][MAX_FRAMES];
    int8_t transition_table[MAX_CHARACTER_STATES][MAX_SEQUENCES];//for when a sequence is interrupted by a state
    uint8_t default_seqs[MAX_CHARACTER_STATES];//index is player state, value is sequence, default to this if there is nothing in transition table

    uint8_t sprite_w;//visual width, used in rednering, must be bigger than logical width
    uint8_t sprite_h;//visual height, used in rednering, must be bigger than logical height
    int8_t sprite_x_displacement;
    int8_t sprite_y_displacement;
    uint32_t sprite_scale;//visual scale of the sprite

    ATK_INFO attacks[NUMBER_OF_ATTACKS_PER_ANIMATION];

    SDL_Texture *sprite_sheet;
}ANIMATION;


typedef struct CHARACTER{
   float x;uint16_t width;//logical width, used in physics
   float y;uint16_t height;//logical height, used in physics
   float vel_x;float dx;
   float vel_y;float dy;

   float processing_delay;//if this is not 0 certain processes will not happen to the player, physics, fsm and attacks

   bool flipped;
   struct CHARACTER *enemy;//we need this so we can flip the sprite to "look at the enemy"

   ANIMATION *ptr_animation;
   uint8_t current_squence;
   uint8_t current_frame;
   bool animation_end;//only true when current frame goes beyond the last frame, i.e when current frame.active = false
   uint8_t frame_counter;//temporary frame counter that will be used to simulate animation, until we implement animation
   float animation_elapsed_time;//play animation if this is greater than 1/ANIMATION_PLAY_RATE, increment with delta time each logical frame.
   bool render_foreground;
   bool loop_animation;

   PLAYER_STATE enum_player_state;
   PLAYER_STATE cache_state;//temporary state that will be use to store current state if we shift to attack state, attack state is responsible for returning us to the cached state
   bool grounded;
   bool can_attack;
   bool is_attacking;
   float parry_timer;//if not 0 then we're parrying
   float low_parry_timer;//crouch parry

   CONTROLLER control;//AI or p1 or p2
   bool *movement_control;//movement keys. updated by keyboard input or AI depending on control, ptr to array
   bool *action_control;//action keys. updated by keyboard input or AI depnding on control, ptr to array

   int8_t hp;
}CHARACTER;//todo:create 2 characters


extern ANIMATION animations[];
extern CHARACTER entities[];
extern PROGRAM prog;
extern CHARACTER *foreground_entity;
extern INPUT input;


#endif // STRUCTS_H_

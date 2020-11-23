#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define SCREEN_W 640
#define SCREEN_H 480

#define MAX_KEYBOARD_KEYS 350

#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_ATTACKS_PER_ANIMATION 4
#define NUMBER_OF_ANIMATIONS 3

#define ANIMATION_PLAY_RATE 10.0 //how many animation frames to play per second

#define MOVEMENT_DIVIDER 0.55 //amount with which to slow movement

//controls
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ACTION_A 0
#define ACTION_B 1
#define ACTION_C 2
#define ACTION_D 3

//animation
#define MAX_SEQUENCES 30
#define MAX_FRAMES 30

#define MAX_CHARACTER_STATES 20

typedef enum{ IDLE, WALK, WALK_BACK, JUMP, JUMP_BACK, ATTACK, DASH, GET_ATTACKED, BLOCK, PARRY, FALL}PLAYER_STATE;
typedef enum{ PLAYER_ONE, PLAYER_TWO, AI}CONTROLLER;
typedef enum{ RUNNING, PAUSED}GAME_STATE;
typedef enum{ HIGH, MID, LOW}ATTACK_TYPE;

#endif // DEFS_H_INCLUDED

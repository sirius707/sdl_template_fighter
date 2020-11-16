#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define SCREEN_W 640
#define SCREEN_H 480

#define MAX_KEYBOARD_KEYS 350

#define NUMBER_OF_PLAYERS 2

#define NUMBER_OF_ANIMATIONS 2

#define ANIMATION_PLAY_RATE 9.0 //how many animation frames to play per second

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

#define MAX_CHARACTER_STATES 15

typedef enum{ IDLE, WALK, JUMP, ATTACK, DASH, GET_ATTACKED, BLOCK, PARRY, FALL}PLAYER_STATE;
typedef enum{ PLAYER_ONE, PLAYER_TWO, AI}CONTROLLER;
typedef enum{ RUNNING, PAUSED}GAME_STATE;

#endif // DEFS_H_INCLUDED

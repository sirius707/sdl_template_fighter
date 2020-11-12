#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define SCREEN_W 640
#define SCREEN_H 480

#define MAX_KEYBOARD_KEYS 350

#define NUMBER_OF_PLAYERS 2

//controls
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ACTION_A 0
#define ACTION_B 1
#define ACTION_C 2
#define ACTION_D 3

typedef enum{ IDLE, WALK, JUMP, ATTACK, DASH, GET_ATTACKED, BLOCK, PARRY, FALL}PLAYER_STATE;
typedef enum{ PLAYER_ONE, PLAYER_TWO, AI}CONTROLLER;
typedef enum{ RUNNING, PAUSED}GAME_STATE;

#endif // DEFS_H_INCLUDED

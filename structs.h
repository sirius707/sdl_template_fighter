#include "common.h"//redundant? it still compiles if i don't include this

typedef struct{
	SDL_Renderer *renderer;
	SDL_Window *window;

	int keyboard[MAX_KEYBOARD_KEYS];

    uint8_t fps;
    float delta_time;//??unused
}PROGRAM;
PROGRAM prog;

typedef struct{
   float x;
   float y;

   float dx;
   float dy;

   uint8_t hp;
}CHARACTER;//todo:create 2 characters
CHARACTER players[NUMBER_OF_PLAYERS];

typedef struct{

}ATK_INFO;//todo:create attack queue

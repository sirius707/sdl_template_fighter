#include "common.h"//redundant? it still compiles if i don't include this

typedef struct{
	SDL_Renderer *renderer;
	SDL_Window *window;

	int keyboard[MAX_KEYBOARD_KEYS];

    uint8_t fps;
}PROGRAM;

PROGRAM prog;

typedef struct{
   float x;
   float y;

   uint8_t hp;
   bool parried;//game specifc, use std bool instead
}CHARACTER;//todo:create 2 characters

typedef struct{

}ATK_INFO;//todo:create attack queue

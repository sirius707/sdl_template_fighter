#ifndef MY_SDL_UTIL_H
#define MY_SDL_UTIL_H

#include <SDL.h>
#include "stdio.h"

SDL_Surface *optimise_surface(SDL_Surface *surface, const SDL_Surface *opt_for);
SDL_Texture *accelerate_surface(SDL_Surface *surface, SDL_Renderer *renderer);//turn it into a texture
void s_cap_framerate(long*, float*);

#endif // SDL_UTIL_H

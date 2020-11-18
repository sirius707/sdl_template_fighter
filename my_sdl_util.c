#include "my_sdl_util.h"
#include <assert.h>

SDL_Surface *optimise_surface(SDL_Surface *surface, const SDL_Surface *opt_for)
{
    SDL_Surface *tmp;

    tmp = SDL_ConvertSurface(surface, opt_for->format, 0);

    if(tmp != NULL){
        SDL_FreeSurface(surface);
        surface = tmp;

        return surface;
    }

    return NULL;
}

SDL_Texture *accelerate_surface(SDL_Surface *surface, SDL_Renderer *renderer, Uint32 colorkey)
{
    SDL_SetColorKey(surface, SDL_TRUE, colorkey);
    SDL_Texture *result = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return result;
}

inline long s_cap_framerate(long *then, float *remainder, size_t fps)
{
	long wait, frameTime;

	wait = 1000/fps + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1){
		wait = 1;
	}


	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();

	return frameTime;
}

inline bool aab_collision(float x1, float y1, float x2, float y2, float w1, float h1, float w2, float h2)
{
    bool c1, c2, c3, c4;//conditions that must be fulfilled to know that there is no collision
    c1 = y1 < y2 + h2;
    c2 = x1 < x2 + w2;
    c3 = y1 + h1 > y2;
    c4 = x1 + w1 > x2;

    return (c1 && c2 && c3 && c4);
}

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

#include "game.h"

void s_cap_framerate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1){
		wait = 1;
	}

    printf("%ld\n", wait);
	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}

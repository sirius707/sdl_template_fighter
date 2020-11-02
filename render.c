#include "render.h"

void render_prepare(void)
{
	SDL_SetRenderDrawColor(prog.renderer, 0, 255, 0, 255);
	SDL_RenderClear(prog.renderer);
}

void render_present(void)
{
	SDL_RenderPresent(prog.renderer);
}

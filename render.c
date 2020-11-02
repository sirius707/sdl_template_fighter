#include "render.h"

void s_render_prepare(void)
{
	SDL_SetRenderDrawColor(prog.renderer, 0, 25, 25, 255);
	SDL_RenderClear(prog.renderer);
}

void s_render_present(void)
{
	SDL_RenderPresent(prog.renderer);
}

#include "render.h"


extern CHARACTER players[];

void s_render_players(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
          SDL_Rect rect;
            rect.x = players[i].x;
            rect.y = players[i].y;
            rect.w = 100;
            rect.h = 150;

            SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(prog.renderer, &rect);
    }
}

void s_render_prepare(void)
{
	SDL_SetRenderDrawColor(prog.renderer, 0, 25, 25, 255);
	SDL_RenderClear(prog.renderer);
}

void s_render_present(void)
{
	SDL_RenderPresent(prog.renderer);
}

void s_render_total(void)
{
    s_render_prepare();
    s_render_players();
    s_render_present();
}

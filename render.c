#include "render.h"


extern CHARACTER players[];
CHARACTER const *players_ptr;

void s_render_init(void)
{
    //should be passed, later
    players_ptr = players;
}

void s_render_players(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
          SDL_Rect rect;
            rect.x = players[i].x;
            rect.y = players[i].y;
            rect.w = players[i].width;
            rect.h = players[i].height;

            SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(prog.renderer, &rect);

            if(players[i].enum_player_state == ATTACK){

                if(players[i].flipped)
                    rect.x = players[i].x - 15 * players[i].frame_counter;
                else
                    rect.x = players[i].x + players[i].width;

                rect.y = players[i].y;
                rect.w = 15 * players[i].frame_counter;
                rect.h = 20;
                SDL_SetRenderDrawColor(prog.renderer, 2, 255, 25, 255);
                SDL_RenderDrawRect(prog.renderer, &rect);

            }
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

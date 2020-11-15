#include "render.h"


extern CHARACTER entities[];

void s_render_entities_test(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
          SDL_Rect rect;
            rect.x = entities[i].x;
            rect.y = entities[i].y;
            rect.w = entities[i].width;
            rect.h = entities[i].height;

            SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(prog.renderer, &rect);

            if(entities[i].enum_player_state == ATTACK){

                if(entities[i].flipped)
                    rect.x = entities[i].x - 15 * entities[i].frame_counter;
                else
                    rect.x = entities[i].x + entities[i].width;

                rect.y = entities[i].y;
                rect.w = 15 * entities[i].frame_counter;
                rect.h = 20;
                SDL_SetRenderDrawColor(prog.renderer, 2, 255, 25, 255);
                SDL_RenderDrawRect(prog.renderer, &rect);

            }
    }
}

void s_render_entities(void)
{
    SDL_SetRenderDrawColor(prog.renderer, 0, 0, 0, 255);
    SDL_RenderClear(prog.renderer);

    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
          SDL_Texture *sprites = entities->ptr_animation->sprite_sheet;
          uint8_t current_frame;
          uint8_t current_seq;
          uint16_t x;
          uint16_t y;
          current_frame = entities[i].current_frame;
          current_seq = entities[i].current_squence;
          x = entities[i].ptr_animation->frames[current_seq][current_frame].x;
          y = entities[i].ptr_animation->frames[current_seq][current_frame].y;

          SDL_Rect source;
            source.x = x;
            source.y = y;
            source.w = entities[i].width;
            source.h = entities[i].height;

          SDL_Rect rect;
            rect.x = entities[i].x;
            rect.y = entities[i].y;
            rect.w = entities[i].width * 2;
            rect.h = entities[i].height * 2;

            SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(prog.renderer, &rect);

            if(entities[i].flipped){
                SDL_RenderCopyEx(prog.renderer, sprites, &source, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            }else{
                SDL_RenderCopy(prog.renderer, sprites, &source, &rect);
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
    s_render_entities();
    s_render_present();
}

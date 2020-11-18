#include "render.h"


extern CHARACTER entities[];

SDL_Texture *background;

void s_render_init(void)
{
    background = SDL_CreateTexture( prog.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
}

inline void s_render_entities(void)
{
    SDL_SetRenderDrawColor(prog.renderer, 0, 0, 0, 255);
    SDL_RenderClear(prog.renderer);

    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
          SDL_Texture *sprites = entities[i].ptr_animation->sprite_sheet;
          uint8_t current_frame;
          uint8_t current_seq;
          uint32_t sprite_scale;
          uint32_t sprite_w;
          uint32_t sprite_h;
          uint32_t x_spritesheet;
          uint32_t y_spritesheet;
          int8_t x_displacement;
          int8_t y_displacement;
          bool flipped;
          uint8_t layer_order;

          sprite_scale = entities[i].ptr_animation->sprite_scale;
          sprite_w = entities[i].ptr_animation->sprite_w;
          sprite_h = entities[i].ptr_animation->sprite_h;

          current_frame = entities[i].current_frame;
          current_seq = entities[i].current_squence;
          x_spritesheet = entities[i].ptr_animation->frames[current_seq][current_frame].x;
          y_spritesheet = entities[i].ptr_animation->frames[current_seq][current_frame].y;

          x_displacement = entities[i].ptr_animation->sprite_x_displacement;
          y_displacement = entities[i].ptr_animation->sprite_y_displacement;

          flipped = entities[i].flipped;

          SDL_Rect source;
            source.x = x_spritesheet;
            source.y = y_spritesheet;
            source.w = sprite_w;
            source.h = sprite_h;

            SDL_Rect rect;
            //draw the sprite in the middle of the player box
            rect.x = (entities[i].x - (sprite_w*sprite_scale - entities[i].width)/2) + x_displacement * (flipped?-1:1);
            rect.y = (entities[i].y - (sprite_h*sprite_scale - entities[i].height)/2) + y_displacement;
            rect.w = sprite_w * sprite_scale;
            rect.h = sprite_h * sprite_scale;


            if(entities[i].flipped){
                SDL_RenderCopyEx(prog.renderer, sprites, &source, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            }else{
                SDL_RenderCopy(prog.renderer, sprites, &source, &rect);
            }


            rect.x = entities[i].x;
            rect.y = entities[i].y;
            rect.w = entities[i].width;
            rect.h = entities[i].height;


            SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(prog.renderer, &rect);
    }

}

void inline s_render_entity(CHARACTER *player)
{
    SDL_Texture *sprites = player->ptr_animation->sprite_sheet;
    uint8_t current_frame;
    uint8_t current_seq;
    uint32_t sprite_scale;
    uint32_t sprite_w;
    uint32_t sprite_h;
    uint32_t x_spritesheet;
    uint32_t y_spritesheet;
    int8_t x_displacement;
    int8_t y_displacement;
    bool flipped;
    uint8_t layer_order;

    sprite_scale = player->ptr_animation->sprite_scale;
    sprite_w = player->ptr_animation->sprite_w;
    sprite_h = player->ptr_animation->sprite_h;

    current_frame = player->current_frame;
    current_seq = player->current_squence;
    x_spritesheet = player->ptr_animation->frames[current_seq][current_frame].x;
    y_spritesheet = player->ptr_animation->frames[current_seq][current_frame].y;

    x_displacement = player->ptr_animation->sprite_x_displacement;
    y_displacement = player->ptr_animation->sprite_y_displacement;

    flipped = player->flipped;

    SDL_Rect source;
    source.x = x_spritesheet;
    source.y = y_spritesheet;
    source.w = sprite_w;
    source.h = sprite_h;

    SDL_Rect rect;
            //draw the sprite in the middle of the player box
    rect.x = (player->x - (sprite_w*sprite_scale - player->width)/2) + x_displacement * (flipped?-1:1);
    rect.y = (player->y - (sprite_h*sprite_scale - player->height)/2) + y_displacement;
    rect.w = sprite_w * sprite_scale;
    rect.h = sprite_h * sprite_scale;


    if(player->flipped){
        SDL_RenderCopyEx(prog.renderer, sprites, &source, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }else{
        SDL_RenderCopy(prog.renderer, sprites, &source, &rect);
    }


     rect.x = player->x;
     rect.y = player->y;
     rect.w = player->width;
     rect.h = player->height;


     SDL_SetRenderDrawColor(prog.renderer, 255, 255, 255, 255);
     SDL_RenderDrawRect(prog.renderer, &rect);

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

    s_render_entity(foreground_entity->enemy);
    s_render_entity(foreground_entity);
    //s_render_entities();

    s_render_present();
}

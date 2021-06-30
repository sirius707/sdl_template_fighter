#include "animation.h"

void s_animation_init(void)
{
    memset(animations, 0, sizeof(ANIMATION)*NUMBER_OF_ANIMATIONS);

    for(int i = 0; i < NUMBER_OF_ANIMATIONS; i++){
        for(int j = 0; j < MAX_CHARACTER_STATES; j++){
            for(int k = 0; k < MAX_SEQUENCES; k++){
                animations[i].transition_table[j][k] = -1;
            }
        }
    }
}

inline void s_animation_animate(CHARACTER *player)
{
    if(player->processing_delay > 0) return;//don't process

    if(player->animation_elapsed_time >= 1/ANIMATION_PLAY_RATE){

        player->animation_elapsed_time = 0.0;
        //if at went beyond last frame loop
        //other wise advance frame by 1
        const ANIMATION *ptr_animation = player->ptr_animation;
        uint8_t *sequence = &player->current_squence;
        uint8_t *frame = &player->current_frame;

        (*frame)++;
        player->animation_end = !(ptr_animation->frames[*sequence][*frame].active);

        if(player->animation_end){
                if(player->loop_animation)*frame = 0;
                else{
                  (*frame)--;
                }
        }

        player->is_attacking = player->ptr_animation->frames[*sequence][*frame].data;

    }

}

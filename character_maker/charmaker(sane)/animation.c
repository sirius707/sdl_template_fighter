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



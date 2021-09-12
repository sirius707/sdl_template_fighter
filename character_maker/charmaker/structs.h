#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "common.h"

typedef struct PROGRAM{


}PROGRAM;



typedef struct{
    //hitbox
    float x, y;
    float width, height;

    float target_dx;//displace victim
    float target_dy;//displace victim

    uint8_t damage;

    ATTACK_TYPE type;
}ATK_INFO;//todo:create attack queue

typedef struct FRAME{
    bool active;
    uint32_t x;
    uint32_t y;
    uint8_t data;
}ANIMATION_FRAME;

typedef struct ANIMATION{
    char name[20];
    ANIMATION_FRAME frames[MAX_SEQUENCES][MAX_FRAMES];
    int8_t transition_table[MAX_CHARACTER_STATES][MAX_SEQUENCES];//for when a sequence is interrupted by a state
    uint8_t default_seqs[MAX_CHARACTER_STATES];//index is player state, value is sequence, default to this if there is nothing in transition table

    uint8_t sprite_w;//visual width, used in rednering, must be bigger than logical width
    uint8_t sprite_h;//visual height, used in rednering, must be bigger than logical height
    int8_t sprite_x_displacement;
    int8_t sprite_y_displacement;
    uint32_t sprite_scale;//visual scale of the sprite

    ATK_INFO attacks[NUMBER_OF_ATTACKS_PER_ANIMATION];

    void *sprite_sheet;
}ANIMATION;


extern ANIMATION animations[];
extern PROGRAM prog;



#endif // STRUCTS_H_

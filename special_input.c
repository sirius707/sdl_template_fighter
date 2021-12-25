
#include "common.h"//SDL
#include "structs.h"//structs
#include "special_input.h"

#include <stdio.h>

void s_SInput_GetSpecialInput(CHARACTER *player)
{
    bool *movement_control;//movement keys. updated by keyboard input or AI depending on control, ptr to array
    bool *action_control;//action keys. updated by keyboard input or AI depnding on control, ptr to array
    INPUT_FRAME *frame_buffer;
    INPUT_FRAME tmp_input_frame;

    movement_control = player->movement_control;
    action_control = player->action_control;
    frame_buffer = player->input_frame_buffer;

    //translate to input frame;
    tmp_input_frame.bits.a = action_control[ACTION_A];
    tmp_input_frame.bits.b = action_control[ACTION_B];
    tmp_input_frame.bits.c = action_control[ACTION_C];
    tmp_input_frame.bits.d = action_control[ACTION_D];

    tmp_input_frame.bits.up    = movement_control[UP];
    tmp_input_frame.bits.down  = movement_control[DOWN];
    tmp_input_frame.bits.left  = movement_control[LEFT];
    tmp_input_frame.bits.right = movement_control[RIGHT];


    //insert into frame buffer
    player->input_frame_buffer[player->current_input_frame] = tmp_input_frame;

    player->current_input_frame++;
    if(player->current_input_frame > INPUT_BUFFER_LENGTH)player->current_input_frame = 0;

    //printf("%x\n", tmp_input_frame.value);
}


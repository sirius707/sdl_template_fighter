#include "game.h"

//external access will be to entities, animations and attacks
extern CHARACTER entities[];

void s_game_player_logic(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        s_game_get_input(&entities[i]);
        s_game_animate(&entities[i]);
        s_game_player_fsm(&entities[i]);
    }
}

inline void s_game_player_fsm(CHARACTER *player)
{
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = player->movement_control[RIGHT] + (-player->movement_control[LEFT]);

    if(player->can_attack){
        if(player->action_control[ACTION_A]){
            player->cache_state = player->enum_player_state;
            player->can_attack = false;
            if(player->grounded)player->dx = 0;
            s_game_shift_player_state(player, ATTACK);
        }
    }

    if(player->grounded)player->flipped = player->enemy->x < player->x;//flip player if facing wrong direction

    switch(player->enum_player_state){

        case IDLE:
            player->dx = movement_direction * DEFAULT_WALKSPD * prog.delta_time;
            if(player->movement_control[UP]){

                    player->dy -= DEFAULT_JMPSPD * prog.delta_time;
                    player->grounded = false;
                    player->can_attack = true;
                    s_game_shift_player_state(player, JUMP);
            }
        break;

        case JUMP:
            if(player->y < GROUND_HEIGHT - DEFAULT_MAX_JMPHEIGHT || player->dy > 0){ //if player reached max height or started falling
                player->dy = 0;
                player->can_attack = true;
                s_game_shift_player_state(player, FALL);
            }

        break;

        case FALL:
            if(player->grounded){
                player->can_attack = true;
                s_game_shift_player_state(player, IDLE);
            }
        break;

        case ATTACK:
            if(player->frame_counter >= 10){
                player->frame_counter = 0;
                player->can_attack = true;
                s_game_shift_player_state(player, player->cache_state);
            }else{
                player->frame_counter++;
            }
        }
}

inline void s_game_get_input(CHARACTER *player)
{
    switch(player->control){
        case PLAYER_ONE:
            player->movement_control[UP] = prog.keyboard[SDL_SCANCODE_U];
            player->movement_control[LEFT] = prog.keyboard[SDL_SCANCODE_H];
            player->movement_control[RIGHT] = prog.keyboard[SDL_SCANCODE_K];
            player->movement_control[DOWN] = prog.keyboard[SDL_SCANCODE_J];

            player->action_control[ACTION_A] = prog.keyboard[SDL_SCANCODE_A];
            player->action_control[ACTION_B] = prog.keyboard[SDL_SCANCODE_S];
            player->action_control[ACTION_C] = prog.keyboard[SDL_SCANCODE_Z];
            player->action_control[ACTION_D] = prog.keyboard[SDL_SCANCODE_X];

            prog.keyboard[SDL_SCANCODE_A] = 0;
            prog.keyboard[SDL_SCANCODE_S] = 0;
            prog.keyboard[SDL_SCANCODE_Z] = 0;
            prog.keyboard[SDL_SCANCODE_X] = 0;
        break;

        case PLAYER_TWO:

            player->movement_control[UP] = prog.keyboard[SDL_SCANCODE_UP];
            player->movement_control[LEFT] = prog.keyboard[SDL_SCANCODE_LEFT];
            player->movement_control[RIGHT] = prog.keyboard[SDL_SCANCODE_RIGHT];
            player->movement_control[DOWN] = prog.keyboard[SDL_SCANCODE_DOWN];

            player->action_control[ACTION_A] = prog.keyboard[SDL_SCANCODE_9];
            player->action_control[ACTION_B] = prog.keyboard[SDL_SCANCODE_0];
            player->action_control[ACTION_C] = prog.keyboard[SDL_SCANCODE_O];
            player->action_control[ACTION_D] = prog.keyboard[SDL_SCANCODE_P];

            prog.keyboard[SDL_SCANCODE_9] = 0;
            prog.keyboard[SDL_SCANCODE_0] = 0;
            prog.keyboard[SDL_SCANCODE_O] = 0;
            prog.keyboard[SDL_SCANCODE_P] = 0;

            break;

        case AI:
            break;

        default:
            fprintf(stderr, "unknown player control value");
            exit(EXIT_FAILURE);

    }
}


inline void s_game_shift_player_state(CHARACTER *player, PLAYER_STATE state)
{
    player->enum_player_state = state;
    player->frame_counter = 0;
    player->current_frame = 0;
    player->animation_end = false;
    //check transition table first
    player->current_squence = player->ptr_animation->default_seqs[state];
    //change animation
    //adjust values if need be
}

inline void s_game_animate(CHARACTER *player)
{
    //if at went beyond last frame loop
    //other wise advance frame by 1

    const ANIMATION *ptr_animation = player->ptr_animation;
    uint8_t *sequence = &player->current_squence;
    uint8_t *frame = &player->current_frame;

    player->animation_end = !(ptr_animation->frames[*sequence][++(*frame)].active);
    if(player->animation_end)*frame = 0;

}

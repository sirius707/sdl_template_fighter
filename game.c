#include "game.h"

void s_game_player_logic(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        s_game_get_input();
        s_game_animate(&entities[i]);
        s_game_player_fsm(&entities[i]);
        s_game_process_attacks(&entities[i]);


        entities[i].animation_elapsed_time += prog.delta_time;
        if(entities[i].processing_delay > 0)entities[i].processing_delay -= prog.delta_time;
        if(entities[i].parry_timer > 0)entities[i].parry_timer -= prog.delta_time;
    }
}

inline void s_game_animate(CHARACTER *player)
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

inline void s_game_player_fsm(CHARACTER *player)
{
    if(player->processing_delay > 0)return;

    int movement_direction = 0; //1 or -1 or 0
    bool forward = false;//true if player is moving forward, whether flipped or not
    movement_direction = player->movement_control[RIGHT] + (-player->movement_control[LEFT]);

    forward = (!player->flipped && movement_direction > 0) || (player->flipped && movement_direction < 0);

    if(player->can_attack){
        if(player->action_control[ACTION_A]){
            s_game_player_attack(player);
        }
    }

    if(player->grounded)player->flipped = player->enemy->x < player->x;//flip player if facing wrong direction
    player->render_foreground = true;
    player->loop_animation = true;
    switch(player->enum_player_state){

        case IDLE:
            player->render_foreground = false;
            player->dx = movement_direction * DEFAULT_WALKSPD * prog.delta_time;

            if(!(player->grounded)){
                s_game_shift_player_state(player, FALL);
            }

            if(movement_direction){
                 s_game_shift_player_state(player, forward? WALK : WALK_BACK );
                 player->parry_timer = 0;//cancel parry if it's there
            }
            if(player->movement_control[UP]){
                s_game_player_jump(player);
            }

            if(player->movement_control[DOWN]){
                s_game_player_crouch(player);
            }
           if(player->action_control[ACTION_B])player->parry_timer = PARRY_WINDOW;//parry button

        break;

        case WALK:
        case WALK_BACK:
            player->render_foreground = false;
            player->dx = movement_direction * DEFAULT_WALKSPD * prog.delta_time;
            if(!forward)player->dx *= MOVEMENT_DIVIDER;//slow down if walking back

            if(!movement_direction){
                s_game_shift_player_state(player, IDLE);
            }
            if(player->movement_control[UP]){
                s_game_player_jump(player);
            }

            if(player->action_control[ACTION_B])player->parry_timer = PARRY_WINDOW;
        break;

        case JUMP:
        case JUMP_BACK:
            if(player->y >= GROUND_HEIGHT){//if player reached max height
                player->dy = 0;
            }
            if(player->dy > 0){ // started falling
                //player->can_attack = true;
                s_game_shift_player_state(player, FALL);
            }
            player->loop_animation = false;
        break;

        case CROUCH:
            player->loop_animation = false;
            if(!player->movement_control[DOWN]){
                s_game_shift_player_state(player, IDLE);
            }
        break;

        case FALL:
            player->render_foreground = false;
            if(player->grounded){
                //player->can_attack = true;
                s_game_shift_player_state(player, IDLE);
            }
        break;

        case BLOCK:
            player->render_foreground = false;
            if(forward){//id player moves forward, whether flipped or not, we want to keep blocking if player presses back,
                 s_game_shift_player_state(player, WALK);
            }
            if(player->animation_end){
                s_game_goto_cached_state(player);
            }
        break;

        case ATTACK:
            if(player->grounded)player->dx = 0;
            if(player->animation_end){
                s_game_goto_cached_state(player);
            }

            if(player->can_attack){//can parry if i hit something, even if i am parried
                if(player->action_control[ACTION_B])player->parry_timer = PARRY_WINDOW;//parry button
            }
        break;

        case GET_ATTACKED:
            player->flipped = player->enemy->x < player->x;
            player->render_foreground = false;
            if(player->animation_end){
                s_game_goto_cached_state(player);
            }
        break;

        case PARRY:
            //player->enum_player_state = player->cache_state;//ugly but we need this to change logical state and retain parry animation, this is nice, but how can we detect animation end
            if(player->action_control[ACTION_B])player->parry_timer = PARRY_WINDOW;//parry button
            if(player->animation_end){
                s_game_goto_cached_state(player);
            }
        break;

        default:
            fprintf(stderr, "unkown state\n");
        break;
    }

    if(player->render_foreground)foreground_entity = player;
    s_game_clear_action_keys(player);//we need to do this to make inputs more responsive, especially after parrying, if its too responsive just clear the keys in the input function itself
}

inline void s_game_process_attacks(CHARACTER *player)
{
        if(player->processing_delay > 0)return;
        //
        //make code here for when both player and enemy are attacking at the same time
        //

        if(player->is_attacking){
            ATK_INFO *ptr_attack;
            float attack_x, attack_y, attack_w, attack_h;//hit box

            ptr_attack = s_game_get_current_attack(player);

            player->is_attacking = false;
            //construct hit bookx
            attack_x = player->x;
            attack_y = player->y + ptr_attack->y;
            attack_w = ptr_attack->width;
            attack_h = ptr_attack->height;
            if(player->flipped){
                attack_x -= -player->width + attack_w + ptr_attack->x;
            }else{
                attack_x += ptr_attack->x;
            }


            //if(fabs(player->x - player->enemy->x) < 100){
            if(aab_collision(attack_x, attack_y,
                            player->enemy->x, player->enemy->y,
                            attack_w, attack_h,
                            player->enemy->width, player->enemy->height)){

                player->processing_delay = ON_HIT_DELAY;
                player->enemy->processing_delay = ON_HIT_DELAY;
                player->can_attack = true;

                if(player->enemy->parry_timer > 0){
                    //player->can_attack =false;//maybe shift the attacker to a different sequence that leads to a heavy attack, to facilitate back and forth parrying
                    player->enemy->can_attack = true;
                    s_game_cache_state(player->enemy);
                    s_game_shift_player_state(player->enemy, PARRY);
                    player->enemy->parry_timer = 0;
                    return;
                }

                player->enemy->dx = ptr_attack->target_dx * (player->flipped? -1: 1);
                player->enemy->dy = ptr_attack->target_dy;

                player->enemy->can_attack = false;

                switch(player->enemy->enum_player_state){
                    case IDLE:
                    case BLOCK:
                    case WALK_BACK:
                    case JUMP_BACK:
                    //case walk_back: implement later
                            player->enemy->enum_player_state = 0;//reset to allow shift state to go to duplicate state
                            s_game_cache_state(player->enemy);
                            s_game_shift_player_state(player->enemy, BLOCK);
                    break;

                    default:
                            //appply attack stats
                            player->enemy->hp -= ptr_attack->damage;
                            player->enemy->enum_player_state = 0;//reset to allow shift state to go to duplicate state
                            s_game_cache_state(player->enemy);
                            s_game_shift_player_state(player->enemy, GET_ATTACKED);

                }
            }
        }

}

inline void s_game_get_input(void)
{
            input.p1_movement[UP] = prog.keyboard[SDL_SCANCODE_U];
            input.p1_movement[LEFT] = prog.keyboard[SDL_SCANCODE_H];
            input.p1_movement[RIGHT] = prog.keyboard[SDL_SCANCODE_K];
            input.p1_movement[DOWN] = prog.keyboard[SDL_SCANCODE_J];

            input.p1_action[ACTION_A] = prog.keyboard[SDL_SCANCODE_A];
            input.p1_action[ACTION_B] = prog.keyboard[SDL_SCANCODE_S];
            input.p1_action[ACTION_C] = prog.keyboard[SDL_SCANCODE_Z];
            input.p1_action[ACTION_D] = prog.keyboard[SDL_SCANCODE_X];


            input.p2_movement[UP] = prog.keyboard[SDL_SCANCODE_UP];
            input.p2_movement[LEFT] = prog.keyboard[SDL_SCANCODE_LEFT];
            input.p2_movement[RIGHT] = prog.keyboard[SDL_SCANCODE_RIGHT];
            input.p2_movement[DOWN] = prog.keyboard[SDL_SCANCODE_DOWN];

            input.p2_action[ACTION_A] = prog.keyboard[SDL_SCANCODE_9];
            input.p2_action[ACTION_B] = prog.keyboard[SDL_SCANCODE_0];
            input.p2_action[ACTION_C] = prog.keyboard[SDL_SCANCODE_O];
            input.p2_action[ACTION_D] = prog.keyboard[SDL_SCANCODE_P];
}

void s_game_clear_action_keys(CHARACTER*player)
{
    switch(player->control){
        case PLAYER_ONE:
            prog.keyboard[SDL_SCANCODE_A] = 0;
            prog.keyboard[SDL_SCANCODE_S] = 0;
            prog.keyboard[SDL_SCANCODE_Z] = 0;
            prog.keyboard[SDL_SCANCODE_X] = 0;
        break;

        case PLAYER_TWO:
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

//helper funcions
inline void s_game_shift_player_state(CHARACTER *player, PLAYER_STATE state)
{
    uint8_t current_sequence = player->current_squence;

    if(player->ptr_animation->transition_table[state][current_sequence] != -1){//check transition table first
        player->current_squence = player->ptr_animation->transition_table[state][current_sequence];
    }else{//go to default state animation, only if we aren't already in that state, this is mainly to avoid the first attack being repeated endlessly
        if(player->enum_player_state != state){
            player->current_squence = player->ptr_animation->default_seqs[state];
        }else{
            return;
        }
    }

    player->enum_player_state = state;
    player->frame_counter = 0;
    player->current_frame = 0;
    player->animation_end = false;
    player->animation_elapsed_time = 1;//so we don't wait for the animation when we shift to a new sequence


    //change animation
    //adjust values if need be
}


inline void s_game_cache_state(CHARACTER *player)//pushes a player state into cache so it can be retrieved later
{
    //in the future we might want to cache animation as well
    switch(player->enum_player_state){
        case IDLE:
        case FALL:
        case JUMP:
            player->cache_state = player->enum_player_state;

        default:
            if(player->grounded)player->cache_state = IDLE;
            else player->cache_state = FALL;

    }
}

//shifts player state to cached state
inline void s_game_goto_cached_state(CHARACTER *player)
{
    player->animation_end = false;
    player->can_attack = true;//debatable
    s_game_shift_player_state(player, player->cache_state);
}

inline void s_game_player_jump(CHARACTER *player)
{
    player->processing_delay = NORMAL_DELAY;//pause the first frame a little (;, looks cooler, also no physics is applied for a litle while
    player->dy -= DEFAULT_JMPSPD * prog.delta_time;
    player->grounded = false;
    player->can_attack = true;
    player->parry_timer = 0;
    s_game_shift_player_state(player, JUMP);
}

inline void s_game_player_crouch(CHARACTER *player)
{
    //player->processing_delay = NORMAL_DELAY;//pause the first frame a little (;, looks cooler, also no physics is applied for a litle while
    player->dx = 0;
    player->grounded = true;
    player->can_attack = true;
    player->parry_timer = 0;
    s_game_shift_player_state(player, CROUCH);
}

void s_game_player_attack(CHARACTER *player)
{
    s_game_cache_state(player);
    player->can_attack = false;
    player->parry_timer = 0;
    if(player->grounded)player->dx = 0;
    s_game_shift_player_state(player, ATTACK);
}

ATK_INFO *s_game_get_current_attack(CHARACTER *player)
{
    ANIMATION *ptr_animation;
    uint16_t sequence;
    uint16_t frame;
    uint8_t attack_index;

    ptr_animation = player->ptr_animation;
    sequence = player->current_squence;
    frame = player->current_frame;

    attack_index = ptr_animation->frames[sequence][frame].data - 1;

    return &(ptr_animation->attacks[attack_index]);
}

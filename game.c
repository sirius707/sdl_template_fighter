#include "game.h"

//external access will be to entities, animations and attacks
extern CHARACTER entities[];

void s_game_physics(void)
{
    //entities
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){


        //gravity
        //entities[i].vel_y += G * prog.delta_time;
        entities[i].dy += DEFAULT_FALLSPD * prog.delta_time;

        //i don't think we will need velocity in a fighting game
        //but what about jumping?
        entities[i].dy += prog.delta_time * entities[i].vel_y;
        entities[i].dx += prog.delta_time * entities[i].vel_x;

        //collision detection
        entities[i].y += entities[i].dy;
        if(entities[i].y + entities[i].height > GROUND_HEIGHT){
            entities[i].y = GROUND_HEIGHT - entities[i].height;
            entities[i].vel_y = 0;
            entities[i].dy = 0;
            entities[i].grounded = true;
        }

        //collision with other players
        if(entities[i].dx != 0){
            for(int j = 0; j < NUMBER_OF_PLAYERS; j++){
                if(j == i)continue;

                if(fabs(entities[i].y - entities[j].y) < entities[i].height/2){//if y collision
                    if(fabs(entities[i].x - entities[j].x) < entities[i].width*0.8){//if collision with other players
                       entities[i].dx *= 0.8;//damp walk speed

                       //displace other player
                       if(entities[i].x < entities[j].x){//if the other player is on the rgiht
                            entities[j].x = entities[i].x + entities[i].width + 0.2f;
                       }else{
                            entities[j].x = entities[i].x - entities[j].width - 0.2f;
                       }
                    }
                }
            }
        }
        entities[i].x += entities[i].dx;

    }
}

void s_game_p1_logic(void)//test function
{
    //int movement_direction = 0; //1 or -1 or 0
    //movement_direction = prog.keyboard[SDLK_RIGHT] + (-prog.keyboard[SDLK_LEFT]);
    //entities[0].dx = movement_direction * DEFAULT_XSPD;

    //if(prog.keyboard[SDLK_UP]){
      //      puts("jump");
        //    entities[0].vel_y += -DEFAULT_JMPSPD;
          //  prog.keyboard[SDLK_SPACE] = 0;
    //}
}

void s_game_player_logic(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        s_game_get_input(&entities[i]);
        s_game_player_fsm(&entities[i]);
    }
}

inline void s_game_player_fsm(CHARACTER *player)
{
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = player->movement_control[RIGHT] + (-player->movement_control[LEFT]);

    if(player->can_attack){
        int tmp = player->action_control[ACTION_A];
        if(player->action_control[ACTION_A]){
            player->cache_state = player->enum_player_state;
            player->can_attack = false;
            if(player->grounded)player->dx = 0;
            s_game_shift_player_state(player, ATTACK);
        }
    }

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
    //change animation
    //adjust values if need be
}

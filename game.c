#include "game.h"

//external access will be to players, animations and attacks
extern CHARACTER players[];

void s_game_physics(void)
{
    //players
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){


        //gravity
        //players[i].vel_y += G * prog.delta_time;
        players[i].dy += DEFAULT_FALLSPD * prog.delta_time;

        //i don't think we will need velocity in a fighting game
        //but what about jumping?
        players[i].dy += prog.delta_time * players[i].vel_y;
        players[i].dx += prog.delta_time * players[i].vel_x;

        //collision detection
        players[i].y += players[i].dy;
        if(players[i].y + players[i].height > GROUND_HEIGHT){
            players[i].y = GROUND_HEIGHT - players[i].height;
            players[i].vel_y = 0;
            players[i].dy = 0;
            players[i].grounded = true;
        }


        players[i].x += players[i].dx;

    }
}

void s_game_p1_logic(void)//test function
{
    //int movement_direction = 0; //1 or -1 or 0
    //movement_direction = prog.keyboard[SDLK_RIGHT] + (-prog.keyboard[SDLK_LEFT]);
    //players[0].dx = movement_direction * DEFAULT_XSPD;

    //if(prog.keyboard[SDLK_UP]){
      //      puts("jump");
        //    players[0].vel_y += -DEFAULT_JMPSPD;
          //  prog.keyboard[SDLK_SPACE] = 0;
    //}
}

void s_game_player_logic(void)
{
    //for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
    //    s_game_get_input(&players[i]);
    //    s_game_player_fsm(&players[i]);
    //}
    s_game_get_input(&players[0]);
    s_game_get_input(&players[1]);
    s_game_player_fsm(&players[0]);
    s_game_player_fsm(&players[1]);
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
            s_game_shift_player_state(player, ATTACK);
        }
    }

    switch(player->enum_player_state){

        case IDLE:
            players->dx = movement_direction * DEFAULT_WALKSPD * prog.delta_time;
            if(players->movement_control[UP]){
                    player->dy -= DEFAULT_JMPSPD * prog.delta_time;
                    player->grounded = false;
                    player->can_attack = true;
                    s_game_shift_player_state(player, JUMP);
            }
        break;

        case JUMP:
            if(players->y < GROUND_HEIGHT - DEFAULT_MAX_JMPHEIGHT || player->dy > 0){ //if player reached max height or started falling
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
            player->movement_control[UP] = prog.keyboard[SDL_SCANCODE_UP];
            player->movement_control[LEFT] = prog.keyboard[SDL_SCANCODE_LEFT];
            player->movement_control[RIGHT] = prog.keyboard[SDL_SCANCODE_RIGHT];
            player->movement_control[DOWN] = prog.keyboard[SDL_SCANCODE_DOWN];

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

            player->movement_control[UP] = 0;
            player->movement_control[LEFT] = 0;
            player->movement_control[RIGHT] = 0;
            player->movement_control[DOWN] = 0;

            player->action_control[ACTION_A] = 0;
            player->action_control[ACTION_B] = 0;
            player->action_control[ACTION_C] = 0;
            player->action_control[ACTION_D] = 0;

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

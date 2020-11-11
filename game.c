#include "game.h"

extern CHARACTER players[];

void s_game_physics(void)
{
    //players
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){


        //gravity
        //players[i].vel_y += G * prog.delta_time;
        players->dy += DEFAULT_FALLSPD * prog.delta_time;

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
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = prog.keyboard[SDLK_RIGHT] + (-prog.keyboard[SDLK_LEFT]);
    players[0].dx = movement_direction * DEFAULT_XSPD;

    if(prog.keyboard[SDLK_UP]){
            puts("jump");
            players[0].vel_y += -DEFAULT_JMPSPD;
            prog.keyboard[SDLK_SPACE] = 0;
    }
}

void s_game_player_logic(void)
{
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        s_game_get_input(&players[i]);
        s_game_player_fsm(&players[i]);
    }
}

inline void s_game_player_fsm(CHARACTER *player)
{
    int movement_direction = 0; //1 or -1 or 0
    movement_direction = player->movement_control[RIGHT] + (-player->movement_control[LEFT]);

    switch(player->enum_player_state){

        case IDLE:
            players->dx = movement_direction * DEFAULT_XSPD;
            if(players->movement_control[UP]){
                    player->dy -= DEFAULT_JMPSPD * prog.delta_time;
                    player->enum_player_state = JUMP;
                    player->grounded = 0;
            }
        break;

        case JUMP:
            if(player->grounded){
                player->enum_player_state = IDLE;
            }
        break;
    }
}

inline void s_game_get_input(CHARACTER *player)
{
    switch(player->control){
        case PLAYER_ONE:
            player->movement_control[UP] = prog.keyboard[SDLK_UP];
            player->movement_control[LEFT] = prog.keyboard[SDLK_LEFT];
            player->movement_control[RIGHT] = prog.keyboard[SDLK_RIGHT];
            player->movement_control[DOWN] = prog.keyboard[SDLK_DOWN];

            player->action_control[ACTION_1] = prog.keyboard[SDLK_a];
            player->action_control[ACTION_1] = prog.keyboard[SDLK_s];

            prog.keyboard[SDLK_a] = 0;
            prog.keyboard[SDLK_s] = 0;
        break;

        case PLAYER_TWO:
            break;

        case AI:
            break;

        default:
            fprintf(stderr, "unknown player control value");
            exit(EXIT_FAILURE);

    }
}

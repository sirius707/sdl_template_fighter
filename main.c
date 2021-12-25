#include "common.h"

#include "structs.h"
#include "init.h"
#include "render.h"
#include "input.h"
#include "special_input.h"
#include "game.h"
#include "physics.h"

//2d fighting game
// data oriented and data driven


int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    memset(&input, 0, sizeof(INPUT));
    memset(entities, 0, sizeof(CHARACTER)*NUMBER_OF_PLAYERS);
    init();
    s_render_init();

    entities[0].x = 100;
    entities[0].y = 20;
    entities[0].width = 30;
    entities[0].height = 100;
    entities[0].control = PLAYER_ONE;
    entities[0].enum_player_state = FALL;
    entities[0].hp = 100;
    entities[0].can_attack = true;
    entities[0].flipped = false;
    entities[0].enemy = &entities[1];
    entities[0].ptr_animation = &animations[2];
    entities[0].current_squence = 0;//fall
    entities[0].action_control = input.p1_action;
    entities[0].movement_control = input.p1_movement;

    entities[1].x = 450;
    entities[1].y = 20;
    entities[1].width = 30;
    entities[1].height = 100;
    entities[1].control = PLAYER_TWO;
    entities[1].enum_player_state = FALL;
    entities[1].hp = 100;
    entities[1].can_attack = true;
    entities[1].flipped = true;
    entities[1].enemy = &entities[0];
    entities[1].ptr_animation = &animations[2];
    entities[1].current_squence = 0;//fall
    entities[1].action_control = input.p2_action;
    entities[1].movement_control = input.p2_movement;

    foreground_entity = &entities[0];

    strcpy(animations[0].name, "stephan");//what does stephan mean
    SDL_Surface *temp_surface = SDL_LoadBMP("data\\hiei.bmp");
    if(temp_surface == NULL){
        return EXIT_FAILURE;
    }


    temp_surface = SDL_LoadBMP("data\\genkai.bmp");
    if(temp_surface == NULL){
        return EXIT_FAILURE;
    }
    {//character 3: genkai
        FILE *testfile = fopen("genkai", "rb");
        fread(&animations[2], sizeof(animations[2]), 1, testfile);
        //animations[2].sprite_y_displacement = -30;
        //animations[2].sprite_x_displacement = 0;
        animations[2].sprite_sheet = accelerate_surface(temp_surface, prog.renderer, SDL_MapRGB(temp_surface->format, 0, 0, 0));
        assert(animations[2].sprite_sheet !=  NULL);

    }

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    while(1){

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        s_input();
        s_SInput_GetSpecialInput(&entities[0]);//disgusting, remove later
        s_physics();
        s_game_player_logic();

        s_render_total();


        prog.delta_time = (double)((NOW - LAST)/ (double)SDL_GetPerformanceFrequency() );//temporary until a fix is found
        if(prog.delta_time > 1.0/prog.fps)prog.delta_time = 1.0/prog.fps;

        s_cap_framerate(&then, &remaining_time, prog.fps);
        //printf("%d %d \r", entities[0].hp,  entities[1].hp);

        /*for(int i = 0; i < INPUT_BUFFER_LENGTH; i++){
            printf("%d ", entities[0].input_buffer[i]);
        }
        printf("\r");*/
    }


    deinit();
	return 0;
}




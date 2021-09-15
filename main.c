#include "common.h"

#include "structs.h"
#include "init.h"
#include "render.h"
#include "input.h"
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
    entities[0].current_squence = 1;//fall
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
    entities[1].current_squence = 1;//fall
    entities[1].action_control = input.p2_action;
    entities[1].movement_control = input.p2_movement;

    foreground_entity = &entities[0];

    strcpy(animations[0].name, "stephan");//what does stephan mean
    SDL_Surface *temp_surface = SDL_LoadBMP("data\\hiei.bmp");
    if(temp_surface == NULL){
        return EXIT_FAILURE;
    }

    {//character 1
        animations[0].sprite_y_displacement = -30;
        animations[0].sprite_x_displacement = 20;
        animations[0].sprite_sheet = accelerate_surface(temp_surface, prog.renderer, SDL_MapRGB(temp_surface->format, 128, 128, 192));
        assert(animations[0].sprite_sheet !=  NULL);
        animations[0].sprite_w = 96;
        animations[0].sprite_h = 96;
        animations[0].sprite_scale = 3;

        animations[0].transition_table[FALL][IDLE] = 0;
        animations[0].default_seqs[IDLE] = 0;
        animations[0].default_seqs[FALL] = 1;
        animations[0].default_seqs[WALK] = 2;
        animations[0].default_seqs[JUMP] = 3;
        animations[0].default_seqs[ATTACK] = 4;
        animations[0].default_seqs[GET_ATTACKED] = 5;

        //idle frames
        animations[0].frames[0][0].x = 0;animations[0].frames[0][0].y = 0;animations[0].frames[0][0].active = 1;
        animations[0].frames[0][1].x = 96;animations[0].frames[0][1].y = 0;animations[0].frames[0][1].active = 1;
        animations[0].frames[0][2].x = 96*2;animations[0].frames[0][2].y = 0;animations[0].frames[0][2].active = 1;
        animations[0].frames[0][3].x = 96;animations[0].frames[0][3].y = 0;animations[0].frames[0][3].active = 1;

        //walk frames
        animations[0].frames[2][0].x = 96*3;animations[0].frames[2][0].y = 0;animations[0].frames[2][0].active = 1;
        animations[0].frames[2][1].x = 96*4;animations[0].frames[2][1].y = 0;animations[0].frames[2][1].active = 1;
        animations[0].frames[2][2].x = 96*5;animations[0].frames[2][2].y = 0;animations[0].frames[2][2].active = 1;
        animations[0].frames[2][3].x = 96*6;animations[0].frames[2][3].y = 0;animations[0].frames[2][3].active = 1;
        animations[0].frames[2][4].x = 96*7;animations[0].frames[2][4].y = 0;animations[0].frames[2][4].active = 1;
        animations[0].frames[2][5].x = 96*8;animations[0].frames[2][5].y = 0;animations[0].frames[2][5].active = 1;
        animations[0].frames[2][6].x = 96*9;animations[0].frames[2][6].y = 0;animations[0].frames[2][6].active = 1;


        //jump frames
        animations[0].frames[3][0].x = 96*7;animations[0].frames[3][0].y = 96*1;animations[0].frames[3][0].active = 1;
        animations[0].frames[3][1].x = 96*8;animations[0].frames[3][1].y = 96*1;animations[0].frames[3][1].active = 1;

        //get hit
        animations[0].frames[5][0].x = 96*4;animations[0].frames[5][0].y = 96*1;animations[0].frames[5][0].active = 1;
        animations[0].frames[5][1].x = 96*4;animations[0].frames[5][1].y = 96*1;animations[0].frames[5][1].active = 1;
        animations[0].frames[5][2].x = 96*4;animations[0].frames[5][2].y = 96*1;animations[0].frames[5][2].active = 1;
        animations[0].frames[5][3].x = 96*4;animations[0].frames[5][3].y = 96*1;animations[0].frames[5][3].active = 1;

        //attack frames
        animations[0].frames[4][0].x = 96*0;animations[0].frames[4][0].y = 90*8;animations[0].frames[4][0].active = 1;
        animations[0].frames[4][1].x = 96*1;animations[0].frames[4][1].y = 90*8;animations[0].frames[4][1].active = 1;animations[0].frames[4][3].data = 1;
        animations[0].frames[4][2].x = 96*2;animations[0].frames[4][2].y = 90*8;animations[0].frames[4][2].active = 1;
        animations[0].frames[4][3].x = 96*3;animations[0].frames[4][3].y = 90*8;animations[0].frames[4][3].active = 1;
        animations[0].frames[4][4].x = 96*4;animations[0].frames[4][4].y = 90*8;animations[0].frames[4][4].active = 1;

        //fall frames
        animations[0].frames[1][0].x = 96*9;animations[0].frames[1][0].y = 90*1;animations[0].frames[1][0].active = 1;

        //attacks
        animations[0].attacks[0].damage = 2;
        animations[0].attacks[0].target_dx = 1.2;
        animations[0].attacks[0].x = 40;
        animations[0].attacks[0].y = -80;
        animations[0].attacks[0].width = 150;
        animations[0].attacks[0].height = 100;

    }

    temp_surface = SDL_LoadBMP("data\\jin.bmp");
    if(temp_surface == NULL){
        return EXIT_FAILURE;
    }
    {//character 2: jin
        animations[1].sprite_y_displacement = -3;
        animations[1].sprite_x_displacement = 20;
        animations[1].sprite_sheet = accelerate_surface(temp_surface, prog.renderer, SDL_MapRGB(temp_surface->format, 192, 220, 192));
        assert(animations[1].sprite_sheet !=  NULL);
        animations[1].sprite_w = 159;
        animations[1].sprite_h = 169;
        animations[1].sprite_scale = 2;

        animations[1].transition_table[FALL][IDLE] = 0;
        animations[1].default_seqs[IDLE] = 0;
        animations[1].default_seqs[FALL] = 1;
        animations[1].default_seqs[WALK] = 2;
        animations[1].default_seqs[WALK_BACK] = 7;
        animations[1].default_seqs[JUMP] = 3;
        animations[1].default_seqs[ATTACK] = 4;
        animations[1].default_seqs[GET_ATTACKED] = 5;
        animations[1].default_seqs[BLOCK] = 6;
        animations[1].default_seqs[JUMP_BACK] = 3;
        animations[1].default_seqs[PARRY] = 6;

        //idle frames
        animations[1].frames[0][0].x = 0;animations[1].frames[0][0].y = 0;animations[1].frames[0][0].active = 1;
        animations[1].frames[0][1].x = 159;animations[1].frames[0][1].y = 0;animations[1].frames[0][1].active = 1;
        animations[1].frames[0][2].x = 159*2;animations[1].frames[0][2].y = 0;animations[1].frames[0][2].active = 1;
        animations[1].frames[0][3].x = 159*3;animations[1].frames[0][3].y = 0;animations[1].frames[0][3].active = 1;

        //walk frames
        animations[1].frames[2][0].x = 159*4;animations[1].frames[2][0].y = 0;animations[1].frames[2][0].active = 1;
        animations[1].frames[2][1].x = 159*5;animations[1].frames[2][1].y = 0;animations[1].frames[2][1].active = 1;
        animations[1].frames[2][2].x = 159*6;animations[1].frames[2][2].y = 0;animations[1].frames[2][2].active = 1;
        animations[1].frames[2][3].x = 159*7;animations[1].frames[2][3].y = 0;animations[1].frames[2][3].active = 1;
        animations[1].frames[2][4].x = 159*8;animations[1].frames[2][4].y = 0;animations[1].frames[2][4].active = 1;
        animations[1].frames[2][5].x = 159*9;animations[1].frames[2][5].y = 0;animations[1].frames[2][5].active = 1;

        //walk back frames
        animations[1].frames[7][5].x = 159*4;animations[1].frames[7][5].y = 0;animations[1].frames[7][5].active = 1;
        animations[1].frames[7][4].x = 159*5;animations[1].frames[7][4].y = 0;animations[1].frames[7][4].active = 1;
        animations[1].frames[7][3].x = 159*6;animations[1].frames[7][3].y = 0;animations[1].frames[7][3].active = 1;
        animations[1].frames[7][2].x = 159*7;animations[1].frames[7][2].y = 0;animations[1].frames[7][2].active = 1;
        animations[1].frames[7][1].x = 159*8;animations[1].frames[7][1].y = 0;animations[1].frames[7][1].active = 1;
        animations[1].frames[7][0].x = 159*9;animations[1].frames[7][0].y = 0;animations[1].frames[7][0].active = 1;

        //jump frames
        animations[1].frames[3][0].x = 159*10;animations[1].frames[3][0].y = 0;animations[1].frames[3][0].active = 1;

        //fall frames
        animations[1].frames[1][0].x = 159*11;animations[1].frames[1][0].y = 0;animations[1].frames[1][0].active = 1;

        //get attacked
        animations[1].frames[5][0].x = 0;animations[1].frames[5][0].y = 400;animations[1].frames[5][0].active = 1;
        animations[1].frames[5][1].x = 160;animations[1].frames[5][1].y = 400;animations[1].frames[5][1].active = 1;

        //attack frames
        animations[1].frames[4][0].x = 159;animations[1].frames[4][0].y = 0;animations[1].frames[4][0].active = 1;
        animations[1].frames[4][1].x = 159*0;animations[1].frames[4][1].y = 169*8;animations[1].frames[4][1].active = 1;animations[1].frames[4][1].data = 1;
        animations[1].frames[4][2].x = 159*1;animations[1].frames[4][2].y = 169*8;animations[1].frames[4][2].active = 1;
        animations[1].frames[4][3].x = 159*1;animations[1].frames[4][3].y = 169*8;animations[1].frames[4][3].active = 1;


        //block
        animations[1].frames[6][0].x = 320;animations[1].frames[6][0].y = 1350;animations[1].frames[6][0].active = 1;
        animations[1].frames[6][1].x = 320;animations[1].frames[6][1].y = 1350;animations[1].frames[6][1].active = 1;
        animations[1].frames[6][2].x = 320;animations[1].frames[6][2].y = 1350;animations[1].frames[6][2].active = 1;

        //attacks
        animations[1].attacks[0].damage = 2;
        animations[1].attacks[0].target_dx = 1.0;
        animations[1].attacks[0].x = 20;
        animations[1].attacks[0].y = 0;
        animations[1].attacks[0].width = 90;
        animations[1].attacks[0].height = 10;


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
        //animations[2].sprite_w = 80;
        //animations[2].sprite_h = 80;
        //animations[2].sprite_scale = 2;

        //animations[2].transition_table[FALL][IDLE] = 0;
        //animations[2].transition_table[GET_ATTACKED][IDLE] = 1;
       /* animations[2].default_seqs[IDLE] = 0;
        animations[2].default_seqs[FALL] = 1;
        animations[2].default_seqs[WALK] = 2;
        animations[2].default_seqs[JUMP] = 3;
        animations[2].default_seqs[ATTACK] = 4;
        animations[2].default_seqs[GET_ATTACKED] = 5;
        animations[2].default_seqs[BLOCK] = 6;
        animations[2].default_seqs[WALK_BACK] = 7;
        animations[2].default_seqs[JUMP_BACK] = 3;
        animations[2].default_seqs[PARRY] = 6;
        animations[2].default_seqs[CROUCH] = 9;

        animations[2].transition_table[ATTACK][4] = 8;//second attack sequence, chain attack after first attack connects
        animations[2].transition_table[ATTACK][3] = 10;//jump attack
        */
        /*
        //idle frames
        animations[2].frames[0][0].x = 0;animations[2].frames[0][0].y = 0;animations[2].frames[0][0].active = 1;

        //walk frames
        animations[2].frames[2][0].x = 80*4;animations[2].frames[2][0].y = 0;animations[2].frames[2][0].active = 1;
        animations[2].frames[2][1].x = 80*5;animations[2].frames[2][1].y = 0;animations[2].frames[2][1].active = 1;
        animations[2].frames[2][2].x = 80*6;animations[2].frames[2][2].y = 0;animations[2].frames[2][2].active = 1;
        animations[2].frames[2][3].x = 80*7;animations[2].frames[2][3].y = 0;animations[2].frames[2][3].active = 1;

        //walk back
        animations[2].frames[7][3].x = 80*4;animations[2].frames[7][3].y = 0;animations[2].frames[7][3].active = 1;
        animations[2].frames[7][2].x = 80*5;animations[2].frames[7][2].y = 0;animations[2].frames[7][2].active = 1;
        animations[2].frames[7][1].x = 80*6;animations[2].frames[7][1].y = 0;animations[2].frames[7][1].active = 1;
        animations[2].frames[7][0].x = 80*7;animations[2].frames[7][0].y = 0;animations[2].frames[7][0].active = 1;


        //jump frames
        animations[2].frames[3][0].x = 80*1;animations[2].frames[3][0].y = 80*6;animations[2].frames[3][0].active = 1;
        animations[2].frames[3][1].x = 80*2;animations[2].frames[3][1].y = 80*6;animations[2].frames[3][1].active = 1;


        //fall frames
        animations[2].frames[1][0].x = 160;animations[2].frames[1][0].y = 320;animations[2].frames[1][0].active = 1;

        //attack frames
        animations[2].frames[4][0].x = 0;animations[2].frames[4][0].y = 80;animations[2].frames[4][0].active = 1;
        animations[2].frames[4][1].x = 80;animations[2].frames[4][1].y = 80;animations[2].frames[4][1].active = 1;animations[2].frames[4][1].data = 1;
        animations[2].frames[4][2].x = 160;animations[2].frames[4][2].y = 80;animations[2].frames[4][2].active = 1;

        //attack 2 frames
        animations[2].frames[8][0].x = 0;animations[2].frames[8][0].y = 160;animations[2].frames[8][0].active = 1;
        animations[2].frames[8][1].x = 80;animations[2].frames[8][1].y = 160;animations[2].frames[8][1].active = 1;animations[2].frames[8][2].data = 2;
        animations[2].frames[8][2].x = 80*2;animations[2].frames[8][2].y = 160;animations[2].frames[8][2].active = 1;
        animations[2].frames[8][3].x = 80*3;animations[2].frames[8][3].y = 160;animations[2].frames[8][3].active = 1;
        animations[2].frames[8][4].x = 80*4;animations[2].frames[8][4].y = 160;animations[2].frames[8][4].active = 1;


        //jump attack
        animations[2].frames[10][0].x = 80*3;animations[2].frames[10][0].y = 320;animations[2].frames[10][0].active = 1;
        animations[2].frames[10][1].x = 80*4;animations[2].frames[10][1].y = 320;animations[2].frames[10][1].active = 1;animations[2].frames[10][1].data = 3;
        animations[2].frames[10][2].x = 80*5;animations[2].frames[10][2].y = 320;animations[2].frames[10][2].active = 1;


        //crouch frames
        animations[2].frames[9][0].x = 80;animations[2].frames[9][0].y = 0;animations[2].frames[9][0].active = 1;
        animations[2].frames[9][1].x = 160;animations[2].frames[9][1].y = 0;animations[2].frames[9][1].active = 1;

         //get attacked
        animations[2].frames[5][0].x = 0;animations[2].frames[5][0].y = 320;animations[2].frames[5][0].active = 1;
        animations[2].frames[5][1].x = 80;animations[2].frames[5][1].y = 320;animations[2].frames[5][1].active = 1;
        animations[2].frames[5][2].x = 80;animations[2].frames[5][3].y = 320;animations[2].frames[5][2].active = 1;
        animations[2].frames[5][3].x = 80;animations[2].frames[5][2].y = 320;animations[2].frames[5][3].active = 1;

        //block
        animations[2].frames[6][0].x = 160;animations[2].frames[6][0].y = 80;animations[2].frames[6][0].active = 1;
        animations[2].frames[6][1].x = 160;animations[2].frames[6][1].y = 80;animations[2].frames[6][1].active = 1;
        animations[2].frames[6][2].x = 160;animations[2].frames[6][2].y = 80;animations[2].frames[6][2].active = 1;

*/
         //attacks
        /*animations[2].attacks[0].damage = 2;
        animations[2].attacks[0].target_dx = 0.7;
        animations[2].attacks[0].x = 20;
        animations[2].attacks[0].y = 0;
        animations[2].attacks[0].width = 60;
        animations[2].attacks[0].height = 20;
*/
/*        animations[2].attacks[1].damage = 2;
        animations[2].attacks[1].target_dx = 3;
        animations[2].attacks[1].x = 20;
        animations[2].attacks[1].y = 0;
        animations[2].attacks[1].width = 80;
        animations[2].attacks[1].height = 20;



        animations[2].attacks[2].damage = 2;
        animations[2].attacks[2].target_dx = 3;
        animations[2].attacks[2].x = 20;
        animations[2].attacks[2].y = 0;
        animations[2].attacks[2].width = 80;
        animations[2].attacks[2].height = 20;*/
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
        s_physics();
        s_game_player_logic();

        s_render_total();

        prog.delta_time = (double)((NOW - LAST)/ (double)SDL_GetPerformanceFrequency() );//temporary until a fix is found
        if(prog.delta_time > 1.0/prog.fps)prog.delta_time = 1.0/prog.fps;

        s_cap_framerate(&then, &remaining_time, prog.fps);
        printf("%d %d \r", entities[0].hp,  entities[1].hp);

    }


    deinit();
	return 0;
}




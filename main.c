#include "common.h"

#include "init.h"
#include "render.h"
#include "input.h"
#include "game.h"

void init();
void deinit();



int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    prog.fps = 60;
    sdl_init();

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();

    while(1){

        s_render_prepare();
        s_input();
        s_render_present();

        s_cap_framerate(&then, &remaining_time);
    }

    sdl_deinit();
	return 0;
}




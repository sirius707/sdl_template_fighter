#include "common.h"

#include "init.h"
#include "render.h"

void init();
void deinit();



int main( int argc, char* args[] )
{
    memset(&prog, 0, sizeof(PROGRAM));
    sdl_init();

    while(1){

        render_prepare();
        render_present();
        SDL_Delay(16);
    }

    sdl_deinit();
	return 0;
}




#include "init.h"
#include "render.h"

void init()
{
    s_render_init();
    sdl_init();
    prog.fps = 60;
    prog.enum_game_state = RUNNING;
}

void deinit()
{
    sdl_deinit();
}

void sdl_init()
{

	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	prog.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, windowFlags);

	if (!prog.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_W, SCREEN_H, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	prog.renderer = SDL_CreateRenderer(prog.window, -1, rendererFlags);

	if (!prog.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void sdl_deinit()
{
    SDL_DestroyRenderer(prog.renderer);
	SDL_DestroyWindow(prog.window);
	SDL_Quit();
}

#include "input.h"

inline void s_key_up(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		prog.keyboard[event->keysym.scancode] = 0;
	}
}

inline void s_key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		prog.keyboard[event->keysym.scancode] = 1;
	}
}

void s_input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				s_key_down(&event.key);
				break;

			case SDL_KEYUP:
				s_key_up(&event.key);
				break;

			default:
				break;
		}
	}
}

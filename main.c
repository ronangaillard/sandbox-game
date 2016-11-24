#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")

#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "graphics.h"
#include "mouse.h"
#include "blocks_handler.h"
#include "ui.h"

SDL_Surface *screen;


//#undef main

int SDL_main(int argc, char **argv)
{
	int keep_going = 1;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) 
	{
		fprintf(stderr, "Cannot init SDL : %s\n", SDL_GetError()); 
		exit(EXIT_FAILURE); 
	}

	screen = SDL_SetVideoMode(SCREEN_W*SCALE_FACTOR, SCREEN_H*SCALE_FACTOR, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Sandbox Game", NULL);

	

	SDL_Event event;

	
	printf("Hello from Nios II!\n");
	erase_video_ram();

	init_mouse();

	draw_main_ui();
	init_screen();

	SDL_ShowCursor(SDL_DISABLE);


	while (keep_going)
	{
		SDL_PollEvent(&event);

		/* If a quit event has been sent */
		if (event.type == SDL_QUIT)
		{
			keep_going = 0;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{

			if (event.button.button == SDL_BUTTON_LEFT)
				mouse_follow(1, 0, event.motion.x / SCALE_FACTOR, event.motion.y / SCALE_FACTOR);

		}

		if (event.type == SDL_MOUSEMOTION)
		{
			printf("movement x : %d y : %d\n", event.motion.x , event.motion.y);
			if(event.button.button == SDL_BUTTON_LEFT)
				mouse_follow(1, 0, event.motion.x / SCALE_FACTOR, event.motion.y / SCALE_FACTOR);
			else
				mouse_follow(0, 0, event.motion.x / SCALE_FACTOR, event.motion.y / SCALE_FACTOR);
		}

		update_screen();
		SDL_Flip(screen);

		read_and_decode();

		animate_world();
	}

	


	SDL_Quit(); 

	return 0;
}

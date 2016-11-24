/*
 * graphics.c
 *
 *  Created on: 18 nov. 2016
 *      Author: codron_gui
 */

#include "graphics.h"
#include "blocks_handler.h"

#include <SDL.h>

extern SDL_Surface *screen;
SDL_Rect PIXELRect;
Uint32 sdl_color = 0;


extern unsigned char screen_table[SCREEN_W][SCREEN_H];
void erase_video_ram()
{
	int i = 0;

	
}


void pixel_on(int x, int y, int color){
	int i = 0;
	

	PIXELRect.h = SCALE_FACTOR;
	PIXELRect.w = SCALE_FACTOR;
	PIXELRect.x = x*SCALE_FACTOR;
	PIXELRect.y = y*SCALE_FACTOR;

	
	switch (color)
	{
	case COLOR_BEIGE:
		sdl_color = SDL_MapRGB(screen->format, 255, 223, 113);
		break;
	case COLOR_BLACK:
		sdl_color = SDL_MapRGB(screen->format, 0, 0, 0);
		break;
	case COLOR_BLUE:
		sdl_color = SDL_MapRGB(screen->format, 29, 81, 201);
		break;
	case COLOR_BROWN:
		sdl_color = SDL_MapRGB(screen->format, 128, 64, 0);
		break;
	case COLOR_GREEN:
		sdl_color = SDL_MapRGB(screen->format, 26, 189, 30);
		break;
	case COLOR_GREY:
		sdl_color = SDL_MapRGB(screen->format, 192, 192, 192);
		break;
	case COLOR_ORANGE:
		sdl_color = SDL_MapRGB(screen->format, 254, 136, 29);
		break;
	case COLOR_WHITE:
		sdl_color = SDL_MapRGB(screen->format, 255, 255, 255);
		break;
	}

	SDL_FillRect(screen, &PIXELRect, sdl_color);

	
	

}

void draw_rectangle(int x, int y, int width, int height, char color)
{
	int i = 0;

	for(i = x; i <= x + width; i++)
	{
		pixel_on(i, y, color);
		pixel_on(i, y + height, color);
		screen_table[i][y] = color;
		screen_table[i][y + height] = color;
	}

	for(i = y; i <= y + height; i++)
	{
		pixel_on(x, i, color);
		pixel_on(x + width, i, color);
		screen_table[x][i] = color;
		screen_table[x + width][i] = color;
	}
}

void draw_rectangle_filled(int x, int y, int width, int height, char color)
{
	int i, j = 0;

	for(i = x; i <= x + width; i++)
		for(j = y; j <= y + height; j++)
		{
			pixel_on(i, j, color);
			screen_table[i][j] = color;
		}
}





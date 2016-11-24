/*
 * graphics.h
 *
 *  Created on: 18 nov. 2016
 *      Author: codron_gui
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define SCREEN_W 640/2
#define SCREEN_H 480/2
#define SCREEN_SIZE SCREEN_W*SCREEN_H

#define COLOR_BLACK	0
/* For retrocompatibility*/
#define COLOR_RED	1
#define COLOR_ORANGE	1
#define COLOR_WHITE 2
#define COLOR_BLUE	3
#define COLOR_GREEN	4
#define COLOR_BEIGE	5
/* For retrocompatibility*/
#define COLOR_YELLOW	5
#define COLOR_GREY	6
#define COLOR_BROWN	7

#define SCALE_FACTOR 5



void erase_video_ram();
void pixel_on(int x, int y, int color);

void draw_rectangle(int x, int y, int width, int height, char color);
void draw_rectangle_filled(int x, int y, int width, int height, char color);

#endif /* GRAPHICS_H_ */

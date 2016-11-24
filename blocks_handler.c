/*
 * blocks_handler.c
 *
 *  Created on: 21 nov. 2016
 *      Author: gaillard_ron
 */



#include "blocks_handler.h"
#include "graphics.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct linked_list
{
	int x;
	int y;
	char color;
	struct linked_list* next_element;
} linked_list;

typedef struct dir{
	int x;
	int y;
} dir;

int current_line = GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT;

unsigned char toggle_bit = 0;

unsigned char odd_frame = 255;

unsigned char blocks_list[NUMBER_OF_BLOCKS] = {COLOR_ORANGE, COLOR_BLUE, COLOR_GREEN, COLOR_BEIGE, COLOR_GREY, COLOR_BROWN, COLOR_BLACK};

unsigned char screen_table[SCREEN_W][SCREEN_H] = {0}; // 8 bits: les 3 bits de poids faible correspondent à la couleur

dir dirs[4] = {{.x=0,.y=-1},{.x=0,.y=1},{.x=-1,.y=0},{.x=1,.y=0}};

linked_list* last_element = NULL;
linked_list* first_element = NULL;

void init_elements(){
	first_element = NULL;
	last_element = NULL;
}
void init_screen()
{
	int x, y;
	for(x = GAME_ZONE_WIDTH_OFFSET+1; x < GAME_ZONE_WIDTH + GAME_ZONE_WIDTH_OFFSET;x++){
		for(y = GAME_ZONE_HEIGHT_OFFSET+1; y < GAME_ZONE_HEIGHT + GAME_ZONE_HEIGHT_OFFSET;y++){
			screen_table[x][y] = COLOR_BLACK;
			pixel_on(x, y, COLOR_BLACK);
		}
	}
}

void update_screen()
{
	while(first_element && first_element->next_element){
		//printf("updating (%d, %d)\n",first_element->x,first_element->y);
		pixel_on(first_element->x,first_element->y, first_element->color);
		linked_list* tmp = first_element;
		first_element = first_element->next_element;
		free(tmp);
	}
	if(first_element){
		pixel_on(first_element->x,first_element->y, first_element->color);
		free(first_element);
	}
	init_elements();
}

void update_pixel(int x,int y,char state)
{
	screen_table[x][y] = state;
	update_pixel_no_save(x, y, state);
}

void update_pixel_no_save(int x,int y,char state)
{
	linked_list* tmp = malloc(sizeof(linked_list));
	tmp->x = x;
	tmp->y = y;
	tmp->color = COLOR_MASK & state;
	tmp->next_element = NULL;
	if(first_element == NULL){
		first_element = tmp;
		last_element = tmp;
	}else{
		last_element->next_element = tmp;
		last_element = last_element->next_element;
	}
}

void animate_world()
{
	int x, y, ran, i, k;
	int test_feu = 0;
	int test_wood = 0;
	char tmp;
	for (current_line = GAME_ZONE_HEIGHT_OFFSET + 1; current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT; current_line++)
	{
		for (x = GAME_ZONE_WIDTH_OFFSET + 1; x < GAME_ZONE_WIDTH_OFFSET + GAME_ZONE_WIDTH; x++)
		{
			if ((YET_UPDATED(screen_table[x][current_line])))
				continue;
			/*
			if((screen_table[x][current_line] & COLOR_MASK) == COLOR_BEIGE)
				printf("screen x y before : %d\n",screen_table[x][current_line]);
			if((screen_table[x][current_line] & COLOR_MASK) == COLOR_BEIGE)
				printf("screen x y after : %d\n",screen_table[x][current_line]);
			 */
			UPDATE_FRAME_BIT(screen_table[x][current_line]);
			// SAND Condition
			if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_BLACK || (screen_table[x][current_line] & COLOR_MASK) == COLOR_GREY) {

			}
			else if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_BEIGE && current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT)
			{
				if (((screen_table[x][current_line + 1] & COLOR_MASK) == COLOR_BLACK || (screen_table[x][current_line + 1] & COLOR_MASK) == COLOR_BLUE) && is_in_game_area(x, current_line + 1))
				{
					tmp = screen_table[x][current_line];
					update_pixel(x, current_line, screen_table[x][current_line + 1]);
					update_pixel(x, current_line + 1, tmp);
				}
				else if (toggle_bit == 0)
				{
					if ((screen_table[x + 1][current_line] & COLOR_MASK) == COLOR_BLACK && (screen_table[x + 1][current_line + 1] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x + 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					else if ((screen_table[x - 1][current_line] & COLOR_MASK) == COLOR_BLACK && (screen_table[x - 1][current_line + 1] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x - 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					toggle_bit = 1;
				}
				else
				{
					if ((screen_table[x - 1][current_line] & COLOR_MASK) == COLOR_BLACK && (screen_table[x - 1][current_line + 1] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x - 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					else if ((screen_table[x + 1][current_line] & COLOR_MASK) == COLOR_BLACK && (screen_table[x + 1][current_line + 1] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x + 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					toggle_bit = 0;
				}
			}
			// WATER condition
			else if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_BLUE && current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT - 1)/* Water*/
			{
				//ran = rand();

				if ((screen_table[x][current_line + 1] & COLOR_MASK) == COLOR_BLACK)
				{
					update_pixel(x, current_line + 1, screen_table[x][current_line]);
					update_pixel(x, current_line, COLOR_BLACK);
				}
				else if (toggle_bit == 0 && is_in_game_area(x + 1, current_line))
				{
					if ((screen_table[x + 1][current_line] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x + 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					else if ((screen_table[x - 1][current_line] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x - 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					toggle_bit = 1;
				}
				else if (is_in_game_area(x + 1, current_line))
				{
					if ((screen_table[x - 1][current_line] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x - 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					else if ((screen_table[x + 1][current_line] & COLOR_MASK) == COLOR_BLACK)
					{
						update_pixel(x + 1, current_line, screen_table[x][current_line]);
						update_pixel(x, current_line, COLOR_BLACK);
					}
					toggle_bit = 0;
				}

				for (i = 0; i < 4; i++) {
					if ((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_ORANGE)
					{
						update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_BLACK));
					}
				}
			}
			// Forest Condition
			else if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_GREEN && current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT)/* Trees*/
			{
				ran = rand();
				for (i = 0; i < 4; i++) {
					if ((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_BLUE ||
						((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_BLACK &&
						((ran < RAND_MAX / 10 && i == 0) || (ran < RAND_MAX / 1000 && i == 1) || (ran < RAND_MAX / 100 && i >1))))
					{
						if (is_in_game_area(x + dirs[i].x, current_line + dirs[i].y)) {
							if (i == 1)
								update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_BROWN));
							else
								update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_GREEN));
						}

					}
				}

			}
			// Wood Condition
			else if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_BROWN && current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT)/* Trees*/
			{
				ran = rand();
				for (i = 0; i < 4; i++) {
					if ((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_BLUE ||
						((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_BLACK &&
						((ran < RAND_MAX / 50 && i == 1) || (ran < RAND_MAX / 5000 && i == 0) || (ran < RAND_MAX / 500 && i >1))))
					{
						if (is_in_game_area(x + dirs[i].x, current_line + dirs[i].y)) {
							if (i == 0)
								update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_GREEN));
							else {
								test_wood = 0;
								for (k = 0; k < 4; k++) {
									test_wood += (screen_table[x + dirs[i].x + dirs[k].x][current_line + dirs[i].y + dirs[k].y] & COLOR_MASK) == COLOR_BROWN;
								}
								if (test_wood < 3)
									update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_BROWN));
							}
						}

					}
				}

			}
			// Fire condition
			else if ((screen_table[x][current_line] & COLOR_MASK) == COLOR_ORANGE && current_line < GAME_ZONE_HEIGHT_OFFSET + GAME_ZONE_HEIGHT)/* Fire*/
			{
				test_feu = 0;
				ran = rand();
				if (ran < RAND_MAX / 3)
					continue;
				for (i = 0; i < 4; i++) {
					if ((screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_GREEN || (screen_table[x + dirs[i].x][current_line + dirs[i].y] & COLOR_MASK) == COLOR_BROWN)
					{
						update_pixel(x + dirs[i].x, current_line + dirs[i].y, INIT_FRAME_BIT(COLOR_ORANGE));
						test_feu++;
					}
				}
				if (test_feu == 0)
					update_pixel(x, current_line, COLOR_BLACK);
			}


		}
	}

	
	odd_frame = odd_frame ^ FRAME_BIT;
	
}



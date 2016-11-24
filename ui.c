/*
 * ui.c
 *
 *  Created on: 21 nov. 2016
 *      Author: gaillard_ron
 */


#include "ui.h"
#include "blocks_handler.h"
#include "graphics.h"

extern char blocks_list[NUMBER_OF_BLOCKS];
extern unsigned char odd_frame;
int current_selected_block = 0;


void draw_main_ui()
{
	int i,j = 0;

	/* draw game border*/
	draw_rectangle(GAME_ZONE_WIDTH_OFFSET, GAME_ZONE_HEIGHT_OFFSET, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT, COLOR_WHITE);

	/* draw blocks that can be selected by mouse */
	/* draw borders */
	for(i = 0; i < NUMBER_OF_BLOCKS; i++)
	{
		draw_rectangle(SELECTABLE_BLOCK_X_POS, ALL_BLOCKS_Y_OFFSET + i * (SELECTABLE_BLOCKS_SIZE + SPACE_BETWEEN_BLOCKS), SELECTABLE_BLOCKS_SIZE, SELECTABLE_BLOCKS_SIZE, COLOR_WHITE);
		draw_rectangle_filled(SELECTABLE_BLOCK_X_POS + 1, ALL_BLOCKS_Y_OFFSET + i * (SELECTABLE_BLOCKS_SIZE + SPACE_BETWEEN_BLOCKS) + 1, SELECTABLE_BLOCKS_SIZE - 2, SELECTABLE_BLOCKS_SIZE - 2, blocks_list[i]);

		/* Highlight current selected block */
		if(current_selected_block == i)
			draw_rectangle(SELECTABLE_BLOCK_X_POS-1, ALL_BLOCKS_Y_OFFSET + i * (SELECTABLE_BLOCKS_SIZE + SPACE_BETWEEN_BLOCKS) -1, SELECTABLE_BLOCKS_SIZE + 2, SELECTABLE_BLOCKS_SIZE + 2, COLOR_WHITE);
		else
			draw_rectangle(SELECTABLE_BLOCK_X_POS-1, ALL_BLOCKS_Y_OFFSET + i * (SELECTABLE_BLOCKS_SIZE + SPACE_BETWEEN_BLOCKS) -1, SELECTABLE_BLOCKS_SIZE + 2, SELECTABLE_BLOCKS_SIZE + 2, COLOR_BLACK);
	}



}

void handle_mouse_click(int x, int y)
{
	int i = 0;

	/* Let's check if mouse is in selectable block */
	for(i = 0; i < NUMBER_OF_BLOCKS; i++)
	{
		if(is_in_rectangle(x, y, SELECTABLE_BLOCK_X_POS, ALL_BLOCKS_Y_OFFSET + i * (SELECTABLE_BLOCKS_SIZE + SPACE_BETWEEN_BLOCKS), SELECTABLE_BLOCKS_SIZE, SELECTABLE_BLOCKS_SIZE))
		{
			current_selected_block = i;
			if (current_selected_block == NUMBER_OF_BLOCKS - 1){
				init_screen();
			}
			draw_main_ui();
			break;
		}
	}
	if (is_in_rectangle(x, y, GAME_ZONE_WIDTH_OFFSET, GAME_ZONE_HEIGHT_OFFSET, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT)){
		update_pixel(x, y, blocks_list[current_selected_block]);
	}

}

/* Tells if (x, y) coordinate is within given rectangle
 * Returns	1 if true
 * 			0 if false */
char is_in_rectangle(int x, int y, int x_rect, int y_rect, int width_rect, int height_rect)
{
	if(x >= x_rect && x <= x_rect + width_rect && y >= y_rect && y <= y_rect + height_rect)
		return 1;

	return 0;
}

/* Tells if (x, y) coordinate is within game area
 * Returns	1 if true
 * 			0 if false */
char is_in_game_area(int x, int y)
{
	return is_in_rectangle(x, y, GAME_ZONE_WIDTH_OFFSET, GAME_ZONE_HEIGHT_OFFSET, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT);
}

/* Tells if (x, y) coordinate is outside of given rectangle
 * Returns	1 if true
 * 			0 if false */
char is_out_of_rectangle(int x, int y, int x_rect, int y_rect, int width_rect, int height_rect)
{
	if((x <= x_rect || x >= x_rect + width_rect) || (y <= y_rect || y >= y_rect + height_rect))
		return 1;

	return 0;
}


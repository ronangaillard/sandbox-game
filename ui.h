/*
 * ui.h
 *
 *  Created on: 21 nov. 2016
 *      Author: gaillard_ron
 */

#ifndef UI_H_
#define UI_H_

#define GAME_ZONE_WIDTH	540/2
#define GAME_ZONE_HEIGHT 470/2
#define GAME_ZONE_WIDTH_OFFSET	2
#define GAME_ZONE_HEIGHT_OFFSET	2


#define SELECTABLE_BLOCKS_SIZE	8
#define SELECTABLE_BLOCK_X_POS	 GAME_ZONE_WIDTH + GAME_ZONE_WIDTH_OFFSET + (SCREEN_W - GAME_ZONE_WIDTH - GAME_ZONE_WIDTH_OFFSET - SELECTABLE_BLOCKS_SIZE) / 2
#define SPACE_BETWEEN_BLOCKS	8
#define ALL_BLOCKS_Y_OFFSET		10

void draw_main_ui();

void draw_mouse(int x, int y);

void handle_mouse_click(int x, int y);

char is_in_rectangle(int x, int y, int x_rect, int y_rect, int width_rect, int height_rect);
char is_in_game_area(int x, int y);
char is_out_of_rectangle(int x, int y, int x_rect, int y_rect, int width_rect, int height_rect);


#endif /* UI_H_ */

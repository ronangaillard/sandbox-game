/*
 * mouse.c
 *
 *  Created on: 17 nov. 2016
 *      Author: codron_gui
 */

#include "mouse.h"
#include "debug.h"
#include "graphics.h"
#include "blocks_handler.h"
#include "ui.h"



//unsigned char packets[3];
int packet_position = 0;

float mouse_position_x = 150;
float mouse_position_y = 150;
int previous_mouse_position_x = 150;
int previous_mouse_position_y = 150;

extern char screen_table[SCREEN_W][SCREEN_H];

int send_command(char command)
{
	return 1;
}

int send_command_with_ack(char command)
{
	return 0;
}

int read_data(unsigned char *data)
{
	
	return 0;
}

int read_data_non_blocking(unsigned char *data)
{
	DEBUG
	return 0;
}
int read_data_timeout(unsigned char *data)
{
	return 0;
}

int init_mouse()
{

	return 0;
}

int read_and_decode()
{


//	mouse_follow(left_click, right_click, x_move, y_move);

	return 0;
}

void mouse_follow(char left_click, char right_click, int x_move, int y_move)
{
	int toggle = 0;
	mouse_position_x = x_move;
	mouse_position_y = y_move;


	if(mouse_position_x > SCREEN_W-1)
		mouse_position_x = SCREEN_W-1;

	if(mouse_position_x < 0)
		mouse_position_x = 0;

	if(mouse_position_y > SCREEN_H)
		mouse_position_y = SCREEN_H;

	if(mouse_position_y < 1)
		mouse_position_y = 1;

	if(previous_mouse_position_x != (int)mouse_position_x || previous_mouse_position_y != (int)mouse_position_y)
	{


		update_pixel(previous_mouse_position_x, previous_mouse_position_y, screen_table[previous_mouse_position_x][previous_mouse_position_y]);
		update_pixel(previous_mouse_position_x+1, previous_mouse_position_y, screen_table[previous_mouse_position_x+1][previous_mouse_position_y]);
		update_pixel(previous_mouse_position_x-1, previous_mouse_position_y, screen_table[previous_mouse_position_x-1][previous_mouse_position_y]);
		update_pixel(previous_mouse_position_x, previous_mouse_position_y+1, screen_table[previous_mouse_position_x][previous_mouse_position_y+1]);
		update_pixel(previous_mouse_position_x, previous_mouse_position_y-1, screen_table[previous_mouse_position_x][previous_mouse_position_y-1]);
		/* Redraw UI if mouse might be above */
		if(is_out_of_rectangle(mouse_position_x, mouse_position_y, GAME_ZONE_WIDTH_OFFSET, GAME_ZONE_HEIGHT_OFFSET, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT))
			draw_main_ui();


		update_pixel_no_save((int)mouse_position_x-1, (int)mouse_position_y, COLOR_WHITE);
		update_pixel_no_save((int)mouse_position_x+1, (int)mouse_position_y, COLOR_WHITE);
		update_pixel_no_save((int)mouse_position_x, (int)mouse_position_y+1, COLOR_WHITE);
		update_pixel_no_save((int)mouse_position_x, (int)mouse_position_y-1, COLOR_WHITE);

	}

	if(left_click == 1)//draw a continuous line from previous mouse position to current
	{
		toggle = 0;

		do{
			if (toggle == 0)
				previous_mouse_position_x += (previous_mouse_position_x < (int)mouse_position_x) - ((int)mouse_position_x < previous_mouse_position_x);
			else
				previous_mouse_position_y += (previous_mouse_position_y < (int)mouse_position_y) - ((int)mouse_position_y < previous_mouse_position_y);
			toggle ^= 1;
			handle_mouse_click(previous_mouse_position_x, previous_mouse_position_y);
		} while(previous_mouse_position_x != (int)mouse_position_x || previous_mouse_position_y != (int)mouse_position_y);

	}else if (right_click == 1) {
		toggle = 0;
		do{
			if (toggle == 0)
				previous_mouse_position_x += (previous_mouse_position_x < (int)mouse_position_x) - ((int)mouse_position_x < previous_mouse_position_x);
			else
				previous_mouse_position_y += (previous_mouse_position_y < (int)mouse_position_y) - ((int)mouse_position_y < previous_mouse_position_y);
			toggle ^= 1;
			update_pixel(mouse_position_x, mouse_position_y,COLOR_BLACK);
		} while(previous_mouse_position_x != (int)mouse_position_x || previous_mouse_position_y != (int)mouse_position_y);

	} else{
		previous_mouse_position_x = (int)mouse_position_x;
		previous_mouse_position_y = (int)mouse_position_y;
		pixel_on(previous_mouse_position_x, previous_mouse_position_y, COLOR_BLACK);
	}


}





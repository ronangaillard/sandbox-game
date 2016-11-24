/*
 * mouse.h
 *
 *  Created on: 17 nov. 2016
 *      Author: codron_gui
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#define MOU_RESET 0xFF
#define MOU_ENABLE 0xF4
#define MOU_STREAM_MODE 0xEA
#define MOU_REMOTE_MODE 0xF0
#define MOU_SCALING_1_1 230
#define MOU_GET_PACKET	0xEB
#define MOU_SET_RESOLUTION	0xE8
#define MOU_GET_STATUS	0xE9
#define TIMEOUT	10000
#define MOUSE_SPEED_DIVIDER		10.0f

#define DATA_REG	250


int init_mouse();
int read_data(unsigned char *data);
int read_data_non_blocking(unsigned char *data);
int read_data_timeout(unsigned char *data);
int send_command(char command);
int send_command_with_ack(char command);
int read_and_decode();
void mouse_follow(char left_click, char right_click, int x_move, int y_move);




#endif /* MOUSE_H_ */

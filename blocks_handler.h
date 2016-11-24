/*
 * blocks_handler.h
 *
 *  Created on: 21 nov. 2016
 *      Author: gaillard_ron
 */

#ifndef BLOCKS_HANDLER_H_
#define BLOCKS_HANDLER_H_

#define NUMBER_OF_BLOCKS	7
#define COLOR_MASK 7

#define FRAME_BIT	8

void init_screen();
void update_screen();
void update_pixel(int x,int y,char state);
void update_pixel_no_save(int x,int y,char state);

void animate_world();

#define UPDATE_FRAME_BIT(block) block = (block ^ FRAME_BIT )
#define INIT_FRAME_BIT(block) (block ^ (~odd_frame ^ FRAME_BIT))
#define YET_UPDATED(block) ((unsigned char)((block & (unsigned char)FRAME_BIT) ^ (~odd_frame)) != 0 )

#endif /* BLOCKS_HANDLER_H_ */

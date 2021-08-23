/*
 * s_frame.h
 *
 *  Created on: 23 Aout 2021
 *      Author: Luc
 */

#ifndef APP_INC_S_FRAME_H_
#define APP_INC_S_FRAME_H_

#include <stdint.h>

typedef enum {
	frameSlaveInquiry,
	frameBroadcastOrder,
	frameSlaveRequest,
	frameSlaveData,
	frameNoRequest
}frameTypeEnum;

typedef struct {
	uint8_t idCalled; 				// id of expected receiver
	frameTypeEnum frameType; 		// type of frame
	uint16_t data;					// data to send
} frameField;

void S_Frame_Format(void);

#endif /* APP_INC_S_FRAME_H_ */

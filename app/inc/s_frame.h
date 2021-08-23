/*
 * s_frame.h
 *
 *  Created on: 23 Aout 2021
 *      Author: Luc
 */

#ifndef APP_INC_S_FRAME_H_

#define APP_INC_S_FRAME_H_

typedef enum {
	frameSlaveInquiry,
	frameBroadcastOrder,
	frameSlaveRequest,
	frameSlaveData,
	frameNoRequest
}frame_type_enum;

typedef struct {
	uint8_t idCalled; 				// id of expected receiver
	frame_type_enum frameType; 		// type of frame
	uint16_t data;					// data to send
} frameField;

void S_FrameFormat(void);

#endif /* APP_INC_S_FRAME_H_ */

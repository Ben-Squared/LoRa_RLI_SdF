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


/**
  * @brief  function for formatting frame according to frameType
  * @param  frameType : {frameSlaveRequest, frameSlaveData, frameNoRequest}
  * @retval None
  */
void S_Frame_Format(frameTypeEnum frameType);

#endif /* APP_INC_S_FRAME_H_ */

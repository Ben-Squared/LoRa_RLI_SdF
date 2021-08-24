/*
 * m_frame_format.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_FRAME_H_
#define APP_INC_FRAME_H_

#define MASTER
#undef MASTER		// If commented => MASTER Mode and if uncommented => SLAVE Mode

#ifndef MASTER
#define SLAVE
#endif

#include <stdint.h>


typedef enum {
	frameSlaveInquiry,
	frameBroadcastOrder,
	frameSlaveRequest,
	frameSlaveData,
	frameNoRequest
}frameTypeEnum;


typedef struct {
	uint8_t idCalled; // id of expected receiver
	frameTypeEnum frameType; // type of frame
	uint16_t data;
	// crc ?? mean of frame verif ??? To Be Determined
} frameField;

/**
  * @brief  function for formatting frame according to frameType
  * @param  frameType : {frameSlaveInquiry, frameBroadcastOrder}
  * @retval None
  */
void Frame_Format(frameTypeEnum frameType);

#endif /* APP_INC_FRAME_H_ */

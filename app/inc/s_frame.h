/*
 * s_frame.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_S_FRAME_H_
#define APP_INC_S_FRAME_H_

typedef enum {slave_inquiry, broadcast_order, slave_request, slave_data, no_request
}frame_type_enum;


typedef struct {
	uint8_t idCalled; // id of expected receiver
	frame_type_enum frameType; // type of frame
	uint16_t data;
	// crc ?? mean of frame verif ??? To Be Determined
} frameField;


#endif /* APP_INC_S_FRAME_H_ */

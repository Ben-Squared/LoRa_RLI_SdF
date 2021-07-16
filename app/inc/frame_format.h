/*
 * frame_format.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_FRAME_FORMAT_H_
#define APP_INC_FRAME_FORMAT_H_

typedef enum {slave_inquiry, broadcast_order, slave_request, slave_data, no_request

}frame_type_enum;


typedef struct {
	uint8_t id_called; // id of expected receiver
	frame_type_enum frame_type; // type of frame
	uint16_t data;
	// crc ?? mean of frame verif ??? To Be Determined
} frame_field;


#endif /* APP_INC_FRAME_FORMAT_H_ */

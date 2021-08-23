/*
 * s_frame.c
 *
  *  Created on: 23 Aout 2021
 *      Author: Luc
 */


#include "s_frame.h"

frame_type_enum SFrame;

void S_FrameFormat(void)
{
	/* probably some initialization */
	switch(SFrame){

	case frameSlaveInquiry:
		break;

	case frameBroadcastOrder:
		break;

	case frameSlaveRequest:
		/* switch case cf diagram*/
		break;

	case frameSlaveData:
		break;

	case frameNoRequest:
		break;

	}
}

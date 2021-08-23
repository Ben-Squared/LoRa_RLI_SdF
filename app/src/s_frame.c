/*
 * s_frame.c
 *
  *  Created on: 23 Aout 2021
 *      Author: Luc
 */


#include "s_frame.h"

frameTypeEnum frameType;

void S_Frame_Format(void)
{
	/* probably some initialization */
	switch(frameType){

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

	default:
		break;
	}
}

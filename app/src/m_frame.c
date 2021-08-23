/*
 * s_frame.c
 *
  *  Created on: 23 Aout 2021
 *      Author: Benoit
 */


#include "m_frame.h"

frameTypeEnum frameType;

void M_Frame_Format(frameTypeEnum frameType)
{
	/* probably some initialization */
	switch(frameType)
	{
		case frameSlaveInquiry:
			//kikou mettre du code ici
			break;

		case frameBroadcastOrder:
			//kikou mettre du code ici
			break;

		case frameSlaveRequest:
			// nothing to do
			break;

		case frameSlaveData:
			// nothing to do
			break;

		case frameNoRequest:
			//nothing to do
			break;

		default:
			break;
	}
}

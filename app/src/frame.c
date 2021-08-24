/*
 * s_frame.c
 *
  *  Created on: 23 Aout 2021
 *      Author: Benoit
 */


#include <frame.h>

frameTypeEnum frameType;

void Frame_Format(frameTypeEnum frameType)
{
	/* probably some initialization */
	switch(frameType)
	{
#ifdef MASTER
		case frameSlaveInquiry:
			//kikou mettre du code ici
			break;

		case frameBroadcastOrder:
			//kikou mettre du code ici
			break;
#endif

#ifdef SLAVE
		case frameSlaveRequest:
			// nothing to do
			break;

		case frameSlaveData:
			// nothing to do
			break;

		case frameNoRequest:
			//nothing to do
			break;
#endif

		default:
			break;
	}
}

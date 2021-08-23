/*
 * s_mef.c
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */


#include "s_mef.h"

StateEnum mefState;


void S_Mef(void)
{
	/* probably some initialization */
	switch(mefState){

	case StateInit:
		break;

	case StateIdle:
		break;

	case StateFrameDecode:
		/* switch case cf diagram*/
		break;

	case StateSendNoRequest:
		break;

	case StateSendSlaveRequest:
		break;

	case StateSendData:
		break;
	}
}

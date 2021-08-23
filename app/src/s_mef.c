/*
 * s_mef.c
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

/*********** defines ***************/
#include "s_mef.h"


/************* Variables *************/
StateEnum mefState;

/************ functions **************/


void S_System_Init(void)
{
	// kikou mettre du code ici
}

void S_Mef(void)
{
	/* probably some initialization */
	switch(mefState){

	case stateInit:
		S_System_Init();
		mefState = stateIdle;
		break;

	case stateIdle:
		break;

	case stateFrameDecode:
		/* switch case cf diagram*/
		break;

	case stateSendNoRequest:
		break;

	case stateSendSlaveRequest:
		break;

	case stateSendData:
		break;
	}
}

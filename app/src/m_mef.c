/*
 * m_mef.c
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

/*************** defines ****************/

#include "m_mef.h"


/****** Variables ***********/
StateEnum mefState;

/********** fonctions declarations ***************/
void M_System_Init(void)
{
	// kikou, mettre du code ici
}

void M_Mef(void)
{
	switch(mefState)
	{
		case stateInit:
			M_System_Init();
			mefState = stateIdle;
			break;

		case stateIdle:
			// wait for periodic interrupt
			break;

		case stateSendSlaveInquiry:
			// kikou mettre du code ici
			mefState = stateWaitForResponse;
			break;

		case stateWaitForResponse:
			/* just wait */
			break;

		case stateFrameDecode:
			/* if noRequest and other station to ask : mefState = stateSendSlaveInquiry, else if no station left : mefState = stateIdle */
			break;

		case stateSendBroadcastOrder:
			break;

		default:
			break;
	}
}

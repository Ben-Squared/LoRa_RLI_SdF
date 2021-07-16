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

	case State_init:
		break;

	case State_Idle:
		break;

	case State_Frame_Decode:
		/* switch case cf diagram*/
		break;

	case State_Send_No_Request:
		break;

	case State_Send_Slave_Request:
		break;

	case State_Send_Data:
		break;
	}
}

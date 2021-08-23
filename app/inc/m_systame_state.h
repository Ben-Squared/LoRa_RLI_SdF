/*
 * m_mef.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_M_SYSTAME_STATE_H_
#define APP_INC_M_SYSTAME_STATE_H_

#include <stdint.h>
#include "frame.h"

typedef enum {
	stateInit,
	stateIdle,
	stateSendSlaveInquiry,
	stateWaitForResponse,
	stateFrameDecode,
	stateSendBroadcastOrder
}StateEnum;


/**
  * @brief  function for initializing the system
  * @param  None
  * @retval None
  */
void M_System_State_Setup(void);

/**
  * @brief  Finite State Machine handler
  * @param  None
  * @retval None
  */
void M_System_State(void);


#endif /* APP_INC_M_SYSTAME_STATE_H_ */



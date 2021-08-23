/*
 * m_mef.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_M_MEF_H_
#define APP_INC_M_MEF_H_

#include <stdint.h>

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
void M_System_Init(void);

/**
  * @brief  Finite State Machine handler
  * @param  None
  * @retval None
  */
void M_Mef(void);


#endif /* APP_INC_M_MEF_H_ */



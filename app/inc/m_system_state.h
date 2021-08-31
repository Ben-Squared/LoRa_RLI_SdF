/*
 * m_mef.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_M_SYSTEM_STATE_H_
#define APP_INC_M_SYSTEM_STATE_H_

#include <stdint.h>
#include "frame.h"

typedef enum {
	stateInit,
	stateIdle,
	stateSendSlaveInquiry,
	stateWaitForResponse,
	stateFrameDecode,
	stateSendBroadcastOrder,
	stateOtherStationLeft
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

/**
  * @brief  function for sending the frame
  * @param  the frame to send
  * @retval None
  */
void M_Transmit(uint8_t frame[4]);

/**
  * @brief  function for receive the frame
  * @param  the array which will contains the new frame received
  * @retval the frame received
  */
uint8_t* M_Receive(uint8_t frame[4]);

#endif /* APP_INC_M_SYSTEM_STATE_H_ */


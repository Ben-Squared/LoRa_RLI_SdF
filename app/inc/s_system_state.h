/*
 * s_mef.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_S_SYSTEM_STATE_H_
#define APP_INC_S_SYSTEM_STATE_H_

#include <stdint.h>

typedef enum {
	stateInit,
	stateIdle,
	stateFrameDecode,
	stateSendNoRequest,
	stateSendSlaveRequest,
	stateSendData,
}StateEnum;

/**
  * @brief  function for initializing the system
  * @param  None
  * @retval None
  */
void S_System_State_Setup(void);

/**
  * @brief  Finite State Machine handler
  * @param  None
  * @retval None
  */
void S_System_State(void);

/**
  * @brief  Transmit function for slave
  * @param  frame to send
  * @retval None
  */
void S_Transmit(uint8_t frame[4]);

/**
  * @brief  Receive function for slave
  * @param  array who will contains the new frame received
  * @retval the frame received
  */
uint8_t* S_Receive(uint8_t frame[4]);

#endif /* APP_INC_S_SYSTEM_STATE_H_ */



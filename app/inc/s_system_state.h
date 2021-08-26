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

// TODO : doxygen
void S_Transmit(uint8_t frame[4]);

// TODO : doxygen
uint8_t* S_Receive(uint8_t frame[4]);

#endif /* APP_INC_S_SYSTEM_STATE_H_ */



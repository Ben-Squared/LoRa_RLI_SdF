/*
 * s_mef.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_S_MEF_H_
#define APP_INC_S_MEF_H_

typedef enum {
	State_init,
	State_Idle,
	State_Frame_Decode,
	State_Send_No_Request,
	State_Send_Slave_Request,
	State_Send_Data,
}StateEnum;

/**
  * @brief  function for initializing the system
  * @param  None
  * @retval None
  */
void S_System_Init(void);

/**
  * @brief  Finite State Machine handler
  * @param  None
  * @retval None
  */
void S_Mef(void);

#endif /* APP_INC_S_MEF_H_ */



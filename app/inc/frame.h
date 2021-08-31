/*
 * m_frame_format.h
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

#ifndef APP_INC_FRAME_H_
#define APP_INC_FRAME_H_

#define MASTER
#undef MASTER		// If commented => MASTER Mode and if uncommented => SLAVE Mode

#ifndef MASTER
#define SLAVE
#endif

/* addresses defines */
#define MASTER_ADDRESS		0xFE
#define STATION_1_ADDRESS	0x01
#define STATION_2_ADDRESS	0x02
#define BROADCAST_ADDRESS	0xFF

#include <stdint.h>

/*
typedef enum {
	masterAddress,
	stationAddress1,
	stationAddress2,
}; */

typedef enum {
	frameSlaveInquiry,
	frameBroadcastOrder,
	frameSlaveRequest,
	frameSlaveData,
	frameNoRequest,
	lastElement, // convenience purpose
	frameDiscovery // for future : if we add a node, this frame will allow to add the address to a list (not done yet)
}frameTypeEnum;


typedef struct {
	uint8_t idCalled; // id of expected receiver
	frameTypeEnum frameType; // type of frame
	uint16_t data;
} frameField;

/**
  * @brief  function for formatting frame according to frameType
  * @param  idDest : id to send frame to. Not used in case of slaveRequest and noRequest (addressed to master only)
  * @param	frameType : {frameSlaveInquiry, frameBroadcastOrder, frameSlaveRequest, frameNoRequest}
  * @retval pointer to frame
  */
uint8_t* Frame_Format(uint8_t idDest, frameTypeEnum frameType, uint8_t frame[32]);

/**
  * @brief  function for decoding received frame and put data into fields
  * @param  frame to decode
  * @retval decoded frame
  */
frameField Frame_Decode(uint8_t frameToDecode[32]);

/**
  * @brief  function for verifying integrity of received frame. Must be called after Frame_Decode()
  * @param  decoded frame to verify : frameField type
  * @retval 0 = frame OK 1 = frame NOK
  */
uint8_t Frame_Verify(frameField frameToVerify);

/**
  * @brief  Function for setting data field (for slaveData
  * @param  array which will contain data to set
  * @retval None
  */
void Set_Data(uint8_t dataToSet[2]);

#endif /* APP_INC_FRAME_H_ */

/*
 * s_frame.c
 *
  *  Created on: 23 Aout 2021
 *      Author: Benoit
 */


#include <frame.h>
#include <stdlib.h>

frameTypeEnum frameType;

frameField decodedFrame;
uint8_t data[2] = {0};

uint8_t* Frame_Format(uint8_t idDest, frameTypeEnum frameType,uint8_t frame[4])
{
	/* probably some initialization */
	switch(frameType)
	{
		uint8_t i =0;
#ifdef MASTER
		case frameSlaveInquiry:
			// id
			for(i=0; i<8; i++)
			{
					frame[0] |= (idDest & (0x01<<i));  // id is the 8 first bits of frame
			}

			// frame type
			for(i=0; i<8; i++)
			{
				frame[1] |= (frameSlaveInquiry & (0x01<<i));
			}

			// data (no data needed; set to 0)
			frame[2] = 0;
			frame[3] = 0;
			break;

		case frameBroadcastOrder:
			// id dest
			for(i=0; i<8; i++)
				{
					frame[0] |= (idDest & (0x01<<i));  // id is the 8 first bits of frame
				}

			// frame type
			for(i=0; i<8; i++)
			{
				frame[1] |= (frameBroadcastOrder & (0x01<<i));
			}
			// data : none

			for(i=0; i<8; i++)
			{
				frame[2] = 0;
			}
			for(i=0; i<8; i++)
			{
				frame[3] = 0;
			}
			break;
#endif

#ifdef SLAVE
		case frameSlaveRequest:
			// id
			for(i=0; i<8; i++)
			{
					frame[0] |= (MASTER_ADDRESS & (0x01<<i));  // id is the 8 first bits of frame
			}

			// frame type
			for(i=0; i<8; i++)
			{
				frame[1] |= (frameSlaveRequest & (0x01<<i));
			}

			// data [idReq1; idReq2];
			frame[2] = data[0];
			frame[3] = data[1];
			break;

		case frameSlaveData:
			// id
			for(i=0; i<8; i++)
			{
					frame[0] |= (BROADCAST_ADDRESS & (0x01<<i));  // id is the 8 first bits of frame
			}

			// frame type
			for(i=0; i<8; i++)
			{
				frame[1] |= (frameSlaveData & (0x01<<i));
			}

			// data
			frame[2] = data[0];
			frame[3] = data[1];
			break;

		case frameNoRequest:
			// id
			for(i=0; i<8; i++)
			{
					frame[0] |=  (MASTER_ADDRESS & (0x01<<i));  // id is the 8 first bits of frame
			}

			// frame type
			for(i=0; i<8; i++)
			{
				frame[1] |= (frameNoRequest & (0x01<<i));
			}

			// no Data
			frame[2] = 0;
			frame[3] = 0;
			break;
#endif

		default:
			break;
	}
	return frame;
}

frameField Frame_Decode(uint8_t frameToDecode[31])
{
	frameField decodedFrame;
	decodedFrame.idCalled = 0;
	decodedFrame.frameType = 0;
	decodedFrame.data = 0;

	uint8_t i =0;

	// idCalled
	for(i=0; i<8; i++)
	{
		decodedFrame.idCalled |= (frameToDecode[0]& (0x01<<i)); // id is the 8 first bits of frame
	}

	// frameType
	for(i=0; i<8; i++)
	{
		decodedFrame.frameType |= (frameToDecode[1]& (0x01<<i));	// frameType is the 9th to 16th bit of frame
	}

	// data[1]
	for(i=0; i<8; i++)
	{
		decodedFrame.data |= (frameToDecode[2]& (0x01<<i));
	}
	// data[2]
	for(i=0; i<8; i++)
	{
		decodedFrame.data |= (frameToDecode[3]& (0x01<<i));
	}

	return decodedFrame;
}

uint8_t Frame_Verify(frameField frameToVerify)
{
	// empty frame is not valid
	if(frameToVerify.idCalled == 0 &&
		frameToVerify.frameType == 0 &&
		frameToVerify.data ==0)
		return 1;
	// id
	else if(frameToVerify.idCalled != MASTER_ADDRESS &&
		frameToVerify.idCalled != STATION_1_ADDRESS &&
		frameToVerify.idCalled != STATION_2_ADDRESS &&
		frameToVerify.idCalled != BROADCAST_ADDRESS)
		return 1;
	//frameType
	else if(frameToVerify.frameType >= lastElement) // lastElement = 5
		return 1;

	// data ??
	else
	return 0;
}

void Set_Data(uint8_t dataToSet[2])
{
	uint8_t i = 0;
	for(i=0; i<2; i++)
	{
		data[i] = dataToSet[i];
	}
}

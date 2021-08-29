 /*
 * s_mef.c
 *
 *  Created on: 16 juil. 2021
 *      Author: benoit
 */

/*********** defines ***************/
#include <s_system_state.h>
#include "main.h"
#include "appSX1272.h"
#include "SX1272.h"
#include "comSX1272.h"
#include "string.h"
#include "delay.h"
#include "frame.h"

extern SX1272status currentstate;

/************* Variables *************/
static float waitPeriod = 0; //en ms
static int cp = 0;  //compteur de paquets transmis
static int type_modulation=TypeModulation;
static uint16_t RegBitRate = BitRate;
static uint16_t RegFdev = Fdev;

char Tab[30];
uint8_t EmptyTab[4] = {0};

StateEnum mefState;
frameField decodedFrame;
uint8_t frameToSend[4] = {0};
uint8_t frameToReceive[4] = {0};
uint8_t dataRequest[2] = {1,0}; // data needed from station 1 only
uint8_t dataToSend[2] = {5,5}; // data to be sent when Station sends data

static uint8_t myId = 2; //id de la station (254 pour le maitre, de 1 a 253 pour les stations, 255 pour broadcast)

/************ Status variables **************/
static int8_t e;
static uint8_t ConfigOK = 1;
uint8_t dataNeeded =0;

/************ functions **************/

void S_System_State(void)
{
	/* probably some initialization */
	switch(mefState){

	case stateInit:
		S_System_State_Setup();
		mefState = stateIdle;
		break;

	case stateIdle:
		for(uint8_t i = 0; i< 4; i++)
		{
			frameToReceive[i] = 0;
		}
		S_Receive(frameToReceive);
		if (!(frameToReceive[0] == 0 && frameToReceive[1] == 0 && frameToReceive[2] == 0 && frameToReceive[3] == 0))
		{
			my_printf("Slave 01 message received \n");

			mefState = stateFrameDecode;
		}
		break;

	case stateFrameDecode:
		my_printf("S decode \r\n");

		decodedFrame = Frame_Decode(frameToReceive);
		if(decodedFrame.idCalled == myId)
		{
			if(decodedFrame.frameType == frameSlaveInquiry)
			{
				if(dataNeeded)
					mefState = stateSendSlaveRequest;
				else
					mefState = stateSendNoRequest;
			}

			else if(decodedFrame.frameType == frameBroadcastOrder)
			{
				mefState = stateSendData;
			}
		}
		else if(decodedFrame.idCalled == BROADCAST_ADDRESS)
		{
			if(dataNeeded)
			{
				dataNeeded = 0;
			}
			mefState = stateIdle;
		}
		else
		{
			my_printf("Frame not needed or invalid \n\r");
			mefState = stateIdle;
		}
		break;

	case stateSendNoRequest:
		my_printf("S send no request \r\n");
		for(uint8_t i = 0; i< 4; i++)
		{
			frameToSend[i] = 0;
		}
		Frame_Format(MASTER_ADDRESS, frameNoRequest, frameToSend);

		//BSP_DELAY_ms(500);


		S_Transmit(frameToSend);

		mefState = stateIdle;
		break;

	case stateSendSlaveRequest:
		Set_Data(dataRequest);
		Frame_Format(MASTER_ADDRESS, frameSlaveRequest, frameToSend);
		S_Transmit(frameToSend);
		mefState = stateIdle;
		break;

	case stateSendData:
		Set_Data(dataToSend);
		Frame_Format(BROADCAST_ADDRESS, frameSlaveData, frameToSend);
		S_Transmit(frameToSend);
		mefState = stateIdle;
		break;
	}
}

void S_System_State_Setup(void)
{
  // Power ON the module
  e = BSP_SX1272_ON(type_modulation);
  if (e == 0)
  {
	my_printf("SX1272 Module on\r\n");
  }
  else
  {
	//my_printfln(F("Problem of activation of SX1272 Module !"));
	ConfigOK = 0;
  }
  // Select frequency channel
  e = BSP_SX1272_setChannel(freq_centrale);
  my_printf("Frequency channel ");
  my_printf("%d",freq_centrale);
  if (e == 0)
  {
	my_printf(" has been successfully set.\r\n");
  }
  else
  {
	my_printf(" has not been set !\r\n");
	ConfigOK = 0;
  }
  // Select output power
  e = BSP_SX1272_setPower(OutPower);
  my_printf("Output power ");
  my_printf("%d",OutPower);
  if (e == 0)
  {
	my_printf(" has been successfully set.\r\n");
  }
  else
  {
	my_printf(" has not been set !\r\n");
	ConfigOK = 0;
  }

  if (ConfigOK == 1)
  {
	//////////////////////////////////////////////////////////////////////
  //config suppl�mentaire mode LORA
	//////////////////////////////////////////////////////////////////////
	if(type_modulation==0)
	{
	  // Set header
	  e = BSP_SX1272_setHeaderON();
	  // Set transmission mode
	  e = BSP_SX1272_setCR(paramCR);    // CR_5 : CR = 4/5
	  e = BSP_SX1272_setSF(paramSF);   // SF = 12
	  e = BSP_SX1272_setBW(paramBW);    // BW = 125 KHz
	  // Set CRC
	  e = BSP_SX1272_setCRC_ON();
	  // Set the node address
	  e = BSP_SX1272_setNodeAddress(RX_Addr);
	  // Set the length of preamble
	  e = BSP_SX1272_setPreambleLength(PreambLong);
	  // Set the number of transmission retries
	  currentstate._maxRetries = MaxNbRetries;
	}
	//////////////////////////////////////////////////////////////////////
	//config suppl�mentaire mode FSK
	//////////////////////////////////////////////////////////////////////
	else
	{
	  // Set CRC
	  e = BSP_SX1272_setCRC_ON();
	  // Set the node address
	  e = BSP_SX1272_setNodeAddress(RX_Addr);
	  // Set the length of preamble
	  e = BSP_SX1272_setPreambleLength(PreambLong);
	  // Set the number of transmission retries
	  currentstate._maxRetries = MaxNbRetries;

	  BSP_SX1272_Write(REG_SYNC_VALUE1,0x05);
	  BSP_SX1272_Write(REG_SYNC_VALUE2,0x05);
	  BSP_SX1272_Write(REG_SYNC_VALUE3,0x05);
	  BSP_SX1272_Write(REG_SYNC_VALUE4,0x05);

	  //Set the frequency deviation an bit rate parameters
	  BSP_SX1272_Write(REG_FDEV_MSB,(RegFdev>>8)&0x00FF);// FDA = Fstep*FDEV = 61Hz*Fdev : ex: 0x7FF*61 = 125kHz ex2: 0X52*61=5kHz
	  BSP_SX1272_Write(REG_FDEV_LSB,RegFdev&0x00FF);//...
	  BSP_SX1272_Write(REG_BITRATE_MSB,(RegBitRate>>8)&0x00FF);//FXOSC=32Mz, BR = FXOSC/(Bitrate + BitrateFrac/16), ex: FXOSC/0x682B = 1200 bauds, ex2: FXOSC/0x200=62.5 kbauds
	  BSP_SX1272_Write(REG_BITRATE_LSB,RegBitRate&0x00FF);//...

	}
	my_printf("SX1272 successfully configured !\r\n");
  }
  else
  {
	my_printf("SX1272 initialization failed !\r\n");
  }

  waitPeriod = PeriodTransmission;

  BSP_DELAY_ms(1000);
}

//void M_Transmit(const char* Message)
void S_Transmit(uint8_t frame[4]) // TODO : mettre un type à Message
{
  uint8_t dest_address = TX_Addr;

  //////////////////////////////////////////////////////////////////////////////////
  // Transmit a packet continuously with a pause of "waitPeriod"
  if (ConfigOK == 1)
  {

    e = BSP_SX1272_sendPacketTimeout(dest_address, frame, WaitTxMax);

    if (e == 0)
    {
      my_printf("\n Packet number ");
      my_printf("%d",cp);
	  my_printf(" ; Broadcast address ");
	  my_printf("%d\r",dest_address);

	  my_printf("\n Message sent : ");
	  for(uint8_t i = 0; i< 4; i++)
	  {
		  my_printf("%d;",frame[i]);
	  }
	  my_printf("\n\r");

      cp++;
    }
    else
    {
      my_printf("\n Transmission problem !\r\n");
    }
    //BSP_DELAY_ms(waitPeriod); //delay to send packet every PeriodTransmission
  }
}

uint8_t* S_Receive(uint8_t frame[4])
{

  //////////////////////////////////////////////////////////////////////////////////
  // Receive packets continuously
  if (ConfigOK == 1)
  {
	  e = BSP_SX1272_receivePacketTimeout(WaitRxMax);
	  //paquet recu, correct ou non
	  if (e == 0)
	  {
		if (currentstate._reception == CORRECT_PACKET)
		{
			my_printf("\n \r\n");
			my_printf("Received data \r\n");

			//////////////////////////////////////////////////////////////////////////////////
			// Plot receive packets in the serial monitor
			//for (uint8_t i =0; i < currentstate.packet_received.length-OFFSET_PAYLOADLENGTH; i++)
			for (uint8_t i =0; i < currentstate.packet_received.length-OFFSET_PAYLOADLENGTH; i++)
			{
			  my_printf("%d",currentstate.packet_received.data[i]);
			}

			for (uint8_t i =0; i < currentstate.packet_received.length-OFFSET_PAYLOADLENGTH; i++)
			{
			  frame[i] = currentstate.packet_received.data[i];
			}

			my_printf("\r\n");
			my_printf("\n Message received : ");
			for(uint8_t i = 0; i< 4; i++)
			{
				my_printf("%d;",frame[i]);
			}

			my_printf("Packet number %d \r\n", currentstate.packet_received.packnum);
			my_printf("Length %d \r\n",currentstate.packet_received.length);
		}
	  }
  }
  return frame;
  //BSP_DELAY_ms(1000);
}



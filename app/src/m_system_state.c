/*
 * M_system_state.c
 *
 *  Created on: 16 juil. 2021
 *      Author: J�r�my/Benoit
 */

#include <m_system_state.h>
#include "main.h"
#include "appSX1272.h"
#include "SX1272.h"
#include "comSX1272.h"
#include "string.h"
#include "delay.h"


extern SX1272status currentstate;

///////////////////////////////////////////////////////////////
// D�claration variables globales
///////////////////////////////////////////////////////////////
static float waitPeriod = 0; //en ms
static int cp = 0;  //compteur de paquets transmis
static int type_modulation=TypeModulation;
static uint16_t RegBitRate = BitRate;
static uint16_t RegFdev = Fdev;

//char Tab[30] = "";

StateEnum mefState;

// status variables
static int8_t e;
static uint8_t ConfigOK = 1;

///////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////

void M_system_state_main(char Tab[30])
{
	enum {Station_1, Station_2, Station_3};
	char etat = Station_1;
	char Retour = "";

	M_Receive(Tab);

	//while (1) {
	/*switch (etat) {
	case 0: 	M_Transmit("Station_1 est-tu la ?");
				//Retour = M_Receive();
				//if (Retour == "") etat = Station_2; break;
				//BSP_DELAY_ms(100);
				etat = Station_2; //break;

	case 1: 	M_Transmit("Station_2 est-tu la ?");
				//Retour = M_Receive();
				//if (Retour == "") etat = Station_3; break;
				//BSP_DELAY_ms(100);
				etat = Station_3; //break;

	case 2: 	M_Transmit("Station_3 est-tu la ?");
				//Retour = M_Receive();
				//if (Retour == "") etat = Station_1; break;
				//BSP_DELAY_ms(100);
				etat = Station_1; //break;
		}*/
	//}

}

void M_System_State(void)
{
	switch(mefState)
	{
		case stateInit:
			M_System_State_Setup();
			mefState = stateIdle;
			break;

		case stateIdle:
			// wait for periodic interrupt
			break;

		case stateSendSlaveInquiry:
			// kikou mettre du code ici
			mefState = stateWaitForResponse;
			break;

		case stateWaitForResponse:
			/* just wait */
			break;

		case stateFrameDecode:
			/* if noRequest and other station to ask : mefState = stateSendSlaveInquiry, else if no station left : mefState = stateIdle */
			break;

		case stateSendBroadcastOrder:
			break;

		default:
			break;
	}
}

void M_System_State_Setup()
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
void M_Transmit(Message) // TODO : mettre un type à Message
{
  uint8_t dest_address = TX_Addr;

  //////////////////////////////////////////////////////////////////////////////////
  // Transmit a packet continuously with a pause of "waitPeriod"
  if (ConfigOK == 1)
  {

    e = BSP_SX1272_sendPacketTimeout(dest_address, Message, WaitTxMax);

    if (e == 0)
    {
      my_printf("\n Packet number ");
      my_printf("%d",cp);
	  my_printf(" ;Rx node address ");
	  my_printf("%d\r",dest_address);

	  my_printf("\n Message ");
	  my_printf("%s\r\n",Message);
      cp++;
    }
    else
    {
      my_printf("\n Transmission problem !\r\n");
    }
    //BSP_DELAY_ms(waitPeriod); //delay to send packet every PeriodTransmission
  }
}

void M_Receive(void)
{
  //char Message_receive[30] = "";

  my_printf(Tab);

  //////////////////////////////////////////////////////////////////////////////////
  // Receive packets continuously
  if (ConfigOK == 1)
  {
	  e = BSP_SX1272_receivePacketTimeout(WaitRxMax);
	  //paquet re�u, correct ou non
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
			  my_printf("%c",currentstate.packet_received.data[i]);
			}

			for (uint8_t i =0; i < currentstate.packet_received.length-OFFSET_PAYLOADLENGTH; i++)
			{
			  Tab[i] = currentstate.packet_received.data[i];
			}

			my_printf("\r\n");
			my_printf("Message : %s \r\n", Tab);
			my_printf("Packet number %d \r\n", currentstate.packet_received.packnum);
			my_printf("Length %d \r\n",currentstate.packet_received.length);
		}
	  }


  }

  //BSP_DELAY_ms(1000);
}

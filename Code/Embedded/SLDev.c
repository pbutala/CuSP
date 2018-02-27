/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Defines.h"
#include "Watchdog.h"
#include "Clock.h"
#include "Serial.h"
#include "GPIO.h"
#include "TimerA.h"
#include "ANTmsgs.h"
#include "ANTmtds.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "ADJDS311.h"
#include "TCS3414.h"
#include "TCS3471.h"
#include "CtrlRoutines.h"
#include "DataRoutines.h"

/***********************************************
 * Change DEVICENUMBER before programming !!!
 * *********************************************/
void main(void)
{
	unsigned int flgOpen;
	unsigned char LED;
	unsigned char* bufPtr;
	//UCHAR nxtCnfgMsgID = MESG_INVALID_ID;	// ANT configuration command selector variable
	ConfigureWDT();					// Configure Watchdog timer TODO: enable it for release
	ConfigureBCS();					// Configure Basic Clock System TODO: figure out lpm modes
	ConfigureGPIO();				// Configure GPIO
	//ConfigureI2C();					// Configure I2C to talk to ACC and GYRO
	ConfigureSPI();					// Configure SPI to talk to ANT module
	
	_bis_SR_register(GIE);			// turn on interrupts
	
	ConfigureI2C();					// Configure I2C to talk to ACC and GYRO
	SleepADJDS311(false);			// need this[SleepADJDS311(false);]. else hangs I2C bus
	ResetADJDS311();
	//SleepITG3200(true);
	//SleepADXL345(true);
	PowerOffTCS3471();
	PowerOffTCS3414();
	ConfigureTCS3471();

	fCOMFLAG = 0x0000;				// Clear all COMFLAGs
	//P4OUT |= LED_PWR_CTRL; 
	fSTPEND = fResetAnt;			// Set Reset ANT module as next state
	
	while(1){
		if(fSTPEND & fSrvRxMsgAnt){// if state pending == SERV RCVD MSG FROM ANT
			ServiceRcvdMsgBuf();
			fSTPEND &= ~fSrvRxMsgAnt;	// RCVD MSG FROM ANT serviced; clear pending flag
		}
		else if(fSTPEND & fRxMsgAnt){	// if state pending == START RX MSG FROM ANT (Assume RxSYNC rcvd)
			RxMessageFromAnt();
			fSTPEND &= ~fRxMsgAnt;		// Received msg from ANT; clear pending flag
		}
		else if(fSTPEND & fTxMsgAnt){	// if state pending == START Tx MSG TO ANT (Assume TxSYNC rcvd)
			TxMessageToAnt();
			fSTPEND &= ~fTxMsgAnt;		// Transmitted msg to ANT; clear pending flag
			fSTPEND &= ~fTxWaitAnt;				// Done waiting to receive SEN and TxSYNC from ANT module
		}
		else if(fSTPEND & fTxWaitAnt){
			_delay_cycles(DLY_1MHz_10u);	// Do not proceed further if waiting for ANT to reply to TxRequest
		}
		else if(fSTPEND & fTxIniAnt){	// if state pending == Initialize handshake for Tx
			if(P2IN & ANT_SEN){
				TxInitiateHandshake();
				fSTPEND |= fTxWaitAnt;		// Waiting to receive SEN and TxSYNC from ANT module 
				fSTPEND &= ~fTxIniAnt;		// Initialized tx handshake with ANT; clear pending flag
			}
		}
		else if(fSTPEND & fResetAnt){		// if state pending == RESET ANT
			fCOMFLAG = 0x0000;				// Clear all COMFLAGs
			ResetANTModule();
			nxtCnfgMsgID = MESG_NETWORK_KEY_ID;
			fSTPEND = fConfigAnt;					// Set Configure ANT module flag
			fCOMFLAG |= fCtrlChannelOpening;
		}
		else if(fSTPEND & fGyrDtRdy){	// if state pending == GYRO data ready
			// !! currently read from timer intr
			//RxI2CMessage(ITG3200_ADDR, REG_TEMP_OUT_H, &ITG3200Data[0], ITG_DATA_LEN);	// Read 3 Axis GYR data
			fSTPEND &= ~fGyrDtRdy;
		}
		else if(fSTPEND & fAccDtRdy){	// if state pending == ACC data ready
			// !! currently read from timer intr !!
			//RxI2CMessage(ADXL345_ADDR, REG_DATAX0, &ADXL345Data[0], ADXL_DATA_LEN);	// Read 3 Axis ACC data
			fSTPEND &= ~fAccDtRdy;
		}
		else if(fSTPEND & fConfigAnt){ 	// if state pending == CONFIG ANT
			if(!(fCOMFLAG & fSerBusy)){	// if serial not busy
				switch(nxtCnfgMsgID){
					case MESG_NETWORK_KEY_ID: 
							BufSetNwKeyMsg(SYSTEM_NETWORK_NUM, SYSTEM_NW_KEY);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_UNASSIGN_CHANNEL_ID;
							break;
					case MESG_UNASSIGN_CHANNEL_ID:
							BufUnAssignChannelMsg(ANT_CHANNEL);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_ASSIGN_CHANNEL_ID;
							break;
					case MESG_ASSIGN_CHANNEL_ID:
							BufAssignChannelMsg(ANT_CHANNEL, ANT_CHANNELTYPE, SYSTEM_NETWORK_NUM);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_CHANNEL_ID_ID;
							break;
				    case MESG_CHANNEL_ID_ID:
				    		BufSetChannelIDMsg(ANT_CHANNEL, ANT_DEVICENUM, ANT_DEVICETYPE, ANT_TRANSTYPE);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_CHANNEL_RADIO_FREQ_ID;
				    		break;
				    case MESG_CHANNEL_RADIO_FREQ_ID: 
				    		BufSetRadioFreqMsg(ANT_CHANNEL, ANT_FREQ);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_CHANNEL_MESG_PERIOD_ID;
				    		break;
				    case MESG_CHANNEL_MESG_PERIOD_ID: 
				    		//change TimerA count when message period is changed
				    		BufSetChannelMsgPeriodMsg(ANT_CHANNEL, ANT_PERIOD);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_OPEN_CHANNEL_ID;
				    		break;
				    case MESG_OPEN_CHANNEL_ID: 
			    			BufOpenChannelMsg(ANT_CHANNEL);
							fSTPEND |= fTxIniAnt;
							nxtCnfgMsgID = MESG_BROADCAST_DATA_ID;
							LED = ((ANT_CHANNEL == CTRL_ANTCHANNEL) ? LED_PWR_CTRL : LED_RF_DATA);
							P4OUT |= LED;
			    			break;
			    	case MESG_BROADCAST_DATA_ID:
			    			bufPtr = ((ANT_CHANNEL == CTRL_ANTCHANNEL) ? TxControlBuffer : TxDataBuffer);
				    		BufSendBroadcastDataMsg2(ANT_CHANNEL, bufPtr, 8);	// Set up buffer to broadcast
							fSTPEND |= fTxIniAnt;					// Flag tx initiate
							nxtCnfgMsgID = MESG_INVALID_ID;
				    		break;
				    case MESG_CLOSE_CHANNEL_ID:
				    		flgOpen = ((ANT_CHANNEL == CTRL_ANTCHANNEL) ? fCtrlChannelOpen : fDataChannelOpen);
			    			if(fCOMFLAG & flgOpen){
				    			BufCloseChannelMsg(ANT_CHANNEL);
								fSTPEND |= fTxIniAnt;
							}
							else
							{
								LED = ((ANT_CHANNEL == CTRL_ANTCHANNEL) ? LED_PWR_CTRL : LED_RF_DATA);
								P4OUT &= ~LED;
								nxtCnfgMsgID = MESG_INVALID_ID;
							}
				    		break;
					default:fSTPEND &= ~fConfigAnt;
			    			break;						
				}
			}
			else{
				//_delay_cycles(DLY_1MHz_10u);
			}
		}
		else if(fSTPEND & fTxCtrlAnt){
			fSTPEND &= ~fTxCtrlAnt;
			BufSendBroadcastDataMsg2(CTRL_ANTCHANNEL, TxControlBuffer, 8);	// Set up buffer to broadcast
			fSTPEND |= fTxIniAnt;
			ServiceControlCommand();
			P4OUT ^= LED_PWR_CTRL;
		}
		else if(fSTPEND & fTxDataAnt){
			if(fCOMFLAG & fDataChannelOpen){
				fSTPEND &= ~fTxDataAnt;
				BufSendBroadcastDataMsg2(CuSP_ANTCHANNEL, TxDataBuffer, 8);	// Set up buffer to broadcast
				fSTPEND |= fTxIniAnt;
				GetSensorData(DATA_SENSOR);
				P4OUT ^= LED_RF_DATA;
			}
		}
		else{
			//_delay_cycles(DLY_1MHz_10u);
		}
	//_delay_cycles(DLY_1MHz_10u);
	}
}

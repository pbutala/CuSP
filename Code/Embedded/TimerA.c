/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Defines.h"
#include "TimerA.h"
#include "ANTmtds.h"
#include "ANTmsgs.h"
#include "Serial.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "ADJDS311.h"
#include "TCS3414.h"
#include "TCS3471.h"

UCHAR dataSource = ADXL_DATA;
unsigned char TxDataBuffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char TxControlBuffer[8] = {CuSP_SHARED_CHANNELNUM_LSB, CuSP_SHARED_CHANNELNUM_MSB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned int tmrCount = 0;

void ConfigureTimerA()
{
	CCTL0 = CCIE;					// Enable Interrupt
	CCR0 = CNT_12kHz_200Hz;			// set up for 200 Hz.
	//CCR0 = CNT_12kHz_200Hz*2;			// set up for 100 Hz.
	TACTL = TASSEL_1 + MC_1;		// Select ACLK
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
	_bis_SR_register(GIE);					// turn on interrupts for SEN
	
//	if(fCOMFLAG & fNewCtrlCmd){
//		//fCOMFLAG &= ~fNewCtrlCmd;
//		switch(CTRL_COMMAND){
//			case CTRL_CMD_SOURCE:
//				/*if(CTRL_SENSOR != CTRL_SENSOR_OLD){
//					if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//						if(!((fSTPEND & fTxIniAnt)||(fSTPEND & fTxWaitAnt))){
//						SleepADXL345(true);
//						SleepITG3200(true);
//						PowerOffTCS3414();
//						PowerOffTCS3471();
//						switch(CTRL_SENSOR){
//							case SENSOR_TCS3414:
//								PowerOnTCS3414();
//								break;
//							case SENSOR_TCS3471:
//								PowerOnTCS3471();
//								break;
//							case SENSOR_ADJDS311:
//								//PowerOnADJDS311();
//								break;
//							case SENSOR_ADXL345:
//								StartMeasureADXL345();
//								break;
//							case SENSOR_ITG3200:
//								StartMeasureITG3200();
//								break;
//						}
//						CTRL_SENSOR_OLD = CTRL_SENSOR;
//						/ *TxControlBuffer[2] = CTRL_COMMAND;
//						TxControlBuffer[3] = CTRL_SENSOR;
//						TxControlBuffer[4] = CTRL_PARAM_1;
//						TxControlBuffer[5] = CTRL_PARAM_2;* /
//						}
//					}
//				}
//				else
//				{
//					if(fCOMFLAG & fOkToBcstData){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//						if(!((fSTPEND & fTxIniAnt)||(fSTPEND & fTxWaitAnt))){
//							switch(CTRL_SENSOR){
//								case SENSOR_TCS3414:
//									GetTCS3414Data(TxDataBuffer);
//									break;
//								case SENSOR_TCS3471:
//									GetTCS3471Data(TxDataBuffer);
//									break;
//								case SENSOR_ADJDS311:
//									//GetADJDS311Data(TxDataBuffer);
//									break;
//								case SENSOR_ADXL345:
//									GetADXL345Data(TxDataBuffer);
//									break;
//								case SENSOR_ITG3200:
//									GetITG3200Data(TxDataBuffer);
//									break;
//							}
//						}
//					}
//				}*/
//				break;
//			case CTRL_CMD_DATACHANNEL:
//				/*/ *if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//					//fCOMFLAG &= ~fNewCtrlCmd;
//					TxControlBuffer[2] = CTRL_COMMAND;
//					TxControlBuffer[3] = CTRL_SENSOR;
//					TxControlBuffer[4] = CTRL_PARAM_1;
//					TxControlBuffer[5] = CTRL_PARAM_2;
//				}* /
//				switch(CTRL_PARAM_1){
//					case CTRL_PARAM_ON:
//						if(!(fSTPEND & fConfigAnt)){
//							if(!((fCOMFLAG & fDataChannelOpen)||(fCOMFLAG & fDataChannelOpening))){
//								if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//									ANT_CHANNEL = CuSP_ANTCHANNEL;
//									ANT_CHANNELTYPE = CuSP_CHANNELTYPE;
//									ANT_DEVICENUM = CuSP_DEVICENUM;
//									ANT_DEVICETYPE = CuSP_DEVICETYPE;
//									ANT_TRANSTYPE = CuSP_TRANSTYPE;
//									ANT_FREQ = CuSP_FREQ;
//									ANT_PERIOD = CuSP_PERIOD;
//									nxtCnfgMsgID = MESG_UNASSIGN_CHANNEL_ID;
//									fCOMFLAG |= fDataChannelOpening;
//									fSTPEND |= fConfigAnt;
//									
//									/ *TxControlBuffer[2] = CTRL_COMMAND;
//									TxControlBuffer[3] = CTRL_SENSOR;
//									TxControlBuffer[4] = CTRL_PARAM_1;
//									TxControlBuffer[5] = CTRL_PARAM_2;* /
//								}
//							}	
//						}
//						break;
//					case CTRL_PARAM_OFF:
//						if(fCOMFLAG & fDataChannelOpen){
//							if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//								if(!((fSTPEND & fTxIniAnt)||(fSTPEND & fTxWaitAnt))){
//									BufCloseChannelMsg(CuSP_ANTCHANNEL);
//									fSTPEND |= fTxIniAnt;
//									
//									/ *TxControlBuffer[2] = CTRL_COMMAND;
//									TxControlBuffer[3] = CTRL_SENSOR;
//									TxControlBuffer[4] = CTRL_PARAM_1;
//									TxControlBuffer[5] = CTRL_PARAM_2;* /
//								}
//							}
//						}
//						break;
//				}*/
//				break;
//			case CTRL_CMD_TXI2C:
//				/*if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//					if((CTRL_SENSOR == SENSOR_TCS3414) ||
//						 	(CTRL_SENSOR == SENSOR_TCS3471) ||
//						 	(CTRL_SENSOR == SENSOR_ADXL345) ||
//						 	(CTRL_SENSOR == SENSOR_ITG3200)){
//						TxI2CMessage(CTRL_SENSOR, CTRL_PARAM_1, &CTRL_PARAM_2, 1);
//						/ *TxControlBuffer[2] = CTRL_COMMAND;
//						TxControlBuffer[3] = CTRL_SENSOR;
//						TxControlBuffer[4] = CTRL_PARAM_1;
//						TxControlBuffer[5] = CTRL_PARAM_2;* /
//				 	}
//				}*/
//				break;
//			case CTRL_CMD_RXI2C:
//				if((CTRL_SENSOR == SENSOR_TCS3414) ||
//			 		(CTRL_SENSOR == SENSOR_TCS3471) ||
//			 		(CTRL_SENSOR == SENSOR_ADXL345) ||
//			 		(CTRL_SENSOR == SENSOR_ITG3200)){
//					RxI2CMessage(CTRL_SENSOR, CTRL_PARAM_1, &CTRL_PARAM_2, 1);
//			 	}
//				break;
//		}
//	}
//	
//	
//	if(fCOMFLAG & fNewCtrlCmd){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//		fCOMFLAG &= ~fNewCtrlCmd;					// Clear OK to broadcast flag
//		TxControlBuffer[0] = CuSP_SHARED_CHANNELNUM_LSB;
//		TxControlBuffer[1] = CuSP_SHARED_CHANNELNUM_MSB;
//		TxControlBuffer[2] = CTRL_COMMAND;
//		TxControlBuffer[3] = CTRL_SENSOR;
//		TxControlBuffer[4] = CTRL_PARAM_1;
//		TxControlBuffer[5] = CTRL_PARAM_2;
//		//BufSendBroadcastDataMsg2(CTRL_ANTCHANNEL, TxControlBuffer, 8);	// Set up buffer to broadcast
//		//fSTPEND |= fTxIniAnt;					// Flag tx initiate
//		//fSTPEND |= fTxCtrlAnt;
//	}
//	/*else if(fCOMFLAG & fOkToBcstData){					// If OK to broadcst. i.e. ANT has communicated its buffers are free for data
//		fCOMFLAG &= ~fOkToBcstData;					// Clear OK to broadcast flag
//		/ *BufSendBroadcastDataMsg2(CuSP_ANTCHANNEL, TxDataBuffer, 8);	// Set up buffer to broadcast
//		fSTPEND |= fTxIniAnt;* /					// Flag tx initiate
//	}*/
//	
//	/*if(fCOMFLAG & fLEDCtrlOn)
//		P4OUT ^= LED_PWR_CTRL;
//	else
//		P4OUT &= ~LED_PWR_CTRL;
//	
//	if(fCOMFLAG & fLEDDataOn)
//		P4OUT ^= LED_RF_DATA;
//	else
//		P4OUT &= ~LED_RF_DATA;*/
}


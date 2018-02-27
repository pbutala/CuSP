/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "CtrlRoutines.h"
#include "Defines.h"
#include "Serial.h"
#include "ANTmsgs.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "TCS3471.h"
#include "TCS3414.h"

void ServiceControlCommand(){
	switch(CTRL_COMMAND){
		case CTRL_CMD_DATACHANNEL:
			switch(CTRL_PARAM_1){
				case CTRL_PARAM_ON:
					if(!((fCOMFLAG & fDataChannelOpen)||(fCOMFLAG & fDataChannelOpening))){
						ANT_CHANNEL = CuSP_ANTCHANNEL;
						ANT_CHANNELTYPE = CuSP_CHANNELTYPE;
						ANT_DEVICENUM = CuSP_DEVICENUM;
						ANT_DEVICETYPE = CuSP_DEVICETYPE;
						ANT_TRANSTYPE = CuSP_TRANSTYPE;
						ANT_FREQ = CuSP_FREQ;
						ANT_PERIOD = CuSP_PERIOD;
						nxtCnfgMsgID = MESG_UNASSIGN_CHANNEL_ID;
						fCOMFLAG |= fDataChannelOpening;
						fSTPEND |= fConfigAnt;
					}	
					break;
				case CTRL_PARAM_OFF:
					if(fCOMFLAG & fDataChannelOpen){
						ANT_CHANNEL = CuSP_ANTCHANNEL;
						nxtCnfgMsgID = MESG_CLOSE_CHANNEL_ID;
						fSTPEND |= fConfigAnt;
						CTRL_SENSOR = SENSOR_NONE;
					}
					break;
			}
			//break; intentional fall through
		case CTRL_CMD_SOURCE:
			if(CTRL_SENSOR != DATA_SENSOR){
				switch(CTRL_SENSOR){
					case SENSOR_TCS3471:
						SleepADXL345(true);
						//SleepITG3200(true);
						ConfigureTCS3471();				// Configure TCS3471 once I2C/serial is configured
						PowerOnTCS3471();
						PowerOffTCS3414();
						break;
					case SENSOR_TCS3414:
						SleepADXL345(true);
						ConfigureTCS3471();				// Configure TCS3471 once I2C/serial is configured
						PowerOnTCS3471();
						PowerOnTCS3414();
						ConfigureTCS3414();
						break;
					case SENSOR_ADXL345:
						PowerOffTCS3471();
						ConfigureADXL345();				// Configure ADXL345 once I2C/serial is configured
						StartMeasureADXL345();
						PowerOffTCS3414();
						break;
					case SENSOR_ITG3200:
						SleepADXL345(true);
						PowerOffTCS3471();
						PowerOffTCS3414();
					default:
						SleepADXL345(true);
						PowerOffTCS3471();
						PowerOffTCS3414();
						break;
				}
				DATA_SENSOR = CTRL_SENSOR;
			}
			break;
		case CTRL_CMD_TXI2C:
			if((CTRL_SENSOR == SENSOR_TCS3471) ||
				(CTRL_SENSOR == SENSOR_TCS3414) ||
				 	(CTRL_SENSOR == SENSOR_ADXL345)){
				TxI2CMessage(CTRL_SENSOR, CTRL_PARAM_1, &CTRL_PARAM_2, 1);
		 	}
			break;
		case CTRL_CMD_RXI2C:
			if((CTRL_SENSOR == SENSOR_TCS3471) ||
				(CTRL_SENSOR == SENSOR_TCS3414) ||
		 		(CTRL_SENSOR == SENSOR_ADXL345)){
				RxI2CMessage(CTRL_SENSOR, CTRL_PARAM_1, &CTRL_PARAM_2, 1);
		 	}
			break;
		}
	
		TxControlBuffer[CTRL_DEVICE_LSB_OFFSET] = CuSP_SHARED_CHANNELNUM_LSB;
		TxControlBuffer[CTRL_DEVICE_MSB_OFFSET] = CuSP_SHARED_CHANNELNUM_MSB;
		TxControlBuffer[CTRL_CMD_OFFSET] = CTRL_COMMAND;
		TxControlBuffer[CTRL_SENSOR_OFFSET] = CTRL_SENSOR;
		TxControlBuffer[CTRL_PARAM_1_OFFSET] = CTRL_PARAM_1;
		TxControlBuffer[CTRL_PARAM_2_OFFSET] = CTRL_PARAM_2;
		TxControlBuffer[CTRL_PARAM_3_OFFSET] = CTRL_PARAM_3;
		TxControlBuffer[CTRL_PARAM_4_OFFSET] = CTRL_PARAM_4;
}

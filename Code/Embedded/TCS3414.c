/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "TCS3414.h"
#include "Defines.h"
#include "Serial.h"

void ConfigureTCS3414()
{
	UCHAR rcvData, txData;
	RxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_CTRL), &rcvData, 1);
	
	txData = TCS_INTEG_MODE_FR + TCS_NIT_12ms;
	TxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_TIMING), &txData, 1);
		
	//txData = TCS_ADC_EN + TCS_POWER;
	//TxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_CTRL), &txData, 1);
	//PowerOffTCS3414();
}

void GetTCS3414Data(unsigned char *buffer)
{
	RxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_DATA_G_LO), buffer, TCS_DATA_LEN);
}

void PowerOffTCS3414()
{
	UCHAR txData;
	txData = 0x00;
	TxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_CTRL), &txData, 1);
}

void PowerOnTCS3414()
{
	UCHAR txData;
	txData = TCS_ADC_EN + TCS_POWER;
	TxI2CMessage(TCS_ADDR, (TCS_CMD_BYTE|TCS_REG_CTRL), &txData, 1);
}

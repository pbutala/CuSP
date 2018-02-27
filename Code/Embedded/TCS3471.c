/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "TCS3471.h"
#include "Defines.h"
#include "Serial.h"

void ConfigureTCS3471()
{
	UCHAR txData;
	RxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_ID), &txData, 1);
	
	txData = TCS71_AGAIN_4X;
	TxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_CONTROL), &txData, 1);
	
	txData = 0xFB;
	TxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_ATIME), &txData, 1);
}

void GetTCS3471Data(unsigned char *buffer)
{
	UCHAR txData;
	txData = 0x00;
	while(!(txData & TCS71_STAT_AVALID))
	{
		RxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_STATUS), &txData, 1);	
	}
	RxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_CDATA), buffer, TCS71_DATA_LEN);
}

void PowerOnTCS3471(void)
{
	UCHAR txData;
	txData = TCS71_AEN | TCS71_PON;
	TxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_ENABLE), &txData, 1);
}

void PowerOffTCS3471(void)
{
	UCHAR txData;
	txData = 0x00;
	TxI2CMessage(TCS71_ADDR, (TCS71_CMD_BYTE|TCS71_REG_ENABLE), &txData, 1);
}

/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "ADXL345.h"
#include "Defines.h"
#include "Serial.h"

void ConfigureADXL345()
{
	// Reads the DEVID register. clears any data in device tx buffer
	UCHAR rcvData, txData;
	RxI2CMessage(ADXL345_ADDR, REG_DEVID, &rcvData, 1);
		
	//txData = JUSTIFY + RANGE_0 + INT ActLow;
	txData = RANGE_0 + INT_INVERT;
	TxI2CMessage(ADXL345_ADDR, REG_DATA_FORMAT, &txData, 1);
	
	// BW-25Hz;	op-50Hz
	txData = RATE_9;
	TxI2CMessage(ADXL345_ADDR, REG_BW_RATE, &txData, 1);
	
	// interrupt map
    // data ready to interrupt 1
    txData = 0x00;
	TxI2CMessage(ADXL345_ADDR, REG_INT_MAP, &txData, 1);
	
	// interrupt enable
	txData = DATA_READY;
	TxI2CMessage(ADXL345_ADDR, REG_INT_ENABLE, &txData, 1);
	
	ADXLconfigured = true;
}

void GetADXL345Data(unsigned char *buffer)
{
	RxI2CMessage(ADXL345_ADDR, REG_DATAX0, buffer, ADXL_DATA_LEN);	// Read 3 Axis ACC data
}

void SleepADXL345(bool slp)
{
	UCHAR txData;
	txData = WAKEUP_3;
	if(slp)
		txData |= ADXL_SLEEP;
		
	TxI2CMessage(ADXL345_ADDR, REG_POWER_CTL, &txData, 1);
}

void StartMeasureADXL345()
{
	SleepADXL345(false);
	UCHAR txData;
	txData = MEASURE;
	TxI2CMessage(ADXL345_ADDR, REG_POWER_CTL, &txData, 1);
}

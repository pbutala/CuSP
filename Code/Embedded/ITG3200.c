/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "ITG3200.h"
#include "Defines.h"
#include "Serial.h"

void ConfigureITG3200(void)
{
	UCHAR txData;
	// Reads the WHO_AM_I register. clears any data in device tx buffer
	//RxI2CMessage(ITG3200_ADDR, REG_WHO_AM_I, &rcvData, 1);
	
	// ±2000°/sec; LPF_BW-10Hz; IntSampRate-1kHz
	txData = FS_SEL_3 + DLPF_CFG_5;
	TxI2CMessage(ITG3200_ADDR, REG_DLPF_FS, &txData, 1);
	
	// Sample Rate Config
	// SampRateDiv-19 (Fsamp = IntSampRate/(SampRateDiv + 1))=> Fsamp = 1kHz/20 = 50Hz
	txData = 0x13;
	TxI2CMessage(ITG3200_ADDR, REG_SMPLRT_DIV, &txData, 1);
	
	// Interrupt Config
	// ActiveLow; EnableRawDataAvail
	txData = ACTL + INT_ANYRD_2CLEAR + RAW_RDY_EN;
	TxI2CMessage(ITG3200_ADDR, REG_INT_CFG, &txData, 1);
	
	// PowerMgmt
	// can be used to put device to sleep or individually set gyro for standby
	// can also be used for external clock source selection
	ITGconfigured = true;
}

void GetITG3200Data(unsigned char *buffer)
{
	RxI2CMessage(ITG3200_ADDR, REG_GYRO_XOUT_H, buffer, ITG_DATA_G_LEN);	// Read 3 Axis GYR data
}

void SleepITG3200(bool slp)
{
	UCHAR txData;
	txData = STBY_XG | STBY_YG | STBY_ZG;
	if(slp)
		txData |= SLEEP;
	
	TxI2CMessage(ITG3200_ADDR, REG_PWR_MGM, &txData, 1);
}

void StartMeasureITG3200()
{
	SleepITG3200(false);
	UCHAR txData;
	txData = 0x00;
	TxI2CMessage(ITG3200_ADDR, REG_PWR_MGM, &txData, 1);
}


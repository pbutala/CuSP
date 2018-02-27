/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "ADJDS311.h"
#include "Defines.h"
#include "Serial.h"

void ConfigureADJDS311()
{
	UCHAR txData;
	
	txData = 0x00;
	TxI2CMessage(ADJD_ADDR, REG_CONFIG, &txData, 1);
	//P2OUT &= ~ADJD_SLP;
	//_delay_cycles(DLY_1MHz_10u);
	//P2OUT |= ADJD_SLP;
	/*P2OUT &= ~ADJD_RST;
	_delay_cycles(DLY_1MHz_10u);*/ 
	
	txData = 0x00;//0x07 = 8 capacitors
	TxI2CMessage(ADJD_ADDR, REG_CAP_RED, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_CAP_GREEN, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_CAP_BLUE, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_CAP_CLEAR, &txData, 1);
	
	txData = 0x00;//
	TxI2CMessage(ADJD_ADDR, REG_INT_RED_HI, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_GREEN_HI, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_BLUE_HI, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_CLEAR_HI, &txData, 1);
	
	txData = 0x0F;//
	TxI2CMessage(ADJD_ADDR, REG_INT_RED_LO, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_GREEN_LO, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_BLUE_LO, &txData, 1);
	TxI2CMessage(ADJD_ADDR, REG_INT_CLEAR_LO, &txData, 1);
}

void ResetADJDS311()
{
	P2OUT |= ADJD_RST;
	_delay_cycles(DLY_1MHz_10u);
	P2OUT &= ~ADJD_RST;
	_delay_cycles(DLY_1MHz_10u);
	P2OUT |= ADJD_RST;
	_delay_cycles(DLY_1MHz_10u);
}

void SleepADJDS311(bool slp)
{
	if(slp)
		P2OUT |= ADJD_SLP;
	else
		P2OUT &= ~ADJD_SLP;
}

void GetADJDS311Data(unsigned char *buffer)
{
	UCHAR txData;
	txData = AJ_GSSR;
	TxI2CMessage(ADJD_ADDR, REG_CTRL, &txData, 1);
	while(txData & AJ_GSSR)
	{
		RxI2CMessage(ADJD_ADDR, REG_CTRL, &txData, 1);	// Read CTRL reg to get end of conversion
	}
	
	RxI2CMessage(ADJD_ADDR, REG_DATA_RED_LO, buffer, ADJD_DATA_LEN);	// Read 4ch RGBC data
}

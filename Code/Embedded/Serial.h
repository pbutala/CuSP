/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef SERIAL_H_
#define SERIAL_H_

#include "Defines.h"

void ConfigureSPI(void);
void ConfigureANTModule(void);
unsigned char RxByte();
void TxByte(unsigned char);
void TxInitiateHandshake(void);
void TxMessageToAnt(void);
void RxMessageFromAnt(void);

void ConfigureI2C(void);

void LockUSCIModule(void);

void TxI2CMessage(UCHAR DevAddr, UCHAR RegAddr, UCHAR* DataArr, int length);
void RxI2CMessage(UCHAR DevAddr, UCHAR RegAddr, UCHAR* RxBuf, int length);

#endif /*SERIAL_H_*/

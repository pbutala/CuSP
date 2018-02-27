/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Defines.h"
#include "Utilities.h"
#include "Serial.h"
#include "GPIO.h"
#include "ANTmtds.h"

UCHAR SPIRxByte;
// configures the SPI module to act as Slave serial module
void ConfigureSPI(void)
{
	/*USICKCTL = USICKPL;				// Clock Idle polarity is High
	USICTL1 = USIIE;				// Interrupt enable
	USICTL0 = USIPE7 + USIPE6 + USIPE5 + USILSB + USIOE;	// SCLk config as IP, LSB first and op enable
	USICTL0 &= ~USISWRST;			// Release USI module
	USICNT = USICNT3;				// Set 8 bit to receive*/
	/*UCA0CTL0 = UCCKPL + UCSYNC;				// Clock Idle polarity is High
	UCA0CTL1 &= ~UCSWRST;			// Release USCI module
	//IE2 |= UCA0TXIE + UCA0RXIE;
	IE2 |= UCA0RXIE;*/
	
	UCB1CTL0 = UCCKPL + UCSYNC;				// Clock Idle polarity is High
	UCB1CTL1 &= ~UCSWRST;			// Release USCI module
	//UC1IFG &= ~UCB1RXIE;
	//UC1IFG &= ~UCA1RXIE;
	UC1IFG = 0x00;
	UC1IE = UCB1RXIE;
	//UCB1CTL1 &= ~UCSWRST;			// Release USCI module
}

void LockUSCIModule(void)
{
	UC1IE &= ~UCB1RXIE;
	UCB1CTL1 |= UCSWRST;			// Release USCI module
}

// Receives a byte from ANT module
UCHAR RxByte()
{	
	UCB1TXBUF = 0x33;
	fCOMFLAG &= ~fSerDone;
	AssertSRDY();					// Pulse SRDY to tx/rx byte
	while(!(fCOMFLAG & fSerDone)){	// Wait till SPI flags serial transaction done
		//_delay_cycles(DLY_1MHz_10u);
	}
	fCOMFLAG &= ~fSerDone;			// Reset serial transaction flag
	//return UCA0RXBUF;					// Return received byte
	return SPIRxByte;					// Return received byte
}

// Transmits a byte to ANT module
void TxByte(UCHAR data)
{
	UCB1TXBUF = data;					// Load shift register with data to transmit
	fCOMFLAG &= ~fSerDone;
	AssertSRDY();					// Pulse SRDY to tx/rx byte
	while(!(fCOMFLAG & fSerDone)){	// Wait till SPI flags serial transaction done
		//_delay_cycles(DLY_1MHz_10u);
	}
	fCOMFLAG &= ~fSerDone;			// Reset serial transaction flag
}

// initiate Tx MCU->ANT by transition MRDY H->L
void TxInitiateHandshake()
{
	if((serTxArr[0] > 0) && (serTxArr[0] <= DATAMAX))	// If data length specified is OK
	{
		fCOMFLAG |= fSerBusy;		// Set serial busy flag
		P4OUT |= ANT_MRDY;			// MSGRDY low to high
		_delay_cycles(DLY_1MHz_5u);
		P4OUT &= ~ANT_MRDY;			// MSGRDY high to low
		_delay_cycles(DLY_1MHz_5u);
	}
}

// Assume handshake done and TxSYNC rcvd
void TxMessageToAnt()
{
	int i=0;						// iterator variable
	int msgLen = serTxArr[0] + 2; 	// length byte + cmd byte + data bytes (serTxArr[0] contains length of data)
	UCHAR cs;						// Checksum variable
	
	P4OUT |= ANT_MRDY;				// MSGRDY low to high
	for(; i<msgLen; i++){
		TxByte(serTxArr[i]);		// Transmit Length, CMD and Data
	}
	cs = CalcChecksum(serTxArr, msgLen, TxSYNC); // Calculate checksum
	TxByte(cs);						// Transmit checksum
	fCOMFLAG &= ~fSerBusy;			// Reset serial busy flag
}

// Assume handshake done and RxSYNC rcvd
void RxMessageFromAnt()
{
	int i=0;						// iterator variable
	int msgLen;						// variable to store length of message to receive
	UCHAR rxCh;						// received byte
	
	rxCh = RxByte();				// 1st byte is data-length
	msgLen = rxCh + 2;				// message+cs length = [CMD(1) + data] + checksum(1)
	serRxArr[0] = rxCh;				// message[0] = data length
	
	for(; i<msgLen; i++){
		serRxArr[i+1] = RxByte();	// Receive CMD, Data and checksum
	}
	fSTPEND |= fSrvRxMsgAnt;		// Set Service Received Message flag
	fCOMFLAG &= ~fSerBusy;			// Reset serial busy flag
}

/*
// USI interrupt service routine
// Invoked when specified# (8) of bits in USICNT are tx/rx
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCITX_ISR (void)
{
	//USICNT = USICNT3;				// Set 8 bits to tx/rx, also clears USI intr flag
	//IFG2 &= ~UCA0TXIFG;
	UCA0TXBUF = 0xFF;
	fCOMFLAG |= fSerDone;			// Set serial transaction done flag
}
*/

// USI interrupt service routine
// Invoked when specified# (8) of bits in USICNT are tx/rx
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR (void)
{
	/*//P5OUT |= BIT1;
	//USICNT = USICNT3;				// Set 8 bits to tx/rx, also clears USI intr flag
	//IFG2 &= ~UCA0RXIFG;
	SPIRxByte = UCA0RXBUF;
	fCOMFLAG |= fSerDone;			// Set serial transaction done flag
	//P5OUT &= ~BIT1;*/
}

// USI interrupt service routine
// Invoked when specified# (8) of bits in USICNT are tx/rx
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCIAB1RX_ISR (void)
{
	//P5OUT |= BIT1;
	//USICNT = USICNT3;				// Set 8 bits to tx/rx, also clears USI intr flag
	//IFG2 &= ~UCA0RXIFG;
	SPIRxByte = UCB1RXBUF;
	fCOMFLAG |= fSerDone;			// Set serial transaction done flag
	//P5OUT &= ~BIT1;
}

// configures the I2C module as master to talk to ACC and GYRO
void ConfigureI2C(void)
{
	UCB0CTL0 |= (UCMST + UCMODE1 + UCMODE0 + UCSYNC);	// Master, I2C mode
	UCB0CTL1 |= UCSSEL_2;			// Select SMCLK as clk source
	//UCB0BR0 = 0x0C;					// Set clk prescalar = 8 (1Mhz/12 ~ 83.33kHz)
	//UCB0BR0 = 0x08;					// Set clk prescalar = 8 (1Mhz/8 = 125kHz)
	UCB0BR0 = 0x03;					// Set clk prescalar = 8 (1Mhz/3 ~ 333.33kHz)
	UCB0BR1 = 0x00;
	UCB0CTL1 &= ~UCSWRST;			// Release USI module
}

void TxI2CMessage(UCHAR DevAddr, UCHAR RegAddr, UCHAR* DataArr, int length)
{
	int i;
	UCB0I2CSA = DevAddr;			// Slave Addr = Device Address
	UCB0CTL1 |= UCTR;				// I2C Master transmit mode
	UCB0CTL1 |= UCTXSTT;			// START
	
	while(!(IFG2 & UCB0TXIFG));		// Start generated, OK to write data to buffer
	UCB0TXBUF = RegAddr;			// Write register address to buffer
	
	for(i=0; i<length; i++){
		while(!(IFG2 & UCB0TXIFG));	// Wait for OK to write data to buffer
		UCB0TXBUF = DataArr[i];		// Write data to buffer
	}
	while(!(IFG2 & UCB0TXIFG));		// Wait for OK to write data to buffer
	UCB0CTL1 |= UCTXSTP;			// STOP
	IFG2 &= ~UCB0TXIFG;				// Clear flag
}

void RxI2CMessage(UCHAR DevAddr, UCHAR RegAddr, UCHAR* RxBuf, int length)
{
	int i;
	TxI2CMessage(DevAddr, RegAddr, 0, 0);	// Transmit register address to read from to slave
	
	UCB0CTL1 &= ~UCTR;				// I2C Master Rx mode
	UCB0CTL1 |= UCTXSTT;			// START
	
	while(UCB0CTL1 & UCTXSTT);		// Wait till slave address ack
	
	for(i=0; i<(length-1); i++){	// if more than 1 byte data to be rcvd 
		while(!(IFG2 & UCB0RXIFG)); // Wait for byte rcvd flag
	    RxBuf[i] = UCB0RXBUF;		// Read Rx buffer; automatically starts next byte read
	}
		
	UCB0CTL1 |= UCTXSTP;			// Set STOP flag during last byte read
	while(!(IFG2 & UCB0RXIFG));		// Wait for byte rcvd flag
	RxBuf[i] = UCB0RXBUF;			// Read last byte
}

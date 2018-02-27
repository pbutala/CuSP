/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Serial.h"
#include "Defines.h"
#include "GPIO.h"

int temp = 0;
// Configure the GPIO module
void ConfigureGPIO()
{ 	
	P1DIR = 0xFF;
	P1DIR = ~ADXL_INT2;// currently using only int1
	P1DIR &= ~ADXL_INT1;
	P1DIR &= ~ITG_INTR;
	P1DIR &= ~TCS71_INTR;
	P1DIR &= ~TCS_INTR;
	
	P2DIR = 0xFF;
	P2DIR &= ~ANT_SEN;
	//P2REN = ADJD_RST + ADJD_SLP;
	//P2REN = 0x00;
	P2IFG = 0x00;
	//P2IE = ANT_SEN; /*+ ITG_INTR + ADXL_INT1*/	// enable interrupt on P1.0,1
	P2IES = ANT_SEN; /*+ ITG_INTR + ADXL_INT1*/	// intr on H-L transition
  	
  	 
  	P3DIR = 0xFF;
	P3DIR &= ~I2C_SDA;
	P3DIR &= ~I2C_SCL;
	P3SEL |= I2C_SDA + I2C_SCL; 	// P3.I2C
	
	P4DIR = 0xFF;
	P4OUT = ANT_MRDY + ANT_SRDY + ANT_RST;     // clear output pins. Set ant reset, mrdy and srdy high
	//P4OUT = ANT_MRDY + ANT_SRDY + ANT_RST;     // clear output pins. Set ant reset, mrdy and srdy high
	
	P5DIR = 0xFF;
	P5DIR &= ~SPI_DI;
	P5DIR &= ~SPI_CLK;
	//P5REN = SPI_CLK;
	P5SEL |= SPI_DI + SPI_DO + SPI_CLK; 	// P5.SPI
}

// Pulses the SRDY pin HLH
void AssertSRDY(void)
{
	P4OUT |= ANT_SRDY;						// SRDY low to high
	_delay_cycles(DLY_1MHz_5u);
	P4OUT &= ~ANT_SRDY;						// SRDY high to low
	_delay_cycles(DLY_1MHz_5u);				
	P4OUT |= ANT_SRDY;						// SRDY low to high
}

// Resets the ANT module by asserting the hardware reset pin
void ResetANTModule(void)
{
	int i = 0;
	P2IE &= ~ANT_SEN;	// disable interrupt on P1.0,1
	fCOMFLAG &= ~fAntRstOK;
	P4OUT|= ANT_RST;
	_delay_cycles(DLY_1MHz_250u);
	for(i=0;i<600;i++){
		_delay_cycles(DLY_1MHz_1m);	
	}
	P4OUT &= ~ANT_RST;						// apply reset to ANT module
  	_delay_cycles(DLY_1MHz_250u);						
  	P4OUT |= ANT_RST;							// apply reset to ANT module
  	_delay_cycles(DLY_1MHz_250u);
  	
  	for(i=0;i<600;i++){
		_delay_cycles(DLY_1MHz_1m);	
	}
  	
  	ConfigureSPI();					// Configure SPI to talk to ANT module
  	P2IFG &= 0x00;
  	P2IE = ANT_SEN; /*+ ITG_INTR + ADXL_INT1*/	// enable interrupt on P1.0,1
  	
  	/*while(!(fCOMFLAG & fAntRstOK)){	// Wait till SEN intr received and tx Sync rcvd
		_delay_cycles(DLY_1MHz_250u);
	}*/
	fCOMFLAG |= fAntRstOK; // DELETE for AP2
			
  	//***********************
}

// P1 interrupt service routine
// Invoked when the SEN transitions H-L
#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR (void)
{
	/*UCHAR sync;
	if(P1IFG & ANT_SEN){
		P1IFG &= ~ANT_SEN;						// Reset P2_INTR flag
		_bis_SR_register(GIE);					// turn on interrupts for serial since SR is
		
		fCOMFLAG |= fSerBusy;					// Set Serial Busy Comm Flag
		sync = RxByte();						// Receive SYNC byte from ANT
		if(sync == RxSYNC){						// If sync commands to receive
			fSTPEND |= fRxMsgAnt;				// Set receive message flag
			fCOMFLAG |= fAntRstOK;
			P4OUT |= ANT_MRDY;
		}
		else if(sync == TxSYNC){				// If sync commands to transmit
			fSTPEND |= fTxMsgAnt;				// Set transmit message flag
		}
		else{									// If garbage sync, set flag to reset ant module
			fSTPEND |= fResetAnt;
		}
	}
	else if(P1IFG & ITG_INTR){
		P1IFG &= ~ITG_INTR;
		//fSTPEND |= fGyrDtRdy;
	}
	else if(P1IFG & ADXL_INT1){
		P1IFG &= ~ADXL_INT1;
		//fSTPEND |= fAccDtRdy;
	}
	else{
		P1IFG &= ~ADXL_INT1;//TODO: Just for debug DELETE THIS
	}*/
}

// P2 interrupt service routine
// Invoked when the SEN transitions H-L
#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR (void)
{
	UCHAR sync;
	if(P2IFG & ANT_SEN){
		P2IFG &= ~ANT_SEN;						// Reset P2_INTR flag
		_bis_SR_register(GIE);					// turn on interrupts for serial since SR is
		
		fCOMFLAG |= fSerBusy;					// Set Serial Busy Comm Flag
		sync = RxByte();						// Receive SYNC byte from ANT
		if(sync == RxSYNC){						// If sync commands to receive
			fSTPEND |= fRxMsgAnt;				// Set receive message flag
			//fCOMFLAG |= fAntRstOK;
			//P4OUT |= ANT_MRDY;
		}
		else if(sync == TxSYNC){				// If sync commands to transmit
			fSTPEND |= fTxMsgAnt;				// Set transmit message flag
			//fSTPEND &= ~fTxWaitAnt;				// Done waiting to receive SEN and TxSYNC from ANT module
		}
		else{									// If garbage sync, set flag to reset ant module
			fSTPEND |= fResetAnt;
		}
	}
}

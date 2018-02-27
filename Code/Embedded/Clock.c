/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Clock.h"

void ConfigureBCS(void)
{
 if (CALBC1_1MHZ == TAG_EMPTY || CALDCO_1MHZ == TAG_EMPTY)                                       
   FaultRoutine();		                    // If calibration data is erased
 				                            // run FaultRoutine()
  BCSCTL1 = CALBC1_1MHZ; 					// Set range
  DCOCTL = CALDCO_1MHZ;  					// Set DCO step + modulation 
  BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  BCSCTL2 = 0;         
  
  // MCLK => DCO -> 1MHz; DIVM = 1;
  // SMCLK => DCO -> 1MHz; DIVS = 1;
  // ACLK => VLO -> 12kHz
}

void FaultRoutine(void)
 {
   P1OUT = BIT0;                            // P1.0 on (red LED)
   while(1); 			                    // TRAP
 }

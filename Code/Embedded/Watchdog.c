/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>

void ConfigureWDT(void)
{
	WDTCTL = WDTPW + WDTHOLD;			// Stop watchdog timer
}

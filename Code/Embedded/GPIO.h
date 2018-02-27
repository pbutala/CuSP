/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef GPIO_H_
#define GPIO_H_

void ConfigureGPIO(void);
void AssertSRDY(void);					// pulse SRDY -> HLH
void ResetANTModule(void);					

#endif /*GPIO_H_*/

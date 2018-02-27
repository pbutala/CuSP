/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "Defines.h"
#include "Utilities.h"

// Returns the checksum of the values in array 
UCHAR CalcChecksum(UCHAR array[], int length, UCHAR sync)
{
	int i = 0;
	UCHAR cs = sync;
	for(;i<length;i++){
		cs ^= array[i];
	}
	return cs;
}

/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "DataRoutines.h"
#include "Defines.h"
#include "Serial.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "ADJDS311.h"
#include "TCS3414.h"
#include "TCS3471.h"

void GetSensorData(UCHAR snsrID)
{
	switch(snsrID){
		case SENSOR_TCS3471:
			GetTCS3471Data(TxDataBuffer);
			break;
		case SENSOR_TCS3414:
			GetTCS3414Data(TxDataBuffer);
			break;
		case SENSOR_ADXL345:
			GetADXL345Data(TxDataBuffer);
			break;
		case SENSOR_ITG3200:
			GetITG3200Data(TxDataBuffer);
			break;
	}
}

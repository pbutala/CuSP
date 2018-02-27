/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef ADXL345_H_
#define ADXL345_H_
#include "Defines.h"

// ADXL345 methods
void ConfigureADXL345(void);
void GetADXL345Data(unsigned char *buffer);
void SleepADXL345(bool slp);
void StartMeasureADXL345(void);

// Data bufffer
#define ADXL_DATA_LEN		6

#define ADXL345_ADDR		0x53	// 7-bit accel slave address. shift and add bit0 to W/r

// ADXL345 register map
#define REG_DEVID			0x00	// Device ID; 								Reset: 0xE5
#define REG_THRESH_TAP		0x1D	// Tap threshold
#define REG_OFSX			0x1E	// X-Axis offset
#define REG_OFSY			0x1F	// Y-Axis offset
#define REG_OFSZ			0x20	// Z-Axis offset
#define REG_DUR				0x21	// Tap duration
#define REG_Latent			0x22	// Tap latency
#define REG_Window			0x23	// Tap window
#define REG_THRESH_ACT		0x24	// Activity threshold (UCHAR, 62.5 mg/LSB)
#define REG_THRESH_INACT	0x25	// Inactivity threshold	(UCHAR, 62.5 mg/LSB)
#define REG_TIME_INACT		0x26	// Inactivity time (UCHAR, 1sec/LSB)
#define REG_ACT_INACT_CTL	0x27	// Axis enable control for activity and inactivity detection
#define REG_THRESH_FF		0x28	// Free-fall threshold (UCHAR, 62.5 mg/LSB) (Recommended 0x05(300mg)-0x09(600mg))
#define REG_TIME_FF			0x29	// Free-fall time	(UCHAR, 5ms/LSB) (Recommended 0x14(100ms)-0x46(350ms))
#define REG_TAP_AXES		0x2A	// Axis control for tap/double tap
#define REG_ACT_TAP_STATUS	0x2B	// Source of tap/double tap
#define REG_BW_RATE			0x2C	// Data rate and power mode control; 		Reset: 0x0A
#define REG_POWER_CTL		0x2D	// Power saving features control
#define REG_INT_ENABLE		0x2E	// Interrupt enable control
#define REG_INT_MAP			0x2F	// Interrupt mapping control
#define REG_INT_SOURCE		0x30	// Source of interrupts; 					Reset: 0x02
#define REG_DATA_FORMAT		0x31	// Data format control
#define REG_DATAX0			0x32	// X-Axis Data 0 (LSB)
#define REG_DATAX1			0x33	// X-Axis Data 1 (MSB)
#define REG_DATAY0			0x34	// Y-Axis Data 0 (LSB)
#define REG_DATAY1			0x35	// Y-Axis Data 1 (MSB)
#define REG_DATAZ0			0x36	// Z-Axis Data 0 (LSB)
#define REG_DATAZ1			0x37	// Z-Axis Data 1 (MSB)
#define REG_FIFO_CTL		0x38	// FIFO control
#define REG_FIFO_STATUS		0x39	// FIFO status

#define REG_DEVID_RESET		0xE5

// REG_ACT_INACT_CTL definations
#define ACT_AC_DC			0x80
#define ACT_X_EN			0x40
#define ACT_Y_EN			0x20
#define ACT_Z_EN			0x10
#define INACT_AC_DC			0x08
#define INACT_X_EN			0x04
#define INACT_Y_EN			0x02
#define INACT_Z_EN			0x01

// REG_TAP_AXES definations
#define SUPPRESS			0x08
#define TAP_X_EN			0x04
#define TAP_Y_EN			0x02
#define TAP_Z_EN			0x01

// REG_BW_RATE definations
#define LOW_POWER			0x10
									/*BW(Hz)	Data op(Hz)	*/
#define RATE_0				0x00	/*	-			-		*/
#define RATE_1				0x01	/*	-			-		*/
#define RATE_2				0x02	/*	-			-		*/
#define RATE_3				0x03	/*	-			-		*/
#define RATE_4				0x04	/*	-			-		*/
#define RATE_5				0x05	/*	-			-		*/
#define RATE_6				0x06	/*	 3.125		  6.25	*/
#define RATE_7				0x07	/*	 6.25	     12.5	*/
#define RATE_8				0x08	/*	12.5		 25		*/
#define RATE_9				0x09	/*  25			 50		*/
#define RATE_10				0x0A	/*  50			100		*/
#define RATE_11				0x0B	/* 100			200		*/
#define RATE_12				0x0C	/* 200			400		*/
#define RATE_13				0x0D	/* 400			800		*/
#define RATE_14				0x0E	/* 800		   1600		*/
#define RATE_15				0x0F	/*1600		   3200		*/

// REG_POWER_CTL definations
#define LINK				0x20
#define AUTO_SLEEP			0x10
#define MEASURE				0x08
#define ADXL_SLEEP			0x04
#define WAKEUP_0			0x00	/* 8Hz */
#define WAKEUP_1			0x01	/* 4Hz */
#define WAKEUP_2			0x02	/* 2Hz */
#define WAKEUP_3			0x03	/* 1Hz */

// REG_INT_ENABLE/REG_INT_MAP/REG_INT_SOURCE definations
#define DATA_READY			0x80
#define SINGLE_TAP			0x40
#define DOUBLE_TAP			0x20
#define ACTIVITY			0x10
#define INACTIVITY			0x08
#define FREE_FALL			0x04
#define WATERMARK			0x02
#define OVERRUN				0x01

// REG_DATA_FORMAT definations
#define SELF_TEST			0x80
#define SPI					0x40
#define INT_INVERT			0x20

#define FULL_RES			0x08
#define JUSTIFY				0x04
#define RANGE_0				0x00	/* ±2g */
#define RANGE_1				0x01	/* ±4g */
#define RANGE_2				0x02	/* ±8g */
#define RANGE_3				0x03	/* ±16g */

// REG_FIFO_CTL definations
#define FIFO_MODE_0			0x00	/* Bypass */
#define FIFO_MODE_1			0x40	/* FIFO */
#define FIFO_MODE_2			0x80	/* Stream */
#define FIFO_MODE_3			0xC0	/* Trigger */

#define TRIGGER				0x20
#define SAMPLES4			0x10
#define SAMPLES3			0x08
#define SAMPLES2			0x04
#define SAMPLES1			0x02
#define SAMPLES0			0x01

// REG_FIFO_STATUS definations
#define FIFO_TRIG			0x80

#define ENTRIES5			0x20
#define ENTRIES4			0x10
#define ENTRIES3			0x08
#define ENTRIES2			0x04
#define ENTRIES1			0x02
#define ENTRIES0			0x01

#endif /*ADXL345_H_*/

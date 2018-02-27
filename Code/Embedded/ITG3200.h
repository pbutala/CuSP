/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef ITG3200_H_
#define ITG3200_H_
#include "Defines.h"
// ITG3200 methods
void ConfigureITG3200(void);
void GetITG3200Data(unsigned char *buffer);
void SleepITG3200(bool slp);
void StartMeasureITG3200(void);

// data buffer
#define ITG_DATA_GT_LEN		8
#define ITG_DATA_G_LEN		6

#define ITG3200_ADDR		0x69	// 7-bit gyro slave address. shift and add bit0 to W/r

// ITG3200 register map
#define REG_WHO_AM_I		0x00	// Device ID; 								Reset: 0x69
#define REG_SMPLRT_DIV		0x15	// Sample Rate Divider (UCHAR)
#define REG_DLPF_FS			0x16	// Digital Low Pass Filter Config
#define REG_INT_CFG			0x17	// Interrupt configuration
#define REG_INT_STATUS		0x1A	// Interrupt Status
#define REG_TEMP_OUT_H		0x1B	// TEMP_OUT_H/L 16-bit temperature data (2’s complement format)
#define REG_TEMP_OUT_L		0x1C	//
#define REG_GYRO_XOUT_H		0x1D	// 16-bit X gyro output data (2’s complement format)
#define REG_GYRO_XOUT_L		0x1E	//
#define REG_GYRO_YOUT_H		0x1F	// 16-bit Y gyro output data (2’s complement format)
#define REG_GYRO_YOUT_L		0x20	//
#define REG_GYRO_ZOUT_H		0x21	// 16-bit Y gyro output data (2’s complement format)
#define REG_GYRO_ZOUT_L		0x22	//
#define REG_PWR_MGM			0x3E	// Power Management

// REG_DLPF_FS
#define FS_SEL_0			0x00	/*reserved*/
#define FS_SEL_1			0x08	/*reserved*/
#define FS_SEL_2			0x10	/*reserved*/
#define FS_SEL_3			0x18	/*±2000°/sec*/
									/*BW(Hz)	SampRate(kHz)*/
#define DLPF_CFG_0			0x00	/*256			8		 */
#define DLPF_CFG_1			0x01	/*188			1		 */
#define DLPF_CFG_2			0x02	/* 98			1		 */
#define DLPF_CFG_3			0x03	/* 42			1		 */
#define DLPF_CFG_4			0x04	/* 20			1		 */
#define DLPF_CFG_5			0x05	/* 10			1		 */
#define DLPF_CFG_6			0x06	/*  5			1		 */
#define DLPF_CFG_7			0x07	/*  -			-		 */

// REG_INT_CFG
#define ACTL				0x80	/* Logic level for INT pin 1=AL, 0=AH */
#define OPEN				0x40	/* Drive Type for INT pin 1=OpenDrain, 0=PushPull */
#define LATCH_INT_EN		0x20	/* Latch Mode 1=Latch till INT cleared, 0=50us pulse */
#define INT_ANYRD_2CLEAR	0x10	/* Latch Clear Method 1=Any Reg Read, 0=Stat Reg Read Only */
#define INT_RDY_EN			0x04	/* Enable INT when device is ready (PLL ready after changing clock source) */
#define RAW_RDY_EN			0x01	/* Enable interrupt when data is available */

// REG_INT_STATUS
#define ITG_RDY 			0x04	/* PLL ready*/
#define RAW_DATA_RDY 		0x01	/* Raw data is ready*/

// REG_PWR_MGM
#define H_RESET 			0x80	/* Reset device and internal registers to the power-up-default settings */
#define SLEEP 				0x40	/* Enable low power sleep mode */
#define STBY_XG 			0x20	/* Put gyro X in standby mode (1=standby, 0=normal) */
#define STBY_YG 			0x10	/* Put gyro Y in standby mode (1=standby, 0=normal) */
#define STBY_ZG 			0x08	/* Put gyro Z in standby mode (1=standby, 0=normal) */
									/* Select device clock source */
#define CLK_SEL_0 			0x00	/* Internal oscillator */
#define CLK_SEL_1 			0x01	/* PLL with X Gyro reference */
#define CLK_SEL_2 			0x02	/* PLL with Y Gyro reference */
#define CLK_SEL_3 			0x03	/* PLL with Z Gyro reference */
#define CLK_SEL_4 			0x04	/* PLL with external 32.768kHz reference */
#define CLK_SEL_5 			0x05	/* PLL with external 19.2MHz reference */
#define CLK_SEL_6 			0x06	/* RESERVED */
#define CLK_SEL_7 			0x07	/* RESERVED */

#endif /*ITG3200_H_*/

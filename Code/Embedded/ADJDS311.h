/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012 
 ***********************************************************************************/ 
#ifndef ADJDS311_H_
#define ADJDS311_H_

#endif /*ADJDS311_H_*/

#include "Defines.h"
// internal clock frequency is typical 26 MHz
//ADJDS311 methods
void ConfigureADJDS311(void);
void GetADJDS311Data(unsigned char*);
void ResetADJDS311(void);
void SleepADJDS311(bool slp);

// Data bufffer
#define ADJD_DATA_LEN		8
#define ADJD_OFFSET_LEN		4

#define ADJD_ADDR		0x74	// 7-bit accel slave address. shift and add bit0 to W/r
//#define ADJD_ADDR		0xE8	// 7-bit accel slave address. shift and add bit0 to W/r

// ADJDS311 register map
#define REG_CTRL			0x00	// Control Register
#define REG_CONFIG			0x01	// Configuration Register
#define REG_CAP_RED			0x06	// Capacitor Settings Register for Red Channel		Reset: 15
#define REG_CAP_GREEN		0x07	// Capacitor Settings Register for Green Channel	Reset: 15
#define REG_CAP_BLUE		0x08	// Capacitor Settings Register for Blue Channel		Reset: 15
#define REG_CAP_CLEAR		0x09	// Capacitor Settings Register for Clear Channel	Reset: 15
#define REG_INT_RED_LO		0x0A	// Integration Time Slot Setting Register for Red Channel
#define REG_INT_RED_HI		0x0B	//
#define REG_INT_GREEN_LO	0x0C	// Integration Time Slot Setting Register for Green Channel
#define REG_INT_GREEN_HI	0x0D	//
#define REG_INT_BLUE_LO		0x0E	// Integration Time Slot Setting Register for Blue Channel
#define REG_INT_BLUE_HI		0x0F	//
#define REG_INT_CLEAR_LO	0x10	// Integration Time Slot Setting Register for Clear Channel
#define REG_INT_CLEAR_HI	0x11	//
#define REG_DATA_RED_LO		0x40	// Red Channel Sensor ADC Reading
#define REG_DATA_RED_HI		0x41	// 
#define REG_DATA_GREEN_LO	0x42	// Green Channel Sensor ADC Reading
#define REG_DATA_GREEN_HI	0x43	// 
#define REG_DATA_BLUE_LO	0x44	// Blue Channel Sensor ADC Reading
#define REG_DATA_BLUE_HI	0x45	// 
#define REG_DATA_CLEAR_LO	0x46	// Clear Channel Sensor ADC Reading
#define REG_DATA_CLEAR_HI	0x47	// 
#define REG_OFFSET_RED		0x48	// Offset Data Register for Red Channel
#define REG_OFFSET_GREEN	0x49	// Offset Data Register for Green Channel
#define REG_OFFSET_BLUE		0x4A	// Offset Data Register for Blue Channel
#define REG_OFFSET_CLEAR	0x4B	// Offset Data Register for Clear Channel

// REG_CTRL definations
#define AJ_GSSR				0x01	// Get sensor reading. Active high and automatically cleared. Result is stored in registers 64-71 (DEC)
#define AJ_GOFS				0x02	// Get offset reading. Active high and automatically cleared. Result is stored in registers 72-75 (DEC)

// REG_CONFIG definations
#define AJ_TOFS				0x01	// Trim offset mode. Active high.
#define AJ_SLEEP				0x02	// Sleep mode. Active high and external clock mode only. Automatically cleared if otherwise.
#define AJ_EXTCLK				0x04	// External clock mode. Active high.

//// REG_CAP_XX definations
//#define CAP_XX				0x0F	// INT_XX[3:0]; # of XX channel capacitors 
//
//// REG_INT_XX_LO definations
//#define INT_LO_XX			0xFF	// INT_XX[7:0]
//// REG_INT_XX_HI definations
//#define INT_HI_XX			0x0F	// INT_XX[11:8]
//
//// REG_DATA_XX_LO definations
//#define DATA_LO_XX			0xFF	// DATA_XX[7:0]
//// REG_DATA_XX_HI definations
//#define DATA_HI_XX			0x03	// DATA_XX[9:8]
//
//// REG_OFFSET_XX definations
//#define SIGN_XX				0x80	// Sign bit. 0 = POSITIVE, 1 = NEGATIVE.
//#define OFFSET_XX			0x3F	// XX channel ADC offset data. (XX = RGBC)

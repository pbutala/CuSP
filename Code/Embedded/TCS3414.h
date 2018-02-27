/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef TCS3414_H_
#define TCS3414_H_

#endif /*TCS3414_H_*/
// TCS3414 methods
void ConfigureTCS3414(void);
void PowerOnTCS3414(void);
void PowerOffTCS3414(void);
void GetTCS3414Data(unsigned char *buffer);

// Data bufffer
#define TCS_DATA_LEN		8

#define TCS_ADDR		0x39	// [011 1001]b 7-bit tri color sensor (TAOS) slave address. shift and add bit0 to W/r

// TCS3414 register map
#define TCS_REG_CTRL		0x00	// Control Register
#define TCS_REG_TIMING		0x01	// Integration time/gain control
#define TCS_REG_INTR		0x02	// Interrupt control
#define TCS_REG_INTSRC		0x03	// Interrupt source
#define TCS_REG_ID			0x04	// Part number/ Rev ID
#define TCS_REG_GAIN		0x07	// ADC gain control
#define TCS_REG_LOTH_LO		0x08	// Low byte of low interrupt threshold
#define TCS_REG_LOTH_HI		0x09	// High byte of low interrupt threshold
#define TCS_REG_HITH_LO		0x0A	// Low byte of high interrupt threshold
#define TCS_REG_HITH_HI		0x0B	// High byte of high interrupt threshold
#define TCS_REG_DATA_G_LO	0x10	// Low byte of ADC green channel
#define TCS_REG_DATA_G_HI	0x11	// High byte of ADC green channel
#define TCS_REG_DATA_R_LO	0x12	// Low byte of ADC red channel
#define TCS_REG_DATA_R_HI	0x13	// High byte of ADC red channel
#define TCS_REG_DATA_B_LO	0x14	// Low byte of ADC blue channel
#define TCS_REG_DATA_B_HI	0x15	// High byte of ADC blue channel
#define TCS_REG_DATA_C_LO	0x16	// Low byte of ADC clear channel
#define TCS_REG_DATA_C_HI	0x17	// High byte of ADC clear channel

/*
 * SMB PROTOCOL
 */
 #define TCS_CMD_BYTE		0x80	// CMD + Byte Protocol
 #define TCS_CMD_WORD		0xA0	// CMD + Word Protocol
 #define TCS_CMD_BLOCK		0xC0	// CMD + Block Protocol
 #define TCS_CMD_INTCLR		0xE0	// CMD + Interrupt Clear

// TCS_REG_CTRL definations
/*
 * 1. Both ADC_EN and POWER must be asserted before the ADC channels will operate correctly.
 * 2. INTEG_MODE and TIME/COUNTER fields in the Timing Register (01h) should be written before ADC_EN is asserted.
 * 3. If a value of 03h is written, the value returned during a read cycle will be 03h. 
 * 	  This feature can be used to verify that the device is communicating properly.
 * 4. During writes and reads, the POWER bit is overridden and the oscillator is enabled, 
 *    independent of the state of POWER.
 */
#define TCS_ADC_VALID		0x10	// This read-only field indicates that the ADC channel has completed an integration cycle
#define TCS_ADC_EN			0x02	// (1:Activate; 0:Disable) all ADC channels
#define TCS_POWER			0x01	// 1:ON; 0:OFF

// TCS_REG_TIMING definations
#define TCS_SYNC_EDGE		0x40	// (0:falling; 1:rising) stop INTEG_MODE cycle on selected edge of the sync pin
#define TCS_INTEG_MODE_FR	0x00	// free running integrator; internally-generated Nominal Integration Times is selected for each conversion
#define TCS_INTEG_MODE_MNL	0x10	// Manually start/stop integration through serial bus using ADC_EN field in Control Register
#define TCS_INTEG_MODE_ONE	0x20	// One integration cycle; internal NOMINAL INTEGRATION TIME; 2.4 us after SYNC IN
#define TCS_INTEG_MODE_PLS	0x30	// Integrate over specified number of pulses on SYNC IN pin. Minimum width of sync pulse is 50 us. SYNC IN must be low at least 3.6 us
#define TCS_NIT_12ms		0x00	// Nominal Integration Time: 12ms
#define TCS_NIT_100ms		0x01	// Nominal Integration Time: 100ms
#define TCS_NIT_400ms		0x02	// Nominal Integration Time: 400ms
#define TCS_SYNC_PLS_1		0x00	// Pulse Count: 1
#define TCS_SYNC_PLS_2		0x01	// Pulse Count: 2
#define TCS_SYNC_PLS_4		0x02	// Pulse Count: 4
#define TCS_SYNC_PLS_8		0x03	// Pulse Count: 8
#define TCS_SYNC_PLS_16		0x04	// Pulse Count: 16
#define TCS_SYNC_PLS_32		0x05	// Pulse Count: 32
#define TCS_SYNC_PLS_64		0x06	// Pulse Count: 64
#define TCS_SYNC_PLS_128	0x07	// Pulse Count: 128
#define TCS_SYNC_PLS_256	0x08	// Pulse Count: 256

// TCS_REG_INTR definations
#define TCS_INTR_STOP		0x40	// ADC integration will stop once an interrupt is asserted

#define TCS_INTR_DISABLE	0x00	// Interrupt output disabled
#define TCS_INTR_LEVEL		0x10	// Level Interrupt
#define TCS_INTR_SMB		0x20	// SMB-Alert compliant
#define TCS_INTR_INTSMB		0x30	// Sets an interrupt and functions as mode TCS_INTR_SMB

#define TCS_PRST_EVERY		0x00	// Every ADC cycle generates interrupt
#define TCS_PRST_SNGL		0x00	// Any value outside of threshold range
#define TCS_PRST_100ms		0x00	// Consecutively out of range for 0.1 second
#define TCS_PRST_1s			0x00	// Consecutively out of range for 1 second

// TCS_REG_INTSRC definations
 //Selects which ADC channel to use to generate an interrupt
#define TCS_INTSRC_G		0x00	// Green
#define TCS_INTSRC_R		0x01	// Red
#define TCS_INTSRC_B		0x02	// Blue
#define TCS_INTSRC_C		0x03	// Clear

// TCS_REG_GAIN definations
 //Common analog gain of the four ADC channels
#define TCS_GAIN_1X			0x00	// 1X 
#define TCS_GAIN_4X			0x10	// 4X
#define TCS_GAIN_16X		0x20	// 16X
#define TCS_GAIN_64X		0x30	// 64X
 //Prescaler. This field controls a 6-bit digital prescaler and divider. 
 //The prescaler reduces the sensitivity of each ADC integrator
#define TCS_PS_1X			0x00	// Divide by 1 
#define TCS_PS_2X			0x01	// Divide by 2
#define TCS_PS_4X			0x02	// Divide by 4
#define TCS_PS_8X			0x03	// Divide by 8
#define TCS_PS_16X			0x04	// Divide by 16
#define TCS_PS_32X			0x05	// Divide by 32
#define TCS_PS_64X			0x06	// Divide by 64

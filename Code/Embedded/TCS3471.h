/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef TCS3471_H_
#define TCS3471_H_

#endif /*TCS3471_H_*/
// TCS3414 methods
void ConfigureTCS3471(void);
void PowerOnTCS3471(void);
void PowerOffTCS3471(void);
void GetTCS3471Data(unsigned char *buffer);

// Data bufffer
#define TCS71_DATA_LEN		8

#define TCS71_ADDR				0x29	// [010 1001]b 7-bit tri color sensor (TAOS) slave address. shift and add bit0 to W/r

// TCS713414 register map
#define TCS71_REG_ENABLE		0x00	// Enables states and interrupts
#define TCS71_REG_ATIME			0x01	// RGBC ADC time
#define TCS71_REG_WTIME			0x03	// Wait time
#define TCS71_REG_AILTL			0x04	// RGBC interrupt low threshold low byte
#define TCS71_REG_AILTH			0x05	// RGBC interrupt low threshold high byte
#define TCS71_REG_AIHTL			0x06	// RGBC interrupt high threshold low byte
#define TCS71_REG_AIHTH			0x07	// RGBC interrupt high threshold high byte
#define TCS71_REG_PERS			0x0C	// Interrupt persistence filters
#define TCS71_REG_CONFIG		0x0D	// Configuration
#define TCS71_REG_CONTROL		0x0F	// Gain control register
#define TCS71_REG_ID			0x12	// Device ID
#define TCS71_REG_STATUS		0x13	// Device status
#define TCS71_REG_CDATA			0x14	// Clear ADC low data register
#define TCS71_REG_CDATAH		0x15	// Clear ADC high data register
#define TCS71_REG_RDATA			0x16	// Red ADC low data register
#define TCS71_REG_RDATAH		0x17	// Red ADC high data register
#define TCS71_REG_GDATA			0x18	// Green ADC low data register
#define TCS71_REG_GDATAH		0x19	// Green ADC high data register
#define TCS71_REG_BDATA			0x1A	// Blue ADC low data register
#define TCS71_REG_BDATAH		0x1B	// Blue ADC high data register


#define TCS71_CMD_BYTE			0x80	// CMD + Byte Protocol
#define TCS71_CMD_WORD			0xA0	// CMD + Word Protocol
#define TCS71_CMD_BLOCK			0xC0	// CMD + Block Protocol
#define TCS71_CMD_INTCLR		0xE0	// CMD + Interrupt Clear

// TCS71_REG_COMMAND definations
#define TCS71_COMMAND		0x80	// Select Command Register. Must write as 1 when addressing COMMAND register.
#define TCS71_RPT_BYTE		0x00	// Repeated byte protocol transaction
#define TCS71_AUTO_INCR		0x20	// Auto-increment protocol transaction
#define TCS71_SPC_FUNC		0x60	// Special function
#define TCS71_INTR_CLR		0x06	// RGBC INTR Clear 

// TCS71_REG_ENABLE definations
#define TCS71_AIEN			0x10	// RGBC interrupt enable. When asserted, permits RGBC interrupts to be generated
#define TCS71_WEN			0x08	// Wait enable. This bit activates the wait feature. Writing a 1 activates the wait timer. Writing a 0 disables the wait timer
#define TCS71_AEN			0x02	// RGBC enable. This bit actives the two-channel ADC. Writing a 1 activates the RGBC. Writing a 0 disables the RGBC.
#define TCS71_PON			0x01	// Power ON.

// TCS71_REG_CONTROL definations
#define TCS71_AGAIN_1X		0x00	// 1X gain
#define TCS71_AGAIN_4X		0x01	// 4X gain
#define TCS71_AGAIN_16X		0x02	// 16X gain
#define TCS71_AGAIN_60X		0x03	// 60X gain

// TCS71_REG_STATUS definations
#define TCS71_STAT_AINT		0x10	// RGBC clear channel Interrupt
#define TCS71_STAT_AVALID	0x01	// RGBC Valid. Indicates that the RGBC channels have completed an integration cycle

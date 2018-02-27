/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef DEFINES_H_
#define DEFINES_H_
#include "ANTdefines.h"

//Global defines
#define UCHAR		unsigned char
#define UINT		unsigned int
#define ULONG		unsigned long

#define bool 				UCHAR
#define true 				((UCHAR)1)
#define false 				((UCHAR)0)

#define CONFIG_I2C				0x20

#define CTRL_ANTCHANNEL				0x01
#define CTRL_CHANNELTYPE			PARAMETER_SHARED_CHANNEL
#define CTRL_DEVICENUM				0x0001     // Device number Master
#define CTRL_DEVICETYPE				0x01      // Device type
#define CTRL_TRANSTYPE				0x01      // Transmission type
#define CTRL_FREQ					250
//#define CTRL_PERIOD					32768	// 1Hz
#define CTRL_PERIOD					6554	// 5Hz
//#define CTRL_PERIOD					3277	// 10Hz
//#define CTRL_PERIOD					656	// 50Hz

#define CuSP_ANTCHANNEL				0x00      // ANT channel to use
#define CuSP_CHANNELTYPE			PARAMETER_TX_NOT_RX
#define CuSP_DEVICENUM				0x0003     // Device number
#define CuSP_DEVICETYPE				0x03      // Device type
#define CuSP_TRANSTYPE				0x03      // Transmission type
//#define CuSP_FREQ					20
#define CuSP_FREQ					101
//#define CuSP_PERIOD					32768	// 1Hz
//#define CuSP_PERIOD					3277	// 10Hz
#define CuSP_PERIOD					8192	// 4Hz
//#define CuSP_PERIOD					6554	// 5Hz
//#define CuSP_PERIOD					656		// 50Hz

#define CuSP_SHARED_CHANNELNUM_LSB			0x03     // Device number Slave
#define CuSP_SHARED_CHANNELNUM_MSB			0x00     // Device number Slave
#define SYSTEM_NETWORK_NUM			0x00	// network number

#define CTRL_DEVICE_LSB_OFFSET		0x00
#define CTRL_DEVICE_MSB_OFFSET		0x01
#define CTRL_CMD_OFFSET				0x02
#define CTRL_SENSOR_OFFSET			0x03
#define CTRL_PARAM_1_OFFSET			0x04
#define CTRL_PARAM_2_OFFSET			0x05
#define CTRL_PARAM_3_OFFSET			0x06
#define CTRL_PARAM_4_OFFSET			0x07

#define CTRL_CMD_SOURCE				0x10
#define CTRL_CMD_DATACHANNEL		0x20
#define CTRL_CMD_TXI2C				0x40
#define CTRL_CMD_RXI2C				0x41
#define CTRL_CMD_CTRLCH				0x80

#define SENSOR_NONE				0x00
#define SENSOR_TCS3414			0x39
#define SENSOR_TCS3471			0x29
#define SENSOR_ADJDS311			0x74
#define SENSOR_ADXL345			0x53
#define SENSOR_ITG3200			0x69

#define CTRL_PARAM_INVALID			0x00
#define CTRL_PARAM_ON				0x10
#define CTRL_PARAM_OFF				0x11

#define DLY_1MHz_5u	 	5
#define DLY_1MHz_10u 	10
#define DLY_1MHz_50u 	50
#define DLY_1MHz_250u 	250
#define DLY_1MHz_1m		1000

#define CNT_12kHz_1Hz	12000
#define CNT_12kHz_50Hz	240
#define CNT_12kHz_200Hz	60

//Serial defines
#define SERMAX 		16
#define DATAMAX 	SERMAX-2
#define TxSYNC      0xA5
#define RxSYNC		0xA4
extern unsigned char serTxArr[SERMAX];
extern unsigned char serRxArr[SERMAX];

//GPIO defines

// PORT1
#define ADXL_INT2 	BIT0		// ADXL345INT2 interrupt on P1.0	IP H-L edge trig
#define ADXL_INT1 	BIT1		// ADXL345INT1 interrupt on P1.1	IP H-L edge trig
#define ITG_INTR 	BIT2		// ITG-3200 interrupt on P1.2		IP H-L edge trig
#define TCS71_INTR 	BIT5		// TCS3471 interrupt on P1.5		IP H-L edge trig
#define TCS_INTR 	BIT6		// TCS3414 interrupt on P1.6		IP H-L edge trig
#define TCS_SYNC 	BIT7		// TCS3414 SYNC

// PORT2
#define ADJD_SLP 	BIT0		// ADJD S311 Sleep
#define ADJD_RST 	BIT1		// ADJD S311 Reset
#define ANT_SEN 	BIT7		// AT3 SEN

// PORT3
#define I2C_SDA		BIT1		// I2C module Data on P3.1
#define I2C_SCL		BIT2		// I2C module Clk on P3.2

// PORT4
#define LED_PWR_CTRL		BIT0		// LED1 output on P4.0
#define LED_RF_DATA			BIT1		// LED2 output on P4.1
#define LED3				BIT2		// LED3 output on P4.2
#define LED4				BIT3		// LED4 output on P4.3
#define ANT_SRDY 			BIT5		// AT3 serial ready on P4.5		OP AL
#define ANT_MRDY 			BIT6		// AT3 msg ready on P4.6		OP AL
#define ANT_RST 			BIT7		// AT3 reset on P4.7			OP AL

// PORT5
#define SPI_DI 		BIT1		// SPI module data in on P5.1	IP
#define SPI_DO 		BIT2		// SPI module data out on P5.2	OP
#define SPI_CLK 	BIT3		// SPI module clk on P5.3		IP 

extern unsigned char nxtCnfgMsgID; 
//FLAGS
extern unsigned int fSTPEND;
#define fTxIniAnt		BIT0
#define fTxMsgAnt		BIT1
#define fRxMsgAnt		BIT2
#define fSrvRxMsgAnt	BIT3
#define fTxErrAnt		BIT4
#define fRxErrAnt		BIT5
#define fConfigAnt		BIT6
#define fResetAnt		BIT7
#define fTxWaitAnt		BIT8
#define fTxCtrlAnt		BIT9
#define fTxDataAnt		BITA
#define fAccDtRdy		BITB
#define fGyrDtRdy		BITF

extern unsigned int fCOMFLAG;
#define fSerDone				BIT0
//#define fPairCmdOK			BIT1
#define fDataChannelOpen		BIT2
#define fCtrlChannelOpen		BIT3
#define fOkToBcstData			BIT4
#define fAntRstOK				BIT5
#define fSerBusy				BIT7
#define fDataChannelOpening		BIT8
#define fCtrlChannelOpening		BIT9
//#define fAcqDataRcvd			BITA
//#define fDiscovered			BITB
#define fNewCtrlCmd				BITC
//#define fLEDDataOn				BITD
#define fDEBUG					BITE
//#define fLEDCtrlOn				BITF

extern bool ADXLconfigured;
extern bool ITGconfigured;
#define ADXL_DATA		((UCHAR)1)
#define ITG_DATA		((UCHAR)2)

extern unsigned char TxDataBuffer[8];
extern unsigned char TxControlBuffer[8];

extern unsigned char SYSTEM_NW_KEY[8];
extern unsigned char ANT_CHANNEL;
extern unsigned char ANT_CHANNELTYPE;
extern unsigned int ANT_DEVICENUM;
extern unsigned char ANT_DEVICETYPE;
extern unsigned char ANT_TRANSTYPE;
extern unsigned char ANT_FREQ;
extern unsigned int ANT_PERIOD;

extern unsigned char CTRL_COMMAND;
extern unsigned char CTRL_SENSOR;
extern unsigned char CTRL_PARAM_1;
extern unsigned char CTRL_PARAM_2;
extern unsigned char CTRL_PARAM_3;
extern unsigned char CTRL_PARAM_4;

extern unsigned char DATA_SENSOR;
#endif /*DEFINES_H_*/

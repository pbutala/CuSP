#pragma once
#include "antdefines.h"
#include "antmessage.h"
#include "libant.h"
#include "Translate.h"

#define CHANNEL_TYPE_MASTER   (0)
#define CHANNEL_TYPE_SLAVE    (1)
#define CHANNEL_TYPE_INVALID  (2)

#define USER_BAUDRATE			   (57600)  // For AP1, use 50000; for AT3/AP2, use 57600
#define USER_RADIOFREQ			   (35)     // RF Frequency + 2400 MHz

#define CTRL_ANTCHANNEL				(3)
#define CTRL_DEVICENUM				(UINT)0x0001     // Device number Master
#define CTRL_DEVICETYPE				(USHORT)0x01      // Device type
#define CTRL_TRANSTYPE				(USHORT)0x01      // Transmission type
#define CTRL_FREQ					(250)
//#define CTRL_PERIOD					(32768)	// 1Hz
//#define CTRL_PERIOD					(3277)	// 10Hz
#define CTRL_PERIOD					(656)	// 50Hz

#define CuSP_ANTCHANNEL				(0)      // ANT channel to use
#define CuSP_DEVICENUM				0x0002     // Device number
#define CuSP_SHARED_NUM_LSB			0x01     // Device number Slave
#define CuSP_SHARED_NUM_MSB			0x00     // Device number Slave
#define CuSP_DEVICETYPE				0x01      // Device type
#define CuSP_TRANSTYPE				0x01      // Transmission type
#define CuSP_FREQ					(50)
#define CuSP_PERIOD					(656)		// 50Hz

#define USER_NETWORK_KEY         {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}
#define USER_NETWORK_NUM         (0)      // The network key is assigned to this network number


#define MAX_CHANNEL_EVENT_SIZE   (MESG_MAX_SIZE_VALUE)     // Channel event buffer size, assumes worst case extended message size
#define MAX_RESPONSE_SIZE        (MESG_MAX_SIZE_VALUE)     // Protocol response buffer size

#define  USB_IFDEV_FIRST			(0)
#define  USB_IFDEV_SECOND			(1)

	// Indexes into message recieved from ANT 
#define MESSAGE_BUFFER_DATA1_INDEX ((UCHAR) 0)
#define MESSAGE_BUFFER_DATA2_INDEX ((UCHAR) 1)
#define MESSAGE_BUFFER_DATA3_INDEX ((UCHAR) 2)
#define MESSAGE_BUFFER_DATA4_INDEX ((UCHAR) 3)
#define MESSAGE_BUFFER_DATA5_INDEX ((UCHAR) 4)
#define MESSAGE_BUFFER_DATA6_INDEX ((UCHAR) 5)
#define MESSAGE_BUFFER_DATA7_INDEX ((UCHAR) 6)
#define MESSAGE_BUFFER_DATA8_INDEX ((UCHAR) 7)
#define MESSAGE_BUFFER_DATA9_INDEX ((UCHAR) 8)
#define MESSAGE_BUFFER_DATA10_INDEX ((UCHAR) 9)
#define MESSAGE_BUFFER_DATA11_INDEX ((UCHAR) 10)
#define MESSAGE_BUFFER_DATA12_INDEX ((UCHAR) 11)
#define MESSAGE_BUFFER_DATA13_INDEX ((UCHAR) 12)
#define MESSAGE_BUFFER_DATA14_INDEX ((UCHAR) 13)

#define CuSP_MAX_DEVICES_SUPPORTED	7

class CNwIfANT
{
private:
	static CNwIfANT* ppSnsrs[CuSP_MAX_DEVICES_SUPPORTED];
	static int mCount;
	static char aucTmpBuffer[1024];
	static UCHAR aucChannel_0_Buffer[MAX_CHANNEL_EVENT_SIZE];
	static UCHAR aucTransmit_0_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
	static UCHAR aucChannel_Ctrl_Buffer[MAX_CHANNEL_EVENT_SIZE];
	static UCHAR aucTransmit_Ctrl_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
	static UCHAR aucTransmit_CtrlPrev_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
	static UCHAR aucResponseBuffer[MAX_RESPONSE_SIZE];

	static BOOL NwIf_Data_Channel_0_Callback(UCHAR, UCHAR);
	static BOOL NwIf_Ctrl_ChannelCallback(UCHAR, UCHAR);
	static BOOL NwIf_ResponseCallback(UCHAR, UCHAR);
	static void serviceCtrlMsg(UCHAR* pMsg);
	static void setCtrlPrevBuffer(UCHAR* cBuf);
	static bool isControlExecuted(UCHAR* cBuf);

	static bool openDataChannel(void);
	static bool closeDataChannel(void);

	static bool fOkForNewCtrl;

	static bool dataChannelOpening;

protected:
	CNwIfANT(void);
public:
	CTranslate* pN2CBuffer;
	CTranslate* pC2NBuffer;

	CNwIfANT(CTranslate* pClientBuffer);
	~CNwIfANT(void);
	static bool detectInterface(void);
	bool openControlChannel(void);
	bool connectSensor(void);
};

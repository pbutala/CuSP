#pragma once
#include <Windows.h>

#define TRANS_MAX_BUF_SZ		1024
#define TRANS_EOL_BUF_SZ		3
#define PR_MAX_BUF_SZ			1024

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

#define SENSOR_NONE				0x00
#define SENSOR_TCS3414			0x39
#define SENSOR_TCS3471			0x29
//#define SENSOR_ADJDS311			0x74
#define SENSOR_ADXL345			0x53
#define SENSOR_ITG3200			0x69

#define CTRL_PARAM_INVALID			0x00
#define CTRL_PARAM_ON				0x10
#define CTRL_PARAM_OFF				0x11

enum E_SOURCE{
	e_TCS3414 = 0,
	e_TCS3471 = 1,
	e_ADJDS311 = 2,
	e_ADXL345 = 3,
	e_ITG3200 = 4,
	e_NONE = 5
};

using namespace System::Threading;
class CTranslate
{
private:
	static const char* strSource;
	static const char* strTx;
	static const char* strRx;
	static const char* strDataCh;
	static const char* strADXL345;
	static const char* strITG3200;
	static const char* strTCS3414;
	static const char* strTCS3471;
	static const char* strADJDS311;
	static const char* strNone;
	static const char* strOn;
	static const char* strOff;

	char strDEVID[PR_MAX_BUF_SZ];
	char strCOMMAND[PR_MAX_BUF_SZ];
	char strSENSOR[PR_MAX_BUF_SZ];
	char strPARAM1[PR_MAX_BUF_SZ];
	char strPARAM2[PR_MAX_BUF_SZ];
	char strPARAM3[PR_MAX_BUF_SZ];
	char strPARAM4[PR_MAX_BUF_SZ];

	char aucBuffer[TRANS_MAX_BUF_SZ];
	//static char acEOL[TRANS_EOL_BUF_SZ];
	int mReadPtr;
	int mWritePtr;
	E_SOURCE* e_SRC;

	HANDLE ghMutex;
	int getBufferLength();
	static unsigned int getUINT(unsigned char msb, unsigned char lsb);
	void translateTCS3414Message(char* msgIn, char* bufOut);
	void translateTCS3471Message(char* msgIn, char* bufOut);
	void translateADJDS311Message(char* msgIn, char* bufOut);
	void translateADXL345Message(char* msgIn, char* bufOut);
	void translateITG3200Message(char* msgIn, char* bufOut);
	void extractClientMessage(char* bufIn);
	void getCommand(char* ch);
	void getSensor(char* ch);
	void getParam1(char* ch);
	void getParam2(char* ch);
	void getParam3(char* ch);
	void getParam4(char* ch);

public:
	int getBufferData(char* buffer, int MAXBUF);
	int setBufferData(char* buffer, int MAXBUF);
	int setBufferData(char* buffer, int START, int STOP);
	//int setBufferEOL();
	void translateDataMessage(char* msgIn, char* bufOut);
	void translateCtrlMessage(char* msgIn, char* bufOut);
	void translateClientMessage(char* msgIn, char* bufOut);
	void setDataSource(UCHAR srcAddress);
	CTranslate(void);
	~CTranslate(void);
};


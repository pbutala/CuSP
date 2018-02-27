#include "StdAfx.h"
#include "Translate.h"
#include <string.h>
#include <stdio.h>

//char CTranslate::acEOL[TRANS_EOL_BUF_SZ] = {'\r','\n','\0'};
const char* CTranslate::strSource = "source";
const char* CTranslate::strTx = "writereg";
const char* CTranslate::strRx = "readreg";
const char* CTranslate::strDataCh = "datach";
const char* CTranslate::strADXL345 = "adxl345";
const char* CTranslate::strITG3200 = "itg3200";
const char* CTranslate::strTCS3414 = "tcs3414";
const char* CTranslate::strTCS3471 = "tcs3471";
const char* CTranslate::strADJDS311 = "adjds311";
const char* CTranslate::strNone = "none";
const char* CTranslate::strOn = "on";
const char* CTranslate::strOff = "off";

CTranslate::CTranslate(void)
{
	ghMutex = CreateMutex(NULL, FALSE, NULL);
	mReadPtr = 0;
	mWritePtr = 0;
	e_SRC = new E_SOURCE();
	*e_SRC = E_SOURCE::e_NONE;
	strDEVID[0] = '\0';
	strCOMMAND[0] = '\0';
	strSENSOR[0] = '\0';
	strPARAM1[0] = '\0';
	strPARAM2[0] = '\0';
	strPARAM3[0] = '\0';
	strPARAM4[0] = '\0';
}

CTranslate::~CTranslate(void)
{
	CloseHandle(ghMutex);
}

int CTranslate::getBufferData(char* buffer, int MAXBUF)
{
	int i=0;

	DWORD dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		try
		{
			int MAXDATA = this->getBufferLength();
			for(i=0;(i<MAXDATA) && (i<MAXBUF);i++)
			{
				buffer[i] = aucBuffer[mReadPtr++];
				if(mReadPtr == TRANS_MAX_BUF_SZ)
				{
					mReadPtr = 0;
				}
			}
		}
		finally
		{
			while(!ReleaseMutex(ghMutex)){}
		}	
	}
	return i;
}

int CTranslate::setBufferData(char* buffer, int MAXBUF)
{
	/*int i=0;

	DWORD dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		try
		{
			for(i=0;(i<MAXBUF) && (i<TRANS_MAX_BUF_SZ);i++)
			{
				aucBuffer[mWritePtr++] = buffer[i];
				if(mWritePtr == TRANS_MAX_BUF_SZ)
				{
					mWritePtr = 0;
				}
			}
		}
		finally
		{
			while(!ReleaseMutex(ghMutex)){}
		}	
	}
	return i;*/
	return setBufferData(buffer, 0, MAXBUF-1);
}

int CTranslate::setBufferData(char* buffer, int START, int STOP)
{
	int i=0;
	int MAXBUF = STOP-START+1;

	DWORD dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		try
		{
			for(i=0;(i<MAXBUF) && (i<TRANS_MAX_BUF_SZ);i++)
			{
				aucBuffer[mWritePtr++] = buffer[START+i];
				if(mWritePtr == TRANS_MAX_BUF_SZ)
				{
					mWritePtr = 0;
				}
			}
		}
		finally
		{
			while(!ReleaseMutex(ghMutex)){}
		}	
	}
	return i;
}

/*int CTranslate::setBufferEOL()
{
	return this->setBufferData(acEOL,TRANS_EOL_BUF_SZ);
}*/

int CTranslate::getBufferLength()
{
	int len = 0;
	if(mWritePtr >= mReadPtr)
	{
		len = mWritePtr - mReadPtr;
	}
	else
	{
		len = TRANS_MAX_BUF_SZ - mReadPtr + mWritePtr;
	}
	return len;
}

void CTranslate::setDataSource(UCHAR srcAddress)
{
	switch(srcAddress)
		{
		case SENSOR_TCS3471:
			*e_SRC = E_SOURCE::e_TCS3471;
			break;
		case SENSOR_TCS3414:
			*e_SRC = E_SOURCE::e_TCS3414;
			break;
		case SENSOR_ADXL345:
			*e_SRC = E_SOURCE::e_ADXL345;
			break;
		case SENSOR_ITG3200:
			*e_SRC = E_SOURCE::e_ITG3200;
			break;
		default:
			*e_SRC = E_SOURCE::e_NONE;
			break;
		}
}

void CTranslate::translateCtrlMessage(char* msgIn, char* bufOut)
{
	unsigned int n;
	char strVAL[8];

	strcpy(bufOut, "CTRL;");
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[0]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[1]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[2]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[3]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[4]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[5]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[6]);
	strcat(bufOut, strVAL);
	n = sprintf(strVAL, "%X ", (UCHAR)msgIn[7]);
	strcat(bufOut, strVAL);
	
	/*switch((UCHAR)msgIn[3])
	{
	case 0x29:
		*e_SRC = E_SOURCE::e_TCS3471;
		break;
	case 0x53:
		*e_SRC = E_SOURCE::e_ADXL345;
		break;
	case 0x69:
		*e_SRC = E_SOURCE::e_ITG3200;
		break;
	default:
		*e_SRC = E_SOURCE::e_NONE;
		break;
	}*/
	//strcat(bufOut, "\r\n");
}

void CTranslate::translateDataMessage(char* msgIn, char* bufOut)
{
	char msgOut[1024];

	switch(*e_SRC)
	{
	case E_SOURCE::e_TCS3414:
		this->translateTCS3414Message(msgIn, msgOut);
		break;
	case E_SOURCE::e_TCS3471:
		this->translateTCS3471Message(msgIn, msgOut);
		break;
	case E_SOURCE::e_ADJDS311:
		this->translateADJDS311Message(msgIn, msgOut);
		break;
	case E_SOURCE::e_ADXL345:
		this->translateADXL345Message(msgIn, msgOut);
		break;
	case E_SOURCE::e_ITG3200:
		this->translateITG3200Message(msgIn, msgOut);
		break;
	default:
		strcpy(msgOut,"");
		break;
	}
	strcpy(bufOut,"DATA;");
	strcat(bufOut,msgOut);
}

void CTranslate::translateTCS3414Message(char* msgIn, char* bufOut)
{
	unsigned int VAL,n;
	char strVAL[8];

	strcpy(bufOut, "R:");
	VAL = getUINT(msgIn[3], msgIn[2]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " G:");
	VAL = getUINT(msgIn[1], msgIn[0]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " B:");
	VAL = getUINT(msgIn[5], msgIn[4]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " C:");
	VAL = getUINT(msgIn[7], msgIn[6]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	//strcat(bufOut, "\r\n");
}

void CTranslate::translateTCS3471Message(char* msgIn, char* bufOut)
{
	unsigned int VAL,n;
	char strVAL[8];

	strcpy(bufOut, "R:");
	VAL = getUINT(msgIn[3], msgIn[2]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " G:");
	VAL = getUINT(msgIn[5], msgIn[4]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " B:");
	VAL = getUINT(msgIn[7], msgIn[6]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " C:");
	VAL = getUINT(msgIn[1], msgIn[0]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	//strcat(bufOut, "\r\n");
}

void CTranslate::translateADJDS311Message(char* msgIn, char* bufOut)
{
	unsigned int VAL,n;
	char strVAL[8];

	strcpy(bufOut, "R:");
	VAL = getUINT(msgIn[1], msgIn[0]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " G:");
	VAL = getUINT(msgIn[3], msgIn[2]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " B:");
	VAL = getUINT(msgIn[5], msgIn[4]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " C:");
	VAL = getUINT(msgIn[7], msgIn[6]);
	n = sprintf(strVAL, "%u",VAL);
	strcat(bufOut, strVAL);

	//strcat(bufOut, "\r\n");
}

void CTranslate::translateADXL345Message(char* msgIn, char* bufOut)
{
	int VAL,n;
	char strVAL[8];

	strcpy(bufOut, "X:");
	VAL = getUINT(msgIn[1], msgIn[0]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " Y:");
	VAL = getUINT(msgIn[3], msgIn[2]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " Z:");
	VAL = getUINT(msgIn[5], msgIn[4]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	//strcat(bufOut, "\r\n");
}

void CTranslate::translateITG3200Message(char* msgIn, char* bufOut)
{
	int VAL,n;
	char strVAL[8];

	strcpy(bufOut, "X:");
	VAL = getUINT(msgIn[2], msgIn[3]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " Y:");
	VAL = getUINT(msgIn[4], msgIn[5]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " Z:");
	VAL = getUINT(msgIn[6], msgIn[7]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	strcat(bufOut, " T:");
	VAL = getUINT(msgIn[0], msgIn[1]);
	n = sprintf(strVAL, "%i",VAL);
	strcat(bufOut, strVAL);

	//strcat(bufOut, "\r\n");
}

void CTranslate::translateClientMessage(char* msgIn, char* bufOut)
{
	this->extractClientMessage(msgIn);
	this->getCommand(&bufOut[0]);
	this->getSensor(&bufOut[1]);
	this->getParam1(&bufOut[2]);
	this->getParam2(&bufOut[3]);
	this->getParam3(&bufOut[4]);
	this->getParam4(&bufOut[5]);
	bufOut[6] = '\0';
}

void CTranslate::extractClientMessage(char* bufIn)
{
	strDEVID[0] = '\0';
	strCOMMAND[0] = '\0';
	strSENSOR[0] = '\0';
	strPARAM1[0] = '\0';
	strPARAM2[0] = '\0';
	strPARAM3[0] = '\0';
	strPARAM4[0] = '\0';

	bool bStat = true;
	int i = 0,level = 0;

	char* curParam = strDEVID;
	int curIdx = 0;

	int len = strlen(bufIn)+1;
	while(i<len)
	{
		if(bufIn[i] == ';')
		{
			curParam[curIdx] = '\0';
			curIdx = 0;
			switch(level)
			{
			case 0:
				curParam = strCOMMAND;
				break;
			case 1:
				curParam = strSENSOR;
				break;
			case 2:
				curParam = strPARAM1;
				break;
			case 3:
				curParam = strPARAM2;
				break;
			case 4:
				curParam = strPARAM3;
				break;
			case 5:
				curParam = strPARAM4;
				break;
			case 6:
				break;
			default:
				bStat = false;
				break;
			}
			
			level++;
		}
		else
		{
			if((bufIn[i] != '\r') && (bufIn[i] != '\n')){
				curParam[curIdx++] = bufIn[i];
			}
		}
		i++;
		if(bStat == false)
			break;
	}

}

void CTranslate::getCommand(char* ch)
{
	if(_stricmp(strCOMMAND,CTranslate::strSource) == 0)
	{
		*ch = CTRL_CMD_SOURCE;
	}
	else if(_stricmp(strCOMMAND,CTranslate::strDataCh) == 0)
	{
		*ch = CTRL_CMD_DATACHANNEL;
	}
	else if(_stricmp(strCOMMAND,CTranslate::strTx) == 0)
	{
		*ch = CTRL_CMD_TXI2C;
	}
	else if(_stricmp(strCOMMAND,CTranslate::strRx) == 0)
	{
		*ch = CTRL_CMD_RXI2C;
	}
	else
	{
		*ch = 0x00;
	}
}

void CTranslate::getSensor(char* ch)
{
	if(_stricmp(strSENSOR,CTranslate::strTCS3471) == 0)
	{
		*ch = SENSOR_TCS3471;
	}
	else if(_stricmp(strSENSOR,CTranslate::strTCS3414) == 0)
	{
		*ch = SENSOR_TCS3414;
	}
	else if(_stricmp(strSENSOR,CTranslate::strADXL345) == 0)
	{
		*ch = SENSOR_ADXL345;
	}
	else if(_stricmp(strSENSOR,CTranslate::strITG3200) == 0)
	{
		*ch = SENSOR_ITG3200;
	}
	else
	{
		*ch = SENSOR_NONE;
	}
}

void CTranslate::getParam1(char* ch)
{
	if(_stricmp(strPARAM1,CTranslate::strOn) == 0)
	{
		*ch = CTRL_PARAM_ON;
	}
	else if(_stricmp(strPARAM1,CTranslate::strOff) == 0)
	{
		*ch = CTRL_PARAM_OFF;
	}
	else
	{
		*ch = strPARAM1[0];
	}
}

void CTranslate::getParam2(char* ch)
{
	*ch = strPARAM2[0];
}

void CTranslate::getParam3(char* ch)
{
	*ch = strPARAM3[0];
}

void CTranslate::getParam4(char* ch)
{
	*ch = strPARAM4[0];
}

unsigned int CTranslate::getUINT(unsigned char msb, unsigned char lsb)
{
	unsigned int VAL = (unsigned int)lsb;
	VAL = VAL + (msb << 8);
	return VAL;
}

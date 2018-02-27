#include "StdAfx.h"
#include <stdio.h>
#include <assert.h>
#include "NwIfANT.h"

CNwIfANT* CNwIfANT::ppSnsrs[CuSP_MAX_DEVICES_SUPPORTED];
int CNwIfANT::mCount = 0;
char CNwIfANT::aucTmpBuffer[1024];
bool CNwIfANT::fOkForNewCtrl = true;
bool CNwIfANT::dataChannelOpening = false;
UCHAR CNwIfANT::aucChannel_0_Buffer[MAX_CHANNEL_EVENT_SIZE];
UCHAR CNwIfANT::aucTransmit_0_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
UCHAR CNwIfANT::aucChannel_Ctrl_Buffer[MAX_CHANNEL_EVENT_SIZE];
UCHAR CNwIfANT::aucTransmit_Ctrl_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
UCHAR CNwIfANT::aucTransmit_CtrlPrev_Buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
UCHAR CNwIfANT::aucResponseBuffer[MAX_RESPONSE_SIZE];

CNwIfANT::CNwIfANT(CTranslate* pClientBuffer)
{
	pN2CBuffer = new CTranslate();
	if(CNwIfANT::mCount < CuSP_MAX_DEVICES_SUPPORTED)
		ppSnsrs[CNwIfANT::mCount++] = this;
	pC2NBuffer = pClientBuffer;
	dataChannelOpening = false;
}

CNwIfANT::CNwIfANT(void)
{
	pN2CBuffer = new CTranslate();
	if(CNwIfANT::mCount < CuSP_MAX_DEVICES_SUPPORTED)
		ppSnsrs[CNwIfANT::mCount++] = this;
	dataChannelOpening = false;
}

CNwIfANT::~CNwIfANT(void)
{
	delete pN2CBuffer;
	if(CNwIfANT::mCount > 0)
		CNwIfANT::mCount--;
}

bool CNwIfANT::detectInterface(void)
{	
	bool bStatus;
	// Load the ANT DLL functions. 
	if(!ANT_Load())
	{
		return false;
	}

	// The device number depends on how many USB sticks have been
	// plugged into the PC. The first USB stick plugged will be 0
	// the next 1 and so on.
	// 
	// The Baud Rate depends on the ANT solution being used. AP1
	// is 50000, all others are 57600   

	bStatus = (bool)ANT_Init(USB_IFDEV_FIRST, USER_BAUDRATE);
	//bStatus = (bool)ANT_Init(USB_IFDEV_SECOND, USER_BAUDRATE);
	//assert(bStatus);

	if(bStatus)
	{
		// Assign callback functions. One for serial message responses 
		// and the other for channel events. Each channel event can have 
		// its own callback function defined. Since we are only 
		// going to open one channel, setup one callback function
		// for the channel callback

		ANT_AssignResponseFunction(&CNwIfANT::NwIf_ResponseCallback, CNwIfANT::aucResponseBuffer); 
		ANT_AssignChannelEventFunction(CTRL_ANTCHANNEL, &CNwIfANT::NwIf_Ctrl_ChannelCallback, CNwIfANT::aucChannel_Ctrl_Buffer); 
	}

	return bStatus;
}

bool CNwIfANT::openControlChannel(void)
{
	bool resp = true;
	BOOL bResp = FALSE;
	bResp = ANT_UnAssignChannel(CTRL_ANTCHANNEL);
	bResp = ANT_AssignChannel(CTRL_ANTCHANNEL, PARAMETER_TX_NOT_RX, USER_NETWORK_NUM);
	bResp = ANT_SetChannelId(CTRL_ANTCHANNEL, CTRL_DEVICENUM, CTRL_DEVICETYPE, CTRL_TRANSTYPE);
	bResp = ANT_SetChannelRFFreq(CTRL_ANTCHANNEL, CTRL_FREQ);
	bResp = ANT_SetChannelPeriod(CTRL_ANTCHANNEL, CTRL_PERIOD);
	bResp = ANT_OpenChannel(CTRL_ANTCHANNEL);
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA1_INDEX] = 0x01;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA2_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA3_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA4_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA5_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA6_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA7_INDEX] = 0x00;
	aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA8_INDEX] = 0x00;
	ANT_SendBroadcastData(CTRL_ANTCHANNEL, aucTransmit_Ctrl_Buffer);
	return resp;
}

bool CNwIfANT::connectSensor(void)
{
	bool bStatus = true;
	bStatus = this->openDataChannel();
	return bStatus;
}

bool CNwIfANT::openDataChannel(void)
{
	bool bStatus = true;
	if(ppSnsrs[0]->dataChannelOpening == false)
	{
		ppSnsrs[0]->dataChannelOpening = true;
		BOOL bResp = FALSE;
		bResp = ANT_UnAssignChannel(CuSP_ANTCHANNEL);
		bResp = ANT_AssignChannel(CuSP_ANTCHANNEL, PARAMETER_RX_NOT_TX, USER_NETWORK_NUM);
		bResp = ANT_SetChannelId(CuSP_ANTCHANNEL, CuSP_DEVICENUM, CuSP_DEVICETYPE, CuSP_TRANSTYPE);
		bResp = ANT_SetChannelRFFreq(CuSP_ANTCHANNEL, CuSP_FREQ);
		bResp = ANT_SetChannelPeriod(CuSP_ANTCHANNEL, CuSP_PERIOD);
		ANT_AssignChannelEventFunction(CuSP_ANTCHANNEL, &CNwIfANT::NwIf_Data_Channel_0_Callback, CNwIfANT::aucChannel_0_Buffer);
		bResp = ANT_OpenChannel(CuSP_ANTCHANNEL);
	}
	return bStatus;
}

bool CNwIfANT::closeDataChannel(void)
{
	bool bStatus = true;
	BOOL bResp = FALSE;
	bResp = ANT_CloseChannel(CuSP_ANTCHANNEL);
	return bStatus;
}

void CNwIfANT::serviceCtrlMsg(UCHAR* pMsg)
{
	if(pMsg[CTRL_CMD_OFFSET] == CTRL_CMD_DATACHANNEL)
	{
		if(pMsg[CTRL_PARAM_1_OFFSET] == CTRL_PARAM_ON)
		{
			openDataChannel();
		}
		else if(pMsg[CTRL_PARAM_1_OFFSET] == CTRL_PARAM_OFF)
		{
			closeDataChannel();
		}
	}
	if((pMsg[CTRL_CMD_OFFSET] == CTRL_CMD_SOURCE) || (pMsg[CTRL_CMD_OFFSET] == CTRL_CMD_DATACHANNEL))
	{
		ppSnsrs[0]->pN2CBuffer->setDataSource(pMsg[CTRL_SENSOR_OFFSET]);
	}
}

void CNwIfANT::setCtrlPrevBuffer(UCHAR* cBuf)
{
	for(int i=0; i<ANT_DATA_SIZE; i++)
	{
		aucTransmit_CtrlPrev_Buffer[i] = cBuf[i];
	}
}

bool CNwIfANT::isControlExecuted(UCHAR* cBuf)
{
	bool bStat = false;

	if(cBuf[CTRL_CMD_OFFSET] == aucTransmit_CtrlPrev_Buffer[CTRL_CMD_OFFSET])
	{
		bStat = true;
	}

	return bStat;
}

BOOL CNwIfANT::NwIf_Data_Channel_0_Callback(UCHAR ucChannel_, UCHAR ucEvent_)
{
	UCHAR ucDataOffset = MESSAGE_BUFFER_DATA2_INDEX;   // For most data messages

	switch(ucEvent_)
	{   
	case EVENT_TX:

		break;

	case EVENT_RX_FLAG_ACKNOWLEDGED:
	case EVENT_RX_FLAG_BURST_PACKET:  
	case EVENT_RX_FLAG_BROADCAST:

		// INTENTIONAL FALLTHROUGH

	case EVENT_RX_ACKNOWLEDGED:
	case EVENT_RX_BURST_PACKET:  
	case EVENT_RX_BROADCAST:

		// This is an event generated by the DLL. It is not strictly
		// returned by the ANT part.

		// Display recieved message
		if(CNwIfANT::mCount > 0)
		{
			//ppSnsrs[0]->pN2CBuffer->setBufferData((char*)aucChannel_0_Buffer, ucDataOffset, ucDataOffset+7);
			ppSnsrs[0]->pN2CBuffer->translateDataMessage((char*)&aucChannel_0_Buffer[ucDataOffset],aucTmpBuffer);
			ppSnsrs[0]->pN2CBuffer->setBufferData(aucTmpBuffer, strlen(aucTmpBuffer) + 1);
			ppSnsrs[0]->dataChannelOpening = false;
		}
		break;

	case EVENT_RX_EXT_ACKNOWLEDGED:
	case EVENT_RX_EXT_BURST_PACKET:
	case EVENT_RX_EXT_BROADCAST:
		break;

	case EVENT_RX_SEARCH_TIMEOUT:
		{
			//printf("Search Timeout on channel %d\n",ucChannel_); 
			break;
		}
	case EVENT_RX_FAIL:
		{
			//printf("Rx Fail on channel %d\n", ucChannel_);
			break;
		}
	case EVENT_TRANSFER_RX_FAILED:
		{
			//printf("Burst recieve has failed\n", ucChannel_);
			break;
		}
	case EVENT_TRANSFER_TX_COMPLETED:     
		{
			//printf("Tranfer Completed.\n");
			break;
		}
	case EVENT_TRANSFER_TX_FAILED:        
		{
			//printf("Tranfer Failed.\n");      
			break;
		}
	case EVENT_CHANNEL_CLOSED:            
		{
			// This event should be used to determine that the channel is closed.
			//printf("Channel Closed\n");
			//printf("Unassign Channel\n");
			//ANT_UnAssignChannel(USER_ANTCHANNEL);
			break;
		}
	case EVENT_RX_FAIL_GO_TO_SEARCH:      
		{
			//printf("Goto Search.\n");
			break;
		}
	case EVENT_CHANNEL_COLLISION:         
		{
			//printf("Channel (%d) Collision\n");
			break;
		}
	case EVENT_TRANSFER_TX_START:        
		{
			//printf("Burst Started\n");      
			break;
		}
	default:
		{
			//printf("Unknown Channel(%d) Event %d\n",ucChannel_,ucEvent_); 
			break;
		}

	}
	return(TRUE);
}

BOOL CNwIfANT::NwIf_Ctrl_ChannelCallback(UCHAR ucChannel_, UCHAR ucEvent_)
{
	UCHAR ucDataOffset = MESSAGE_BUFFER_DATA2_INDEX;   // For most data messages
	int outTxLen;
	switch(ucEvent_)
	{   
	case EVENT_TX:
		if(fOkForNewCtrl)
		{
			outTxLen = ppSnsrs[0]->pC2NBuffer->getBufferData(aucTmpBuffer, 1024);
			if(outTxLen > 0)
			{
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA1_INDEX] = 0x01;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA2_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA3_INDEX] = aucTmpBuffer[0];
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA4_INDEX] = aucTmpBuffer[1];
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA5_INDEX] = aucTmpBuffer[2];
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA6_INDEX] = aucTmpBuffer[3];
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA7_INDEX] = aucTmpBuffer[4];
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA8_INDEX] = aucTmpBuffer[5];
				serviceCtrlMsg(aucTransmit_Ctrl_Buffer);
			}
			else
			{
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA1_INDEX] = 0x01;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA2_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA3_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA4_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA5_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA6_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA7_INDEX] = 0x00;
				aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA8_INDEX] = 0x00;
			}
			fOkForNewCtrl = false;
			setCtrlPrevBuffer(&aucTransmit_Ctrl_Buffer[MESSAGE_BUFFER_DATA1_INDEX]);
		}
		ANT_SendBroadcastData(CTRL_ANTCHANNEL, aucTransmit_Ctrl_Buffer);
		break;

	case EVENT_RX_FLAG_ACKNOWLEDGED:
	case EVENT_RX_FLAG_BURST_PACKET:  
	case EVENT_RX_FLAG_BROADCAST:

		// INTENTIONAL FALLTHROUGH

	case EVENT_RX_ACKNOWLEDGED:
	case EVENT_RX_BURST_PACKET:  
	case EVENT_RX_BROADCAST:

		ppSnsrs[0]->pN2CBuffer->translateCtrlMessage((char*)&aucChannel_Ctrl_Buffer[ucDataOffset],aucTmpBuffer);
		ppSnsrs[0]->pN2CBuffer->setBufferData(aucTmpBuffer, strlen(aucTmpBuffer) + 1);
		//serviceRcvdCtrlMsg();
		fOkForNewCtrl = isControlExecuted(&aucChannel_Ctrl_Buffer[ucDataOffset]);
		break;

	case EVENT_RX_EXT_ACKNOWLEDGED:
	case EVENT_RX_EXT_BURST_PACKET:
	case EVENT_RX_EXT_BROADCAST:

		break;

	case EVENT_RX_SEARCH_TIMEOUT:
		{
			//printf("Search Timeout on channel %d\n",ucChannel_); 
			break;
		}
	case EVENT_RX_FAIL:
		{
			//printf("Rx Fail on channel %d\n", ucChannel_);
			break;
		}
	case EVENT_TRANSFER_RX_FAILED:
		{
			//printf("Burst recieve has failed\n", ucChannel_);
			break;
		}
	case EVENT_TRANSFER_TX_COMPLETED:     
		{
			//printf("Tranfer Completed.\n");
			break;
		}
	case EVENT_TRANSFER_TX_FAILED:        
		{
			//printf("Tranfer Failed.\n");      
			break;
		}
	case EVENT_CHANNEL_CLOSED:            
		{
			//this->openControlChannel();
			break;
		}
	case EVENT_RX_FAIL_GO_TO_SEARCH:      
		{
			//printf("Goto Search.\n");
			break;
		}
	case EVENT_CHANNEL_COLLISION:         
		{
			//printf("Channel (%d) Collision\n");
			break;
		}
	case EVENT_TRANSFER_TX_START:        
		{
			//printf("Burst Started\n");      
			break;
		}
	default:
		{
			//printf("Unknown Channel(%d) Event %d\n",ucChannel_,ucEvent_); 
			break;
		}

	}
	return(TRUE);
}

BOOL CNwIfANT::NwIf_ResponseCallback(UCHAR ucChannel_, UCHAR ucMessageId_)
{
	return(TRUE);
}


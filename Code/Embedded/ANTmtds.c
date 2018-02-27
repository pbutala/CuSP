/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include <msp430f2619.h>
#include "Defines.h"
#include "ANTmsgs.h"
#include "ANTmtds.h"
#include "Utilities.h"

void ServiceDataChannelRespEvent(void);
void ServiceControlChannelRespEvent(void);

/* ANT->MCU data processing */
// Services the received message that is in serRxArr
void ServiceRcvdMsgBuf()
{
	UCHAR msgLen, CHNL;		// variable to store the received msg lenth and CMD
	UCHAR csCalc, csRcvd;			// checksums calculated and received from ANT
	//UCHAR* pDATA;
	msgLen = serRxArr[0] + 2;		// serRxArr[0] has data length + byte to store data length + CMD byte 
	CHNL = serRxArr[2];
	//pDATA = &serRxArr[3];
	csRcvd = serRxArr[msgLen];		// eg: serRxArr[0] = 1 => msgLen = 3, next byte (serRxArr[msgLen]) has cs
	csCalc = CalcChecksum(serRxArr, msgLen, RxSYNC);	// Calc Checksum to confirm message is received without errors
	
	if(csCalc != csRcvd){			// if Checksums do not match,
		fSTPEND |= fRxErrAnt;		// Flag Receive error
	}
	else{							// if Checksum OK
		switch(CHNL){
			case CuSP_ANTCHANNEL:
				ServiceDataChannelRespEvent();
				break;
			case CTRL_ANTCHANNEL:
				ServiceControlChannelRespEvent();
				break;
			default:
				break;
		}
	}
}

// Local function to service channel response event message received by MCU from ANT
void ServiceDataChannelRespEvent()
{
	UCHAR CMD, msgCode;		// variable to store the received msg lenth and CMD
	//UCHAR* pDATA;
	CMD = serRxArr[1];				// CMD sent by ANT to MCU
	//pDATA = &serRxArr[3];
	msgCode = serRxArr[4];
	
	switch(CMD)
	{
		case MESG_RESPONSE_EVENT_ID:
			switch(msgCode)
			{
				case EVENT_TX: 
					/*while(fSTPEND & fTxIniAnt){}
					BufSendBroadcastDataMsg2(CuSP_ANTCHANNEL, TxDataBuffer, 8);	// Set up buffer to broadcast
					fSTPEND |= fTxIniAnt;*/					// Flag tx initiate
					fCOMFLAG |= fOkToBcstData;// ok to start next transmit
					fCOMFLAG |= fDataChannelOpen;
					fCOMFLAG &= ~fDataChannelOpening;
					fSTPEND |= fTxDataAnt;
					//P4OUT ^= LED_RF_DATA;
					break;
				case EVENT_QUE_OVERFLOW: // some events missed due to latency in SPI
					break;
				case EVENT_CHANNEL_CLOSED:
					fCOMFLAG &= ~fDataChannelOpen;
					break;
				default:
					break;
			}
			break;
	}
}

void ServiceControlChannelRespEvent()
{
	UCHAR CMD, msgCode;		// variable to store the received msg lenth and CMD
	UCHAR* pDATA;
	CMD = serRxArr[1];				// CMD sent by ANT to MCU
	pDATA = &serRxArr[3];
	msgCode = serRxArr[4];
	
	switch(CMD)
	{
		case MESG_RESPONSE_EVENT_ID:
			switch(msgCode){
				case EVENT_TX: 
					//BufSendBroadcastDataMsg2(CTRL_ANTCHANNEL, TxControlBuffer, 8);	// Set up buffer to broadcast
					//fSTPEND |= fTxIniAnt;
					fCOMFLAG |= fCtrlChannelOpen;
					fCOMFLAG &= ~fCtrlChannelOpening;
					fSTPEND |= fTxCtrlAnt;
					fCOMFLAG |= fNewCtrlCmd;
					break;
				case EVENT_QUE_OVERFLOW: // some events missed due to latency in SPI
					break;
				case EVENT_RX_SEARCH_TIMEOUT:
				//intentional fall through
				case EVENT_CHANNEL_CLOSED:
					fCOMFLAG |= fCtrlChannelOpening;
					fCOMFLAG &= ~fCtrlChannelOpen;
					ANT_CHANNEL = CTRL_ANTCHANNEL;
					ANT_CHANNELTYPE = CTRL_CHANNELTYPE;
					ANT_DEVICENUM = CTRL_DEVICENUM;
					ANT_DEVICETYPE = CTRL_DEVICETYPE;
					ANT_TRANSTYPE = CTRL_TRANSTYPE;
					ANT_FREQ = CTRL_FREQ;
					ANT_PERIOD = CTRL_PERIOD;
					nxtCnfgMsgID = MESG_UNASSIGN_CHANNEL_ID;
					fSTPEND |= fConfigAnt;
					P4OUT &= ~LED_PWR_CTRL;
					break;
				default:
					break;
			}
			break;
		case MESG_BROADCAST_DATA_ID:
		case MESG_ACKNOWLEDGED_DATA_ID:
			// make sense of server commands
			if(pDATA[CTRL_DEVICE_LSB_OFFSET] == CuSP_SHARED_CHANNELNUM_LSB){
				if(pDATA[CTRL_DEVICE_MSB_OFFSET] == CuSP_SHARED_CHANNELNUM_MSB){
					CTRL_COMMAND = pDATA[CTRL_CMD_OFFSET];
					CTRL_SENSOR = pDATA[CTRL_SENSOR_OFFSET];
					CTRL_PARAM_1 = pDATA[CTRL_PARAM_1_OFFSET];
					CTRL_PARAM_2 = pDATA[CTRL_PARAM_2_OFFSET];
					CTRL_PARAM_3 = pDATA[CTRL_PARAM_3_OFFSET];
					CTRL_PARAM_4 = pDATA[CTRL_PARAM_4_OFFSET];
				}
			}
			//P4OUT ^= LED3;
			/*BufSendBroadcastDataMsg2(CTRL_ANTCHANNEL, TxControlBuffer, 8);	// Set up buffer to broadcast
			fSTPEND |= fTxIniAnt;					// Flag tx initiate
			fCOMFLAG |= fNewCtrlCmd;// ok to start next transmit
			fCOMFLAG |= fCtrlChannelOpen;
			fCOMFLAG &= ~fCtrlChannelOpening;*/
			break;
	}
}

/* CONFIGURATION MESSAGES */
// Buffers System Reset Msg in serTxArr. No reply expected
void BufSetSysResetMsg()
{
	serTxArr[0] = MESG_SYSTEM_RESET_SIZE;
	serTxArr[1] = MESG_SYSTEM_RESET_ID;
	serTxArr[2] = 0;
}

// Buffers NwKeyMessage in serTxArr
//NwKey[] must be 8 bytes long
void BufSetNwKeyMsg(UCHAR NwNum, UCHAR* NwKey)
{
	int i=0;	
	serTxArr[0] = MESG_NETWORK_KEY_SIZE;
	serTxArr[1] = MESG_NETWORK_KEY_ID;
	serTxArr[2] = NwNum;
	for(; i<MESG_NETWORK_KEY_SIZE; i++){
		serTxArr[i+3] = NwKey[i];
	}
}

//Buffers AssignChannel message in serTxArr
void BufAssignChannelMsg(UCHAR ChNum, UCHAR ChTyp, UCHAR NwNum)
{
	serTxArr[0] = MESG_ASSIGN_CHANNEL_SIZE;
	serTxArr[1] = MESG_ASSIGN_CHANNEL_ID;
	serTxArr[2] = ChNum;
	serTxArr[3] = ChTyp;
	serTxArr[4] = NwNum;
}

//Buffers UnAssignChannel message in serTxArr
void BufUnAssignChannelMsg(UCHAR ChNum)
{
	serTxArr[0] = MESG_UNASSIGN_CHANNEL_SIZE;
	serTxArr[1] = MESG_UNASSIGN_CHANNEL_ID;
	serTxArr[2] = ChNum;
}

// Buffers Set Channel ID message in serTxArr
void BufSetChannelIDMsg(UCHAR ChNum, UINT DevNum, UCHAR DevTyp, UCHAR TrTyp)
{
	serTxArr[0] = MESG_CHANNEL_ID_SIZE;
	serTxArr[1] = MESG_CHANNEL_ID_ID;
	serTxArr[2] = ChNum;
	serTxArr[3] = DevNum & 0x00FF;
	serTxArr[4] = ((DevNum & 0xFF00)>>8);
	serTxArr[5] = DevTyp;
	serTxArr[6] = TrTyp;
}

// Buffers Set Radio Frequency message in serTxArr
void BufSetRadioFreqMsg(UCHAR ChNum, UCHAR RFreq)
{
	serTxArr[0] = MESG_CHANNEL_RADIO_FREQ_SIZE;
	serTxArr[1] = MESG_CHANNEL_RADIO_FREQ_ID;
	serTxArr[2] = ChNum;
	serTxArr[3] = RFreq;
}

// Buffers SetChannelMsgPeriod message in serTxArr
void BufSetChannelMsgPeriodMsg(UCHAR ChNum, UINT Prd)
{
	serTxArr[0] = MESG_CHANNEL_MESG_PERIOD_SIZE;
	serTxArr[1] = MESG_CHANNEL_MESG_PERIOD_ID;
	serTxArr[2] = ChNum;
	serTxArr[3] = Prd & 0x00FF;
	serTxArr[4] = (Prd & 0xFF00)>>8;
}

// Buffers OpenChannel message in serTxArr
void BufOpenChannelMsg(UCHAR ChNum)
{
	serTxArr[0] = MESG_OPEN_CHANNEL_SIZE;
	serTxArr[1] = MESG_OPEN_CHANNEL_ID;
	serTxArr[2] = ChNum;
}

// Buffers CloseChannel message in serTxArr
void BufCloseChannelMsg(UCHAR ChNum)
{
	serTxArr[0] = MESG_CLOSE_CHANNEL_SIZE;
	serTxArr[1] = MESG_CLOSE_CHANNEL_ID;
	serTxArr[2] = ChNum;
}

/* DATA MESSAGES */
// Buffers Broadcast Data Messages
void BufSendBroadcastDataMsg(UCHAR ChNum, UCHAR* Data, int length, UCHAR DataSource)
{
	int i=0;	
	serTxArr[0] = 0x09;
	serTxArr[1] = MESG_BROADCAST_DATA_ID;
	serTxArr[2] = ChNum;
	
	serTxArr[3] = DataSource;	//indicates source of data: ADXL/ITG/Other...
	
	if(length > 0x07){
		length = 0x07;
	}
	
	for(; i<length; i++){
		serTxArr[i+4] = Data[i];
	}
	
	for(; i<0x08; i++){
		serTxArr[i+4] = 0x00;
	}
}

// Buffers Broadcast Data Messages
void BufSendBroadcastDataMsg2(UCHAR ChNum, UCHAR* Data, int length)
{
	int i=0;	
	serTxArr[0] = 0x09;
	serTxArr[1] = MESG_BROADCAST_DATA_ID;
	serTxArr[2] = ChNum;
	
	if(length > 0x08){
		length = 0x08;
	}
	
	for(; i<length; i++){
		serTxArr[i+3] = Data[i];
	}
	
	for(; i<0x08; i++){
		serTxArr[i+3] = 0x00;
	}
}

// Buffers Acknowledged Data Messages
void BufSendAcknowledgedDataMsg2(UCHAR ChNum, UCHAR* Data, int length)
{
	int i=0;	
	serTxArr[0] = 0x09;
	serTxArr[1] = MESG_ACKNOWLEDGED_DATA_ID;
	serTxArr[2] = ChNum;
	
	if(length > 0x08){
		length = 0x08;
	}
	
	for(; i<length; i++){
		serTxArr[i+3] = Data[i];
	}
	
	for(; i<0x08; i++){
		serTxArr[i+3] = 0x00;
	}
}


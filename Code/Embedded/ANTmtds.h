/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef ANTMTDS_H_
#define ANTMTDS_H_

// MCU ANT data processing
void ServiceRcvdMsgBuf(void);

//Configuration Messages
void BufSetSysResetMsg();
void BufSetNwKeyMsg(UCHAR NwNum, UCHAR* NwKey);
void BufAssignChannelMsg(UCHAR ChNum, UCHAR ChTyp, UCHAR NwNum);
void BufUnAssignChannelMsg(UCHAR ChNum);
void BufSetChannelIDMsg(UCHAR ChNum, UINT DevNum, UCHAR DevTyp, UCHAR TrTyp);
void BufSetRadioFreqMsg(UCHAR ChNum, UCHAR RFreq);
void BufSetChannelMsgPeriodMsg(UCHAR ChNum, UINT Prd);
void BufOpenChannelMsg(UCHAR ChNum);
void BufCloseChannelMsg(UCHAR ChNum);
void BufSetNwKeyMsg(UCHAR NwNum, UCHAR* NwKey);

// Data Messages
void BufSendBroadcastDataMsg(UCHAR ChNum, UCHAR* Data, int length, UCHAR DataSource);
void BufSendBroadcastDataMsg2(UCHAR ChNum, UCHAR* Data, int length);
void BufSendAcknowledgedDataMsg2(UCHAR ChNum, UCHAR* Data, int length);

#endif /*ANTMTDS_H_*/

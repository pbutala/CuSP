/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#include "Defines.h"
#include "ANTmsgs.h"

unsigned int fSTPEND;
unsigned int fCOMFLAG;
unsigned char FREQ;

unsigned char serTxArr[SERMAX];
unsigned char serRxArr[SERMAX];

unsigned char nxtCnfgMsgID = MESG_INVALID_ID;
bool ADXLconfigured = false;
bool ITGconfigured = false;

unsigned char SYSTEM_NW_KEY[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // NW key
unsigned char ANT_CHANNEL = CTRL_ANTCHANNEL;
unsigned char ANT_CHANNELTYPE = CTRL_CHANNELTYPE;
unsigned int ANT_DEVICENUM = CTRL_DEVICENUM;
unsigned char ANT_DEVICETYPE = CTRL_DEVICETYPE;
unsigned char ANT_TRANSTYPE = CTRL_TRANSTYPE;
unsigned char ANT_FREQ = CTRL_FREQ;
unsigned int ANT_PERIOD = CTRL_PERIOD;
/*unsigned char ANT_CHANNEL = CuSP_ANTCHANNEL;
unsigned char ANT_CHANNELTYPE = CuSP_CHANNELTYPE;
unsigned int ANT_DEVICENUM = CuSP_DEVICENUM;
unsigned char ANT_DEVICETYPE = CuSP_DEVICETYPE;
unsigned char ANT_TRANSTYPE = CuSP_TRANSTYPE;
unsigned char ANT_FREQ = CuSP_FREQ;
unsigned int ANT_PERIOD = CuSP_PERIOD;*/

unsigned char CTRL_COMMAND = CTRL_CMD_SOURCE;
unsigned char CTRL_SENSOR = SENSOR_NONE;
unsigned char CTRL_PARAM_1 = CTRL_PARAM_OFF;
unsigned char CTRL_PARAM_2 = CTRL_PARAM_INVALID;
unsigned char CTRL_PARAM_3 = CTRL_PARAM_INVALID;
unsigned char CTRL_PARAM_4 = CTRL_PARAM_INVALID;

unsigned char DATA_SENSOR = SENSOR_NONE;

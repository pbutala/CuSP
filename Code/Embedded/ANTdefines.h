/***********************************************************************************
 * Author: Pankil M. Butala
 * 		Multimedia Communications Lab,
 *      Boston University.
 * Date: 05/08/2012
 ***********************************************************************************/ 
#ifndef ANTDEFINES_H_
#define ANTDEFINES_H_

#include "Defines.h"

#define ANT_DATA_SIZE               8  // ANT message payload size.

//////////////////////////////////////////////
// ANT Clock Frequency
//////////////////////////////////////////////
#define ANT_CLOCK_FREQUENCY                        ((ULONG)32768)                // ANT system clock frequency

//////////////////////////////////////////////
// ANT Message Payload Size
//////////////////////////////////////////////
#define ANT_STANDARD_DATA_PAYLOAD_SIZE             ((UCHAR)8)

//////////////////////////////////////////////
// ANT LIBRARY Extended Data Message Fields
// NOTE: You must check the extended message
// bitfield first to find out which fields
// are present before accessing them!
//////////////////////////////////////////////
#define ANT_EXT_MESG_DEVICE_ID_FIELD_SIZE          ((UCHAR)4)

//////////////////////////////////////////////
// ANT Extended Data Message Bifield Definitions
//////////////////////////////////////////////
#define ANT_EXT_MESG_BITFIELD_DEVICE_ID            ((UCHAR)0x80)           // first field after bitfield

// 4 bits free reserved set to 0
#define ANT_EXT_MESG_BIFIELD_EXTENSION             ((UCHAR)0x01)

#define ANT_EXT_MESG_BITFIELD_OVERWRITE_SHARED_ADR ((UCHAR)0x10)  //!! need to not be defined for outgoing messages? move to top for incoming messages?
#define ANT_EXT_MESG_BITFIELD_TRANSMISSION_TYPE    ((UCHAR)0x08)  //!! same as comment above, maybe not useful at all for incoming



//////////////////////////////////////////////
// ID Definitions
//////////////////////////////////////////////
#define ANT_ID_SIZE                                ((UCHAR)4)
#define ANT_ID_TRANS_TYPE_OFFSET                   ((UCHAR)3)
#define ANT_ID_DEVICE_TYPE_OFFSET                  ((UCHAR)2)
#define ANT_ID_DEVICE_NUMBER_HIGH_OFFSET           ((UCHAR)1)
#define ANT_ID_DEVICE_NUMBER_LOW_OFFSET            ((UCHAR)0)
#define ANT_ID_DEVICE_TYPE_PAIRING_FLAG            ((UCHAR)0x80)

#define ANT_TRANS_TYPE_SHARED_ADDR_MASK            ((UCHAR)0x03)
#define ANT_TRANS_TYPE_1_BYTE_SHARED_ADDRESS       ((UCHAR)0x02)
#define ANT_TRANS_TYPE_2_BYTE_SHARED_ADDRESS       ((UCHAR)0x03)


//////////////////////////////////////////////
// Assign Channel Parameters
//////////////////////////////////////////////
#define PARAMETER_RX_NOT_TX                        ((UCHAR)0x00)
#define PARAMETER_TX_NOT_RX                        ((UCHAR)0x10)
#define PARAMETER_SHARED_CHANNEL                   ((UCHAR)0x20)
#define PARAMETER_NO_TX_GUARD_BAND                 ((UCHAR)0x40)
#define PARAMETER_ALWAYS_RX_WILD_CARD_SEARCH_ID    ((UCHAR)0x40)                 //Pre-AP2
#define PARAMETER_RX_ONLY                          ((UCHAR)0x40)

//////////////////////////////////////////////
// Ext. Assign Channel Parameters
//////////////////////////////////////////////
#define EXT_PARAM_ALWAYS_SEARCH                    ((UCHAR)0x01)
#define EXT_PARAM_FREQUENCY_AGILITY                ((UCHAR)0x04)

//////////////////////////////////////////////
// Radio TX Power Definitions
//////////////////////////////////////////////
#define RADIO_TX_POWER_MASK                        ((UCHAR)0x03)
#define RADIO_TX_POWER_MINUS20DB                   ((UCHAR)0x00)
#define RADIO_TX_POWER_MINUS10DB                   ((UCHAR)0x01)
#define RADIO_TX_POWER_MINUS5DB                    ((UCHAR)0x02)
#define RADIO_TX_POWER_0DB                         ((UCHAR)0x03)

//////////////////////////////////////////////
// Channel Status
//////////////////////////////////////////////
#define STATUS_CHANNEL_STATE_MASK                  ((UCHAR)0x03)
#define STATUS_UNASSIGNED_CHANNEL                  ((UCHAR)0x00)
#define STATUS_ASSIGNED_CHANNEL                    ((UCHAR)0x01)
#define STATUS_SEARCHING_CHANNEL                   ((UCHAR)0x02)
#define STATUS_TRACKING_CHANNEL                    ((UCHAR)0x03)

//////////////////////////////////////////////
// Standard capabilities defines
//////////////////////////////////////////////
#define CAPABILITIES_NO_RX_CHANNELS                ((UCHAR)0x01)
#define CAPABILITIES_NO_TX_CHANNELS                ((UCHAR)0x02)
#define CAPABILITIES_NO_RX_MESSAGES                ((UCHAR)0x04)
#define CAPABILITIES_NO_TX_MESSAGES                ((UCHAR)0x08)
#define CAPABILITIES_NO_ACKD_MESSAGES              ((UCHAR)0x10)
#define CAPABILITIES_NO_BURST_TRANSFER             ((UCHAR)0x20)

//////////////////////////////////////////////
// Advanced capabilities defines
//////////////////////////////////////////////
#define CAPABILITIES_OVERUN_UNDERRUN               ((UCHAR)0x01)     // Support for this functionality has been dropped
#define CAPABILITIES_NETWORK_ENABLED               ((UCHAR)0x02)
#define CAPABILITIES_AP1_VERSION_2                 ((UCHAR)0x04)     // This Version of the AP1 does not support transmit and only had a limited release
#define CAPABILITIES_SERIAL_NUMBER_ENABLED         ((UCHAR)0x08)
#define CAPABILITIES_PER_CHANNEL_TX_POWER_ENABLED  ((UCHAR)0x10)
#define CAPABILITIES_LOW_PRIORITY_SEARCH_ENABLED   ((UCHAR)0x20)
#define CAPABILITIES_SCRIPT_ENABLED                ((UCHAR)0x40)
#define CAPABILITIES_SEARCH_LIST_ENABLED           ((UCHAR)0x80)

//////////////////////////////////////////////
// Advanced capabilities 2 defines
//////////////////////////////////////////////
#define CAPABILITIES_LED_ENABLED                   ((UCHAR)0x01)
#define CAPABILITIES_EXT_MESSAGE_ENABLED           ((UCHAR)0x02)
#define CAPABILITIES_SCAN_MODE_ENABLED             ((UCHAR)0x04)
#define CAPABILITIES_RESERVED                      ((UCHAR)0x08)
#define CAPABILITIES_PROX_SEARCH_ENABLED           ((UCHAR)0x10)
#define CAPABILITIES_EXT_ASSIGN_ENABLED            ((UCHAR)0x20)
#define CAPABILITIES_FREE_1                        ((UCHAR)0x40)
#define CAPABILITIES_FIT1_ENABLED                  ((UCHAR)0x80)

//////////////////////////////////////////////
// Advanced capabilities 3 defines
//////////////////////////////////////////////
#define CAPABILITIES_SENSRCORE_ENABLED             ((UCHAR)0x01)
#define CAPABILITIES_RESERVED_1                    ((UCHAR)0x02)
#define CAPABILITIES_RESERVED_2                    ((UCHAR)0x04)
#define CAPABILITIES_RESERVED_3                    ((UCHAR)0x08)


//////////////////////////////////////////////
// Burst Message Sequence
//////////////////////////////////////////////
#define CHANNEL_NUMBER_MASK                        ((UCHAR)0x1F)
#define SEQUENCE_NUMBER_MASK                       ((UCHAR)0xE0)
#define SEQUENCE_NUMBER_ROLLOVER                   ((UCHAR)0x60)
#define SEQUENCE_FIRST_MESSAGE                     ((UCHAR)0x00)
#define SEQUENCE_LAST_MESSAGE                      ((UCHAR)0x80)
#define SEQUENCE_NUMBER_INC                        ((UCHAR)0x20)

//////////////////////////////////////////////
// Control Message Flags
//////////////////////////////////////////////
#define BROADCAST_CONTROL_BYTE                     ((UCHAR)0x00)
#define ACKNOWLEDGED_CONTROL_BYTE                  ((UCHAR)0xA0)

//////////////////////////////////////////////
// Response / Event Codes
//////////////////////////////////////////////
#define RESPONSE_NO_ERROR                          ((UCHAR)0x00)
#define NO_EVENT                                   ((UCHAR)0x00)

#define EVENT_RX_SEARCH_TIMEOUT                    ((UCHAR)0x01)
#define EVENT_RX_FAIL                              ((UCHAR)0x02)
#define EVENT_TX                                   ((UCHAR)0x03)
#define EVENT_TRANSFER_RX_FAILED                   ((UCHAR)0x04)
#define EVENT_TRANSFER_TX_COMPLETED                ((UCHAR)0x05)
#define EVENT_TRANSFER_TX_FAILED                   ((UCHAR)0x06)
#define EVENT_CHANNEL_CLOSED                       ((UCHAR)0x07)
#define EVENT_RX_FAIL_GO_TO_SEARCH                 ((UCHAR)0x08)
#define EVENT_CHANNEL_COLLISION                    ((UCHAR)0x09)
#define EVENT_TRANSFER_TX_START                    ((UCHAR)0x0A)           // a pending transmit transfer has begun

#define EVENT_CHANNEL_ACTIVE                       ((UCHAR)0x0F)

#define EVENT_TRANSFER_TX_NEXT_MESSAGE             ((UCHAR)0x11)           // only enabled in FIT1

#define CHANNEL_IN_WRONG_STATE                     ((UCHAR)0x15)           // returned on attempt to perform an action from the wrong channel state
#define CHANNEL_NOT_OPENED                         ((UCHAR)0x16)           // returned on attempt to communicate on a channel that is not open
#define CHANNEL_ID_NOT_SET                         ((UCHAR)0x18)           // returned on attempt to open a channel without setting the channel ID
#define CLOSE_ALL_CHANNELS                         ((UCHAR)0x19)           // returned when attempting to start scanning mode, when channels are still open

#define TRANSFER_IN_PROGRESS                       ((UCHAR)0x1F)           // returned on attempt to communicate on a channel with a TX transfer in progress
#define TRANSFER_SEQUENCE_NUMBER_ERROR             ((UCHAR)0x20)           // returned when sequence number is out of order on a Burst transfer
#define TRANSFER_IN_ERROR                          ((UCHAR)0x21)
#define TRANSFER_BUSY                              ((UCHAR)0x22)

#define MESSAGE_SIZE_EXCEEDS_LIMIT                 ((UCHAR)0x27)           // returned if a data message is provided that is too large
#define INVALID_MESSAGE                            ((UCHAR)0x28)           // returned when the message has an invalid parameter
#define INVALID_NETWORK_NUMBER                     ((UCHAR)0x29)           // returned when an invalid network number is provided
#define INVALID_LIST_ID                            ((UCHAR)0x30)           // returned when the provided list ID or size exceeds the limit
#define INVALID_SCAN_TX_CHANNEL                    ((UCHAR)0x31)           // returned when attempting to transmit on channel 0 when in scan mode
#define INVALID_PARAMETER_PROVIDED                 ((UCHAR)0x33)           // returned when an invalid parameter is specified in a configuration message

#define EVENT_QUE_OVERFLOW                         ((UCHAR)0x35)           // ANT event que has overflowed and lost 1 or more events

#define EVENT_CLK_ERROR                            ((UCHAR)0x36)           //!! debug XOSC16M

#define SCRIPT_FULL_ERROR                          ((UCHAR)0x40)           // error writing to script, memory is full
#define SCRIPT_WRITE_ERROR                         ((UCHAR)0x41)           // error writing to script, bytes not written correctly
#define SCRIPT_INVALID_PAGE_ERROR                  ((UCHAR)0x42)           // error accessing script page
#define SCRIPT_LOCKED_ERROR                        ((UCHAR)0x43)           // the scripts are locked and can't be dumped

#define NO_RESPONSE_MESSAGE                        ((UCHAR)0x50)           // returned to the Command_SerialMessageProcess function, so no reply message is generated
#define RETURN_TO_MFG                              ((UCHAR)0x51)           // default return to any mesg when the module determines that the mfg procedure has not been fully completed

#define FIT_ACTIVE_SEARCH_TIMEOUT                  ((UCHAR)0x60)           // Fit1 only event added for timeout of the pairing state after the Fit module becomes active
#define FIT_WATCH_PAIR                             ((UCHAR)0x61)           // Fit1 only
#define FIT_WATCH_UNPAIR                           ((UCHAR)0x62)           // Fit1 only

#endif /*ANTDEFINES_H_*/

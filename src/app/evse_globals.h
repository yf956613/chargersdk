/**
* @file evse_globals.h
* @brief
* @author rgw
* @version v1.0
* @date 2017-01-22
*/
#ifndef  __EVSE_GLOBALS_H
#define  __EVSE_GLOBALS_H

#include "EVSE.h"
#include "interface_rfid.h"
#include "userlib_list.h"

#define BIT_0  ( 1 << 0 )
#define BIT_1  ( 1 << 1 )
#define BIT_2  ( 1 << 2 )
#define BIT_3  ( 1 << 3 )
#define BIT_4  ( 1 << 4 )
#define BIT_5  ( 1 << 5 )
#define BIT_6  ( 1 << 6 )
#define BIT_7  ( 1 << 7 )
#define BIT_8  ( 1 << 8 )
#define BIT_9  ( 1 << 9 )
#define BIT_10 ( 1 << 10 )
#define BIT_11 ( 1 << 11 )
#define BIT_12 ( 1 << 12 )
#define BIT_13 ( 1 << 13 )
#define BIT_14 ( 1 << 14 )
#define BIT_15 ( 1 << 15 )
#define BIT_16 ( 1 << 16 )
#define BIT_17 ( 1 << 17 )
#define BIT_18 ( 1 << 18 )
#define BIT_19 ( 1 << 19 )
#define BIT_20 ( 1 << 20 )
#define BIT_21 ( 1 << 21 )
#define BIT_22 ( 1 << 22 )
#define BIT_23 ( 1 << 23 )
#define BIT_24 ( 1 << 24 )
#define BIT_25 ( 1 << 25 )
#define BIT_26 ( 1 << 26 )
#define BIT_27 ( 1 << 27 )
#define BIT_28 ( 1 << 28 )
#define BIT_29 ( 1 << 29 )
#define BIT_30 ( 1 << 30 )
#define BIT_31 ( 1 << 31 )

/*---------------------------------------------------------------------------/
/ xEventGroup
/---------------------------------------------------------------------------*/
//定义xHandleEventGroupRFID
#define defEventBitGETUID       BIT_0
//定义xHandleEventGroupStartCharge
#define defEventBitAuthed       BIT_0
#define defEventBitLocked       BIT_1
#define defEventBitVoltOK       BIT_2
#define defEventBitCurrOK       BIT_3
#define defEventBitCPOK         BIT_4
#define defEventBitCCOK         BIT_5
#define defEventBitConnTempOK   BIT_6
#define defEventBitACTempOK     BIT_7
//#define defEventBit             BIT_8
//定义xHandleEventTimerCBNotify
#define defEventBitTimerCBTemp              BIT_0
#define defEventBitTimerCBLockState         BIT_1
#define defEventBitTimerCBCPCCState         BIT_2
#define defEventBitTimerCBChargingData      BIT_3
#define defEventBitTimerCBEVSEState         BIT_4
#define defEventBitTimerCBRFID              BIT_5
#define defEventBitTimerCBDataRefresh       BIT_6




extern EVSE_t *pEVSE;
extern UserList_t *pListChargePoint;
extern RFIDDev_t *pRFIDDev;

#endif

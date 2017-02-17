/**
* @file EVSE.h
* @brief
* @author rgw
* @version v1.0
* @date 2017-01-22
*/
#ifndef  __EVSE_H
#define  __EVSE_H

#include "stm32f4xx.h"
#include "errorcode.h"

typedef ErrorCode_t (*pEVSE_ft)(void *pvEVSE);

typedef struct _EVSEInfo
{
    uint8_t ucSN[24]; //设备唯一序列号
    uint8_t ucSNLength;
    uint8_t ucID[24]; //平台分配ID
    uint8_t ucIDLenght;
    uint8_t ucType;   //1：直流设备 2：交流设备 3：交直流一体设备 4：无线设备 5：其他
    double dLng;      //经度，保留后六位
    double dLat;      //纬度，保留后六位

    pEVSE_ft GetSN;
    pEVSE_ft GetID;
    pEVSE_ft GetType;
    pEVSE_ft GetLngLat;
}EVSEInfo_t;
typedef struct _EVSEState
{
    uint32_t ulScramState;
    uint32_t ulKnockState;
    uint32_t ulPEState;
    uint32_t ulPowerOffState;
    uint32_t ulArresterState;

    pEVSE_ft GetScramState;
    pEVSE_ft GetKnockState;
    pEVSE_ft GetPEState;
    pEVSE_ft GetPowerOffState;
    pEVSE_ft GetArresterState;
}EVSEState_t;

typedef struct _EVSE
{
    EVSEInfo_t info;
    EVSEState_t state;
}EVSE_t;

EVSE_t *EVSECreate(void);
void EVSEinit(void);

#endif

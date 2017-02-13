/**
* @file chargepoint.h
* @brief 定义最小充电单元需要的数据与操作
* @author rgw
* @version v1.0
* @date 2017-01-18
*/
#ifndef  __CHARGEPOINT_H
#define  __CHARGEPOINT_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "event_groups.h"

typedef enum __ChargePointStateType
{
    NO_ERR = 0,
    //CP检测
    CP_ERR,
    CP_12V,
    CP_9V,
    CP_9V_PWM,
    CP_6V_PWM,
    //CC检测
    CC_PE,
    CC_NO,
    //插枪检测
    PLUG,
    UNPLUG,
    //枪锁
    LOCK,
    UNLOCK
}ChargePointStateType;

typedef struct _ChargePointStatus
{
    ChargePointStateType ulCPState;     // 检测点1 CP state --12V / 9V / 9V_PWM / 6V_PWM
    ChargePointStateType ulCCState;     // 检测点4 CC state --PE
    ChargePointStateType ulPlugState;
    double dACLTemp;
    double dACNTemp;
    double dBTypeConnectorTemp1;
    double dBTypeConnectorTemp2;
    ChargePointStateType BTypeConnectorLockState; //lock unlock
    double dChargingVoltage;
    double dChargingCurrent;
    double dChargingFrequence;
    EventGroupHandle_t xHandleEventGroupStartCharge;
    EventGroupHandle_t xHandleEventGroupStopCharge;
}ChargePointStatus;

typedef struct _ChargePoint
{
    uint8_t  ucChargePointID;           // 枪号
    ChargePointStatus status;

} ChargePoint_t;

double GetChargingVoltage(ChargePoint_t *pPoint);
double GetChargingCurrent(ChargePoint_t *pPoint);
double GetChargingFrequence(ChargePoint_t *pPoint);

ChargePointStateType GetCPState(ChargePoint_t *pPoint);
ChargePointStateType GetCCState(ChargePoint_t *pPoint);
uint32_t GetPlugState(ChargePoint_t *pPoint);
ChargePointStateType GetBTypeConnectorLock(ChargePoint_t *pPoint); //lock unlock
ChargePointStateType SetBTypeConnectorLock(ChargePoint_t *pPoint);
double GetACLTemp(ChargePoint_t *pPoint);
double GetACNTemp(ChargePoint_t *pPoint);
double GetBTypeConnectorTemp1(ChargePoint_t *pPoint);
double GetBTypeConnectorTemp2(ChargePoint_t *pPoint);
ChargePointStateType StartCharge(ChargePoint_t *pPoint);
ChargePointStateType StopCharge(ChargePoint_t *pPoint);

ChargePoint_t *ChargePointCreate(uint8_t ucChargePointID );
#endif

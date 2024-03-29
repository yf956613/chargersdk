#ifndef SYS_CFG_H
#define SYS_CFG_H

#include "stm32f4xx.h"
#include "errorcode.h"

typedef struct
{
    uint8_t touchtype;
    uint8_t is_calibrate;
    double xfac;
    double yfac;
    uint16_t xoff;
    uint16_t yoff;
} Calibrate_t;


//0   无需升级
//1   待升级
//2   升级成功
//3   升级失败
typedef struct 
{
    uint8_t chargesdk_bin;
    uint8_t evse_cfg;
    uint8_t protocol_cfg;
    uint8_t sys_cfg;
    uint8_t blacklist_cfg;
    uint8_t whitelist_cfg;
    uint32_t chargesdk_bin_crc32;
}UpgradeFlag_t;
typedef struct 
{
    uint8_t use_gprs; // 0:无网络 2:2G 3:3G
    uint8_t use_meter; //1:内部计量  2:单相电表 3：三相电表  4：other电表，需配置
    uint8_t use_rfid; // 1:使用rfid
    uint8_t use_gui; //1:使用GUI
}ModuleSelect_t;

typedef struct
{
    char strVersion[64 + 1];
    char strBootldrCrc32[64 + 1];
    uint32_t ulDispSleepTime_s;
    Calibrate_t xCalibrate;
    UpgradeFlag_t xUpFlag;
    ModuleSelect_t xModule;
    ErrorCode_t(*GetSysCfg)(void *pvSys, void *pvCfgObj);
    ErrorCode_t(*SetSysCfg)(char *jnItemString, void *pvCfgParam, uint8_t type);
    
} Sysconf_t;

void SysCfgInit(Sysconf_t *sysconf);

#endif

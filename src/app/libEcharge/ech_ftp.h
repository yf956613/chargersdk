#ifndef ECH_FTP_H
#define ECH_FTP_H

#include "stm32f4xx.h"
#include "errorcode.h"
typedef struct _ftp_proc
{
    uint32_t ulFTPReGetCnt;
    uint32_t ulFTPReOpenCnt;
    uint32_t ulRecvFileSize;
    uint32_t precent;
}ftp_proc_t;

typedef struct
{
    char strServer[64 + 1];
    char strUser[64 + 1];
    char strPassword[64 + 1];
    char strNewFileName[64 + 1];
    char strNewVersion[64 + 1];
    uint32_t fsize;
    uint16_t usPort;
    uint8_t ucDownloadStart;
    uint8_t ucDownloadStatus;
    ErrorCode_t(*GetFtpCfg)(void *pvFtp, void *pvCfgObj);
    ftp_proc_t ftp_proc;
}EchFtpCfg_t;

void EchFtpInit(EchFtpCfg_t *ftp);

#endif
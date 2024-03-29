/**
* @file taskcreate.c
* @brief 创建任务Todolist 对照表
*        1. 定义STACK大小
*        2. 定义PRIORITY
*        3. 声明任务
*        4. 定义任务句柄
*        5. 任务入口
*        6. 创建任务创建任务Todolist 对照表
* @author rgw
* @version v1.0
* @date 2016-11-03
*/
#include "includes.h"
#include "cli_main.h"
#include "timercallback.h"
#include "bsp.h"
#include "utils.h"
#include "file_op.h"
#include "stringName.h"
#include "bsp_cpu_flash.h"
#include "yaffsfs.h"
#include "yaffs2misc.h"


/*---------------------------------------------------------------------------/
/ 任务栈大小
/---------------------------------------------------------------------------*/
#define defSTACK_TaskInit                   (1024*10)
#define defSTACK_TaskCLI                    (1024 * 50)
#define defSTACK_TaskOTA                    512

/*---------------------------------------------------------------------------/
/ 任务优先级
/---------------------------------------------------------------------------*/
//优先级规则为系统任务优先级低，OTA > 充电任务 > 故障处理 > 系统监视 > 刷卡与通信 > 数据处理与系统任务
#define defPRIORITY_TaskOTA                 31/* 最高*/
#define defPRIORITY_TaskInit                10
#define defPRIORITY_TaskCLI                 2

/*---------------------------------------------------------------------------/
/ 任务名称
/---------------------------------------------------------------------------*/
const char *TASKNAME_INIT           = "TaskInit";
const char *TASKNAME_CLI            = "TaskCLI";
const char *TASKNAME_OTA            = "TaskOTA";



/*---------------------------------------------------------------------------/
/ 任务声明
/---------------------------------------------------------------------------*/
void vTaskInit(void *pvParameters);
void vTaskCLI(void *pvParameters);
void vTaskOTA(void *pvParameters);

/*---------------------------------------------------------------------------/
/ 任务句柄
/---------------------------------------------------------------------------*/
TaskHandle_t xHandleTaskInit = NULL;
TaskHandle_t xHandleTaskCLI = NULL;
TaskHandle_t xHandleTaskOTA = NULL;
/*---------------------------------------------------------------------------/
/ 任务间通信
/---------------------------------------------------------------------------*/
SemaphoreHandle_t xMutexTimeStruct;

EventGroupHandle_t xHandleEventTimerCBNotify = NULL;
EventGroupHandle_t xHandleEventData = NULL;
EventGroupHandle_t xHandleEventDiag = NULL;
EventGroupHandle_t xHandleEventRemote = NULL;
EventGroupHandle_t xHandleEventHMI  = NULL;
EventGroupHandle_t xHandleEventTCP   = NULL;

//队列

QueueHandle_t xHandleQueueErrorPackage = NULL;

//con中还定义了几个定时器，xHandleTimerVolt，xHandleTimerCurr，xHandleTimerCharge分别在使用时进行初始化
//Mutex
extern void fs_init(void);
extern void *_app_start[];
#define APP_ADDRESS         (uint32_t)_app_start

void Jump_To_APP(void)
{
    uart_close(cli_huart);//关闭初始化的设备
    asm("cpsid i");
    asm("ldr sp, =_estack");
    ((void(*)())_app_start[1])();
}

uint32_t initstart;
void vTaskInit(void *pvParameters)
{
    uint8_t *pucBinBuffer;
    uint32_t size;
    uint32_t crc32;
    uint32_t trymax = 3;
    uint32_t tryread = 0;
    char upflag;
    
    char cli_std[1];
    uint32_t cli_std_len;
    char strFindName[256] = { 0 };
    
    uint32_t crc32_calc, crc32_orig;
    char ch_crc32[9] = { 0 };
    ul2uc ul2ucCrc32;
    char filepath[64 + 1] = { 0 };
    int i;
    
    AppObjCreate();
    sys_Init();
    printf_safe("\nPRESS 'C' IN 3 SECONDS FOR CLI MODE...\n");
    while (1)
    {
        cli_std_len = uart_read_wait(cli_huart, (uint8_t *)cli_std, 1, 3000);
        if (cli_std_len >= 1 && (cli_std[0] == 'c' || cli_std[0] == 'C'))
        {
            cli_std[0] = 0;
            cli_std_len = 0;
            SysTaskCreate();
            printf_safe("task init sleep.zZ\n");
            while (1)
            {
                if (initstart == 1)
                {
                    initstart = 0;
                    break;
                }
                vTaskDelay(1000);
            }
        }
        if (tryread < trymax)
        {
            if (find_file(pathUpgradeDir, "new_fw", strFindName) == 1)
            {
                ++tryread;
                for (i = 0; i < 8; i++)
                {
                    ch_crc32[i] = strFindName[i + 7];
                }
                StrToHex(ch_crc32, ul2ucCrc32.ucVal, strlen(ch_crc32));
                crc32_orig = utils_ntohl(ul2ucCrc32.ulVal);
                
                sprintf(filepath, "%s%s", pathUpgradeDir, strFindName);
                pucBinBuffer = GetFileBuffer(filepath, &size);
                if (pucBinBuffer != NULL && size > 0)
                {
                    GetBufferCrc32(pucBinBuffer, size, &crc32_calc);
                    printf_safe("crc32_calc = %x\n", crc32_calc);
                    printf_safe("crc32_orgi = %x\n", crc32_orig);
                    if (crc32_calc != crc32_orig)
                    {
                        printf_safe("Get Crc32 Err!\n");
                        free(pucBinBuffer);
                    }
                    else
                    {
                        printf_safe("Crc32 OK!\n");
                        printf_safe("正在升级程序，请勿断电！\n");
                        bsp_WriteCpuFlash(APP_ADDRESS, pucBinBuffer, size);
                        free(pucBinBuffer);
                        yaffs_unlink(filepath);
                        upflag = '2';
                        set_tmp_file(pathUpgradeTmp, &upflag);
                    }
                }
            }
            else
            {
                printf_safe("app_start!\n");
                Jump_To_APP();
            }
        }
        else
        {
            yaffs_unlink(filepath);
            upflag = '3';
            set_tmp_file(pathUpgradeTmp, &upflag);
            printf_safe("升级失败, 请手动重启或检查待升级固件与CRC32值!\n");
            Jump_To_APP();
        }
        vTaskDelay(2000);
    }
}
void vTaskCLI(void *pvParameters)
{
    cli_main();
}


void TaskInit(void)
{
    xTaskCreate( vTaskInit, TASKNAME_INIT, defSTACK_TaskInit, NULL, defPRIORITY_TaskInit, &xHandleTaskInit );
}

void SysTaskCreate (void)
{
    xTaskCreate( vTaskCLI, TASKNAME_CLI, defSTACK_TaskCLI, NULL, defPRIORITY_TaskCLI, &xHandleTaskCLI );
    //xTaskCreate( vTaskOTA, TASKNAME_OTA, defSTACK_TaskOTA, NULL, defPRIORITY_TaskOTA, &xHandleTaskOTA );
}

/** @brief
 */
void AppObjCreate (void)
{
    xMutexTimeStruct = xSemaphoreCreateMutex();

    xHandleQueueErrorPackage = xQueueCreate(100, sizeof(ErrorPackage_t));

    //TimerHeartbeat远程服务器连接后开启定时器
}


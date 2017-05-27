﻿/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.30                          *
*        Compiled Jul  1 2015, 10:50:32                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "xbffontcreate.h"
#include "HMI_Start.h"
#include "touchtimer.h"
#include "bmpdisplay.h"
#include "touchtimer.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_WINDOW_0     (GUI_ID_USER + 0x10)
//#define ID_BUTTON_0     (GUI_ID_USER + 0x01)
//#define ID_BUTTON_1     (GUI_ID_USER + 0x04)
#define ID_BUTTON_MANAGER   (GUI_ID_USER + 0x12)
#define ID_TEXT_0     (GUI_ID_USER + 0x11)
#define ID_IMAGE_0     (GUI_ID_USER + 0x0A)

#define ID_IMAGE_0_IMAGE_0     0x00

// USER START (Optionally insert additional defines)
#define ID_TEXT_1     (GUI_ID_USER + 0x0B)
#define ID_TEXT_2     (GUI_ID_USER + 0x0C)
#define ID_TEXT_3     (GUI_ID_USER + 0x0D)
#define ID_TEXT_4     (GUI_ID_USER + 0x0E)

#define ID_TEXT_5     (GUI_ID_USER + 0x05)
#define ID_EDIT_0     (GUI_ID_USER + 0x06)
#define ID_TEXT_6     (GUI_ID_USER + 0x07)
#define ID_TEXT_7     (GUI_ID_USER + 0x02)
#define ID_EDIT_1     (GUI_ID_USER + 0x03)
#define ID_TEXT_8     (GUI_ID_USER + 0x09)
#define ID_TEXT_9     (GUI_ID_USER + 0x0F)
#define ID_TEXT_A     (GUI_ID_USER + 0x01)
#define ID_TEXT_B     (GUI_ID_USER + 0x04)
#define ID_MULTIEDIT_0  (GUI_ID_USER + 0x13)
#define ID_TimerTime    0

//14行1列，14个故障项
#define TEXT_MAX_X 1
#define TEXT_MAX_Y 14
#define ERROR_LINE 14
#define ERROR_CAL 1
//后续将编辑和文本的滚轮方式用链表进行封装
static EDIT_Handle _aahEdit[TEXT_MAX_Y][TEXT_MAX_X];
static TEXT_Handle _aahText[ERROR_LINE][ERROR_CAL];
static BUTTON_Handle _framebutton;
static int _x,_y;
// USER END
volatile int   Id;
extern uint8_t *bmpbuffer;
extern FIL BMPFile_BCGROUND;
extern char *bmpBackGround;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
{
    { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
//    { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 67, 80, 250, 40, 0, 0x0, 0 },
//    { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 404, 80, 250, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_A, 67, 80, 250, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_B, 450, 80, 250, 40, 0, 0x0, 0 },
    //{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 245, 50, 254, 50, 0, 0x0, 0 },
    { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 0, 0, 789, 459, 0, 0, 0 },//尝试bmp单独显示
    //{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 114, 299, 50, 50, 0, 0, 0 },
    // USER START (Optionally insert additional widgets)
    { TEXT_CreateIndirect, "Text", ID_TEXT_1, 630, 0, 80, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_2, 720, 0, 70, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_3, 540, 0, 90, 16, 0, 0x0, 0 },//网络信号强度
    { TEXT_CreateIndirect, "Text", ID_TEXT_4, 225, 367, 300, 20, 0, 0x0, 0 },//最底端的说明
    { TEXT_CreateIndirect, "Text", ID_TEXT_5, 422, 177, 80, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 510, 177, 80, 30, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_6, 598, 177, 80, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_7, 422, 216, 80, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 510, 216, 80, 30, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_8, 598, 216, 80, 30, 0, 0x0, 0 },
    //{ BUTTON_CreateIndirect, "Button", ID_BUTTON_MANAGER, 740, 380, 50, 50, 0, 0x0, 0 },
    //{ MULTIEDIT_CreateIndirect, "Multiedit", ID_MULTIEDIT_0, 495, 145, 300, 250, 0, 0x0, 0 },
    // USER END
};
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
// USER START (Optionally insert additional static code)
static void Timer_Process(WM_MESSAGE *pMsg)
{
    CON_t *pCON;
    static uint32_t i = 0;
    uint8_t strPowerFee[10];
    uint8_t strServiceFee[10];
    WM_HWIN hWin_Error;
    EventBits_t uxBitRFID;

    WM_HWIN hWin = pMsg->hWin;

    pCON = CONGetHandle(0);

    CaliDone_Analy(hWin);
    Caculate_RTC_Show(pMsg, ID_TEXT_1, ID_TEXT_2);

    if(pCON->order.ucStartType == 4)
    {
        uxBitRFID = xEventGroupWaitBits(pRFIDDev->xHandleEventGroupRFID,
                                        defEventBitGotIDtoHMI,
                                        pdTRUE, pdTRUE, 0);
        xEventGroupClearBits(pRFIDDev->xHandleEventGroupRFID,defEventBitGotIDtoHMI);
        if((uxBitRFID & defEventBitGotIDtoHMI) == defEventBitGotIDtoHMI)
        {
            //dispbmpNOFree(1,"system/encodeCharge.bmp", 0, 130, 170, 1, 1,hWin);
            free(bmpBackGround);
            free(bmpbuffer);
            WM_DeleteWindow(hWin);
            PutOut_Card_Info();
        }
    }
    else if(pCON->order.ucStartType == 5)
    {
        free(bmpBackGround);
        free(bmpbuffer);
        WM_DeleteWindow(hWin);
        PutOut_Charging();
    }
    //需要增加3G模块的信号强度判断
    switch(i % 5)
    {
    case 0:
        TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_3), "信号:非常强");
        break;
    case 1:
        TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_3), "信号:一般");
        break;
    case 2:
        TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_3), "信号:差");
        break;
    case 3:
        TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_3), "信号:极差");
        break;
    default:
        TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_3), "信号:无");
        break;
    }

    //充电费和服务费的费用值显示
    sprintf(strPowerFee, "%.2lf", pEVSE->info.dDefSegFee);
    sprintf(strServiceFee, "%.2lf", pEVSE->info.dServiceFee);
    EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_0), strPowerFee);//电费
    EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_1), strServiceFee);//服务费
    EDIT_SetCursorAtPixel(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0),100);

    ErrWindow_Show(hWin);
}
// USER END
static void _cbFrame(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      int Id = WM_GetId(pMsg->hWinSrc);      // Id of widget
        ;
    }
    break;
  }
}
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE *pMsg)
{
    const void *pData;
    WM_HWIN      hItem;
    U32          FileSize;
    int          NCode;
    IMAGE_Handle imageHandle;

    uint8_t *buf = "56";
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //
        // Initialization of 'Framewin'
        //
        //FrameWin_Init(pMsg, ID_TEXT_1, ID_TEXT_2, ID_TEXT_3, ID_TEXT_4);
        //IMAGE_SetBMP(WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0), bmpBackGround, BMPFile_BCGROUND.obj.objsize);

        //FrameWin_Init(pMsg, ID_TEXT_1, ID_TEXT_2, ID_TEXT_3, ID_TEXT_4);
        FrameWin_Init_test(pMsg, ID_TEXT_1, ID_TEXT_2, ID_TEXT_3, ID_TEXT_4,ID_IMAGE_0);
        //
        // Initialization of 'Edit'
        //
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0), &XBF24_Font, " ");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1), &XBF24_Font, " ");
        EDIT_SetTextAlign(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0), GUI_TA_RIGHT | GUI_TA_VCENTER);
        EDIT_SetTextAlign(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1), GUI_TA_RIGHT | GUI_TA_VCENTER);
        // Initialization of 'Text'
        //
        //Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), &XBF36_Font, GUI_BLACK, "请选择支付方式");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_5), &XBF24_Font, GUI_BLACK, "充电费");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_6), &XBF24_Font, GUI_BLACK, "元/度");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_7), &XBF24_Font, GUI_BLACK, "服务费");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_8), &XBF24_Font, GUI_BLACK, "元/度");
        //
        // Initialization of 'Button'
        //
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_A), &XBF24_Font, GUI_BLACK, "手机支付请扫描二维码");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_B), &XBF24_Font, GUI_BLACK, "刷卡支付请刷卡");

        //显示二维码
        dispbmpNOFree(0,"system/encodeCharge.bmp", 0, 130, 170, 1, 1,pMsg->hWin);//不能释放内存,需要在切换界面时再把图片内存释放掉

//        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0), GUI_TA_LEFT | GUI_TA_VCENTER,
//                    &XBF24_Font, BUTTON_CI_UNPRESSED, GUI_BLUE, BUTTON_CI_UNPRESSED, GUI_BLUE, "手机支付请扫描二维码");
//        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1), GUI_TA_HCENTER | GUI_TA_VCENTER,
//                    &XBF24_Font, BUTTON_CI_UNPRESSED, GUI_BLUE, BUTTON_CI_UNPRESSED, GUI_BLUE, "刷卡支付请刷卡");

        //Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MANAGER), GUI_TA_HCENTER | GUI_TA_VCENTER,
         //           &XBF24_Font, BUTTON_CI_UNPRESSED, GUI_GREEN, BUTTON_CI_UNPRESSED, GUI_GREEN, "管理");
        //BUTTON_SetDefaultBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MANAGER))
        //BUTTON_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MANAGER),BUTTON_CI_UNPRESSED|BUTTON_CI_PRESSED,GUI_BLUE);
//        WM_SetCallback(pMsg->hWin, _cbFrame);
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id)
        {
        case ID_BUTTON_MANAGER:
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                WM_DeleteWindow(pMsg->hWin);
                Keypad_GetValue(LOGIN_PASSWD);
                break;
            case WM_NOTIFICATION_RELEASED:
                WM_DeleteWindow(pMsg->hWin);
                Keypad_GetValue(LOGIN_PASSWD);
                break;
            }
            break;
//        case ID_BUTTON_0: // Notifications sent by 'Button'
//            switch(NCode)
//            {
//            case WM_NOTIFICATION_CLICKED:
//                // USER START (Optionally insert code for reacting on notification message)
//                // USER END
//                break;
//            case WM_NOTIFICATION_RELEASED:
//                // USER START (Optionally insert code for reacting on notification message)
//                // USER END
//                break;
//                // USER START (Optionally insert additional code for further notification handling)
//                // USER END
//            }
//            break;
//        case ID_BUTTON_1: // Notifications sent by 'Button'
//            switch(NCode)
//            {
//            case WM_NOTIFICATION_CLICKED:
//                // USER START (Optionally insert code for reacting on notification message)
//                // USER END
//                break;
//            case WM_NOTIFICATION_RELEASED:
//                // USER START (Optionally insert code for reacting on notification message)
//                // USER END
//                break;
//                // USER START (Optionally insert additional code for further notification handling)
//                // USER END
//            }
//            break;
            // USER START (Optionally insert additional code for further Ids)
            // USER END
        }
        break;
        // USER START (Optionally insert additional message handling)
    case WM_TIMER:
        /* 显示时间和日期 */
//        Id = WM_GetTimerId(pMsg->Data.v);
        Timer_Process(pMsg);
        /* 重启定时器 */
        WM_RestartTimer(pMsg->Data.v, 200);
        break;
        // USER END
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void)
{
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    WM_CreateTimer(WM_GetClientWindow(hWin), ID_TimerTime, 1000, 0);

    return hWin;
}
// USER START (Optionally insert additional public code)
/** @brief
 *  输出充电桩欢迎界面
 * @param
 * @param
 * @return
 *
 */
void PutOut_Home()
{
    WM_HWIN hWin;

    led_ctrl(1,green,keep_on);
    hWin = CreateFramewin();

    while(1)
    {
        GUI_Delay(500);
        dispbmp("system/dpc.bmp", 0, 5, 5, 1, 1);
        vTaskDelay(500);
    }
}
// USER END

/*************************** End of file ****************************/


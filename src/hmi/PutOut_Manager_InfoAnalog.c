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
// USER START (Optionally insert additional defines)
#define ID_TEXT_1     (GUI_ID_USER + 0x0B)
#define ID_TEXT_2     (GUI_ID_USER + 0x0C)
#define ID_TEXT_3     (GUI_ID_USER + 0x0D)
#define ID_TEXT_4     (GUI_ID_USER + 0x0E)

#define ID_BUTTON_0  (GUI_ID_USER + 0x00)//信息
#define ID_BUTTON_1  (GUI_ID_USER + 0x01)//历史
#define ID_BUTTON_2  (GUI_ID_USER + 0x02)//系统
#define ID_BUTTON_3  (GUI_ID_USER + 0x03)//退出
#define ID_BUTTON_4  (GUI_ID_USER + 0x04)//模拟
#define ID_BUTTON_5  (GUI_ID_USER + 0x05)//状态
#define ID_TEXT_5  (GUI_ID_USER + 0x06)//
#define ID_EDIT_0  (GUI_ID_USER + 0x07)//
#define ID_TEXT_6  (GUI_ID_USER + 0x08)//
#define ID_TEXT_7  (GUI_ID_USER + 0x09)//
#define ID_TEXT_8  (GUI_ID_USER + 0x0A)//
#define ID_TEXT_9  (GUI_ID_USER + 0x0F)//
#define ID_TEXT_10  (GUI_ID_USER + 0x10)//
#define ID_TEXT_11  (GUI_ID_USER + 0x11)//
#define ID_EDIT_1  (GUI_ID_USER + 0x12)//
#define ID_EDIT_2  (GUI_ID_USER + 0x13)//
#define ID_EDIT_3  (GUI_ID_USER + 0x14)//
#define ID_EDIT_4  (GUI_ID_USER + 0x15)//
#define ID_EDIT_5  (GUI_ID_USER + 0x16)//
#define ID_EDIT_6  (GUI_ID_USER + 0x17)//

#define ID_TimerTime    0
// USER END

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
    // USER START (Optionally insert additional widgets)
    { TEXT_CreateIndirect, "Text", ID_TEXT_1, 630, 0, 80, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_2, 720, 0, 70, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_3, 540, 0, 90, 16, 0, 0x0, 0 },//网络信号强度
    { TEXT_CreateIndirect, "Text", ID_TEXT_4, 225, 367, 300, 20, 0, 0x0, 0 },//最底端的说明
    { BUTTON_CreateIndirect, "信息查询", ID_BUTTON_0, 70, 120, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "历史记录", ID_BUTTON_1, 70, 184, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "系统配置", ID_BUTTON_2, 70, 247, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "退    出", ID_BUTTON_3, 70, 312, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "模拟量", ID_BUTTON_4, 285, 40, 140, 40, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "状态量", ID_BUTTON_5, 491, 40, 140, 40, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "交流电压:", ID_TEXT_5, 300, 100, 150, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 477, 100, 100, 30, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "交流电流:", ID_TEXT_6, 300, 140, 150, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "充电导引电压:", ID_TEXT_7, 300, 178, 160, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "频    率:", ID_TEXT_8, 300, 216, 150, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "A插座温度:", ID_TEXT_9, 300, 256, 150, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "B插座温度:", ID_TEXT_10, 300, 296, 150, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "接线温度:", ID_TEXT_11, 300, 336, 150, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 477, 140, 100, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 477, 178, 100, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 477, 216, 100, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 477, 256, 100, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_5, 477, 296, 100, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_6, 477, 336, 100, 30, 0, 0x64, 0 },
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
// USER START (Optionally insert additional static code)
// USER END
static void Timer_Process(WM_MESSAGE *pMsg)
{
    uint8_t i = 0;
    WM_HWIN hWin = pMsg->hWin;

    Caculate_RTC_Show(pMsg,ID_TEXT_1,ID_TEXT_2);
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

    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0),&XBF24_Font,"220.0V");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1),&XBF24_Font,"32.00A");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_2),&XBF24_Font,"12.00V");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_3),&XBF24_Font,"50Hz");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_4),&XBF24_Font,"30.0℃");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_5),&XBF24_Font,"30.0℃");
    Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_6),&XBF24_Font,"30.0℃");

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
    int          Id;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //
        // Initialization of 'Framewin'
        //
        FrameWin_Init(pMsg,ID_TEXT_1,ID_TEXT_2,ID_TEXT_3,ID_TEXT_4);
        //
        //Initialization of 'Text'
        //
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_5),&XBF24_Font,GUI_BLACK,"交流电压:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_6),&XBF24_Font,GUI_BLACK,"交流电流:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_7),&XBF24_Font,GUI_BLACK,"充电导引电压:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_8),&XBF24_Font,GUI_BLACK,"频    率:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_9),&XBF24_Font,GUI_BLACK,"A插座温度:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_10),&XBF24_Font,GUI_BLACK,"B插座温度:");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_11),&XBF24_Font,GUI_BLACK,"接线温度:");
        //
        // Initialization of 'Edit'
        //
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_2),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_3),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_4),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_5),&XBF24_Font,"00");
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_6),&XBF24_Font,"00");
        //
        // Initialization of 'Button'
        //
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_GREEN,BUTTON_CI_UNPRESSED,GUI_RED,"信息查询");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLUE,BUTTON_CI_UNPRESSED,GUI_BLUE,"历史查询");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLUE,BUTTON_CI_UNPRESSED,GUI_BLUE,"系统配置");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLUE,BUTTON_CI_UNPRESSED,GUI_BLUE,"退    出");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_GREEN,BUTTON_CI_UNPRESSED,GUI_RED,"模拟量");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_BLUE,BUTTON_CI_UNPRESSED,GUI_BLUE,"状态量");
//        BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0),BUTTON_CI_UNPRESSED,GUI_GREEN);
//        BUTTON_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0),BUTTON_CI_UNPRESSED,GUI_GREEN);

//         BUTTON_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0), BUTTON_CI_DISABLED, GUI_GREEN);
//        BUTTON_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1), BUTTON_CI_PRESSED, GUI_GREEN);
//        BUTTON_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2), BUTTON_CI_UNPRESSED, GUI_GREEN);


        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id) {
        case ID_BUTTON_0: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
          break;
        case ID_BUTTON_1: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
          break;
        case ID_BUTTON_2: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
          break;
        case ID_BUTTON_3: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
          break;
        case ID_BUTTON_4: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
          break;
        case ID_BUTTON_5: // Notifications sent by 'Button'
          switch(NCode) {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
          }
        }
        break;
        // USER START (Optionally insert additional message handling)
    case WM_TIMER:
        /* 显示时间和日期 */
        Timer_Process(pMsg);
        /* 重启定时器 */
        WM_RestartTimer(pMsg->Data.v, REFLASH);
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
// USER START (Optionally insert additional public code)
/*********************************************************************
*
*       CreateManagerInfoAnalog
*/
WM_HWIN CreateManagerInfoAnalog(void);
WM_HWIN CreateManagerInfoAnalog(void)
{
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    WM_CreateTimer(WM_GetClientWindow(hWin), ID_TimerTime, 1000, 0);

    return hWin;
}
/** @brief
 *  输出管理员界面里的信息查询模拟量部分
 * @param
 * @param
 * @return
 *
 */

void PutOut_Manager_InfoAnalog()
{
    CreateManagerInfoAnalog();
    while(1)
    {
        dispbmp("system/dpc.bmp", 0, 5, 5, 1, 1);
        GUI_Delay(1000);
    }
}
// USER END

/*************************** End of file ****************************/



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
*
*   BUTTON_0    信息查询                                             *
*   BUTTON_1    历史记录
*   BUTTON_2    系统配置
*   BUTTON_3    退出
*   BUTTON_4    模拟量 告警记录
*   BUTTON_5    状态量 充电记录                                         *
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
#define ID_IMAGE_0    (GUI_ID_USER + 0x1C)
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

#define ID_TimerTime    1
#define ID_TimerFlush   2
#define ID_TimerSignal  3
// USER END
static WM_HWIN _hWinManagerInfoAnalog;
static WM_HTIMER _timerRTC,_timerData,_timerSignal;
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
    { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 0, 0, 789, 459, 0, 0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_1, 630, 0, 80, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_2, 720, 0, 70, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_3, 440, 0, 180, 16, 0, 0x0, 0 },//网络信号强度
    { TEXT_CreateIndirect, "Text", ID_TEXT_4, 225, 367, 300, 20, 0, 0x0, 0 },//最底端的说明
    { BUTTON_CreateIndirect, "信息查询", ID_BUTTON_0, 50, 70, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "历史记录", ID_BUTTON_1, 50, 140, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "系统配置", ID_BUTTON_2, 50, 210, 150, 50, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "退    出", ID_BUTTON_3, 50, 280, 150, 50, 0, 0x0, 0 },
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
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void Data_Flush(WM_MESSAGE *pMsg)
{
    CON_t *pCon;
    uint8_t strTmp[10];

    pCon = CONGetHandle(0);

    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dChargingVoltage);
    strcat(strTmp,"V");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0),strTmp);

    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dChargingCurrent);
    strcat(strTmp,"A");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1),strTmp);

    /// TODO (zshare#1#): //share
    /**< 控制导引电压确认 */
    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",Sys_samp.DC.CP1);
    strcat(strTmp,"V");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_2),strTmp);

    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dChargingFrequence);
    strcat(strTmp,"Hz");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_3),strTmp);

    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dBTypeSocketTemp1);
    strcat(strTmp,"℃");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_4),strTmp);

    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dBTypeSocketTemp2);
    strcat(strTmp,"℃");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_5),strTmp);

    /// TODO (zshare#1#): ///接线温度
    memset(strTmp,'\0',strlen(strTmp));
    sprintf(strTmp,"%.1f",pCon->status.dACLTemp);//acl or acn
    strcat(strTmp,"℃");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_6),strTmp);
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

    switch (pMsg->MsgId)
    {
    case WM_PAINT:
        /// TODO (zshare#1#): 下面的if不起作用.\
        但是if里嵌套的if起作用,目前先用此来规避不起作用的if
        if(_hWinManagerInfoAnalog == cur_win)
        {
            /**< 数据处理 */
            //Data_Process(pMsg);
            /**< 信号数据处理 */
            Signal_Show();
            /**< 灯光控制 */
            Led_Show();
            /**< 如果界面发生了切换 */
            if(_hWinManagerInfoAnalog == cur_win)
            {
                /**< 故障分析 */
                Err_Analy(pMsg->hWin);
                /**< 特殊触控点分析 */
                CaliDone_Analy(pMsg->hWin);
            }
        }
        break;
    case WM_INIT_DIALOG:
        //
        // Initialization of 'Framewin'
        //
        FrameWin_Init(pMsg, ID_TEXT_1, ID_TEXT_2, ID_TEXT_3, ID_TEXT_4,ID_IMAGE_0);
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
        BUTTON_SetPressed(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0),1);
        BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0),BUTTON_CI_PRESSED,GUI_RED);

        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLACK,BUTTON_CI_UNPRESSED,GUI_BLACK,"历史查询");

        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLACK,BUTTON_CI_UNPRESSED,GUI_BLACK,"系统配置");
        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF36_Font,BUTTON_CI_UNPRESSED,GUI_BLACK,BUTTON_CI_UNPRESSED,GUI_BLACK,"退    出");

        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_GREEN,BUTTON_CI_UNPRESSED,GUI_RED,"模拟量");
        BUTTON_SetPressed(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4),1);
        BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4),BUTTON_CI_PRESSED,GUI_RED);

        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_BLACK,BUTTON_CI_UNPRESSED,GUI_BLACK,"状态量");
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
                /**< 跳转到历史记录查询 */
                _deleteWin(_hWinManagerInfoAnalog);
                CreateManagerAlarmLog();
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
            WM_DeleteWindow(pMsg->hWin);
            //PutOut_SelAOrB();
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
            /**< noting */
            break;
        /// TODO (zshare#1#): ///因为鼠标重置的问题, \
          所以需要用到WM_NOTIFICATION_MOVED_OUT事件,不触发WM_NOTIFICATION_RELEASED
          case WM_NOTIFICATION_RELEASED://WM_NOTIFICATION_MOVED_OUT:
            /**< 跳转到状态信息查询 */
            _deleteWin(_hWinManagerInfoAnalog);
            CreateManagerInfoStatus();
            break;
          }
        }
        break;
    case WM_TIMER:
        if(pMsg->Data.v == _timerRTC)
        {
            /**< 显示时间和日期 */
            Caculate_RTC_Show(pMsg, ID_TEXT_1, ID_TEXT_2);
            TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_3), strCSQ);
            /**< 重启定时器 */
            WM_RestartTimer(pMsg->Data.v, 20);
        }
        if(pMsg->Data.v == _timerSignal)
        {
            WM_RestartTimer(pMsg->Data.v, 2000);
        }
        if(pMsg->Data.v == _timerData)
        {
            Data_Flush(pMsg);
            WM_RestartTimer(pMsg->Data.v,5000);
        }
        break;
    case MSG_CREATERRWIN:
        /**< 故障界面不存在则创建,存在则刷新告警 */
        err_window(pMsg->hWin);
        break;
    case MSG_DELERRWIN:
        /**< 故障界面存在则删除故障界面 */
        if(bittest(winCreateFlag,0))
        {
            bitclr(winCreateFlag,0);
            GUI_EndDialog(err_hItem,0);
            err_hItem = 0;
        }
        break;
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
/** @brief
 *  输出管理员界面里的信息查询模拟量部分
 * @param
 * @param
 * @return
 *       CreateManagerInfoAnalog
*/
WM_HWIN CreateManagerInfoAnalog(void);
WM_HWIN CreateManagerInfoAnalog(void)
{
    _hWinManagerInfoAnalog = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    cur_win = _hWinManagerInfoAnalog;
    _timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerTime, 20, 0);
    _timerData = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerFlush,1000,0);
    _timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerSignal,5000,0);
}
/*************************** End of file ****************************/



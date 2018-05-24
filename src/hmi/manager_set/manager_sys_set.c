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
*
*   数据变化刷新;
*   需要刷新更新发送刷新数据消息
*   multi更新数据
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "touchtimer.h"
#include "SCROLLBAR.h"
// USER END

#include "DIALOG.h"
/*******************************************************************
*
*       defines
*
********************************************************************
*/
/*编辑窗口14行1列，状态项14个*/
#define _SYSEDIT_MAX_X 5
#define _SYSEDIT_MAX_Y 20
#define _SYSSTATUE_LINE 20
#define _SYSSTATUE_CAL 5
//后续将编辑和文本的滚轮方式用链表进行封装
#define _FONT_WIDTH 24
#define _WORD_WIDTH 20
static uint8_t _aahSysSet[_SYSEDIT_MAX_Y];
static EDIT_Handle   _aahEdit[_SYSEDIT_MAX_Y][_SYSEDIT_MAX_X];
static TEXT_Handle   _aahText[_SYSSTATUE_LINE][_SYSSTATUE_CAL];
static int _x, _y;
static uint8_t _checkbox;
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_IMAGE_0     (GUI_ID_USER + 0x1C)
// USER START (Optionally insert additional defines)
#define ID_TEXT_1     (GUI_ID_USER + 0x0B)
#define ID_TEXT_2     (GUI_ID_USER + 0x0C)
#define ID_TEXT_3     (GUI_ID_USER + 0x0D)
#define ID_TEXT_4     (GUI_ID_USER + 0x0E)

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
#define ID_MULTIEDIT_0 (GUI_ID_USER + 0x18)
#define ID_CHECKBOX_0 (GUI_ID_USER + 0x19)
#define ID_CHECKBOX_1 (GUI_ID_USER + 0x1A)
#define ID_TimerTime    1
#define ID_TimerFlush   2
#define ID_TimerSignal  3

#define sysEVSESN "交流桩SN"
#define sysEVSEID "交流桩ID"
#define sysServerIP "服务器IP"
#define sysServerPort "服务器端口"
#define sysUserName "用户名"
#define sysUserPwd "用户密码"
#define sysDispSleepTime "屏保时间"
#define sysUSEGPRSModem "GPRS类型"
#define sysPasswd "秘钥"
#define sysManagerPwd "管理员密码"
// USER END
static WM_HWIN hWindow;
WM_HWIN _hWinManagerSysSet;
static WM_HTIMER _timerRTC, _timerData, _timerSignal;
extern uint8_t passwd[16];

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
    { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 10, 95, 780, 370, 0, 0x0, 0 },
//	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_0, GUI_MANAGER_XLEFT + _FONT_WIDTH*(strlen(sysUSEGPRSModem)), GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF*7, 90, 32, 0, 0x0, 0 },
//	{ CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_1, GUI_MANAGER_XLEFT + _FONT_WIDTH*(strlen(sysUSEGPRSModem)) + 90, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF*7, 90, 32, 0, 0x0, 0 },
};
/*******************************************************************
*
*       _cbWindow

  The callback moves the edit-fiels when a notification message
  was send.
*/
static void _cbWindow(WM_MESSAGE *pMsg) {
    WM_SCROLL_STATE ScrollState;
    WM_HWIN      hItem;
    int x, y;
    uint8_t tmpU8 = 0;
    volatile int id = 0;
    volatile int v = 0;
    uint8_t _tmpBuff[50];
    CON_t *pCon;
    pCon = CONGetHandle(0);

    switch (pMsg->MsgId)
    {
    case WM_NOTIFY_PARENT:
        /**< 添加两个滑轮的事件 */
        switch (WM_GetId(pMsg->hWinSrc))
        {
        case GUI_ID_HSCROLL://水平
            if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED)
            {
                /* 得到滚动条的状态，得到的数值好像是负值 才能使得 _x - ScrollState.v是正值 */
                WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
                if (_x != ScrollState.v)
                {
                    for (y = 0; y < _SYSEDIT_MAX_Y; y++)
                    {
                        for (x = 0; x < _SYSEDIT_MAX_X; x++)
                        {
                            WM_MoveWindow(_aahEdit[y][x], _x - ScrollState.v, 0);
                            WM_MoveWindow(_aahText[y][x], _x - ScrollState.v, 0);
                        }
                    }
                    _x = ScrollState.v;
                }
            }
            break;
        case GUI_ID_VSCROLL:
            if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED)
            {
                WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
                if (_y != ScrollState.v)
                {
                    for (y = 0; y < _SYSEDIT_MAX_Y; y++)
                    {
                        for (x = 0; x < _SYSEDIT_MAX_X; x++)
                        {
                            WM_MoveWindow(_aahEdit[y][x], 0, _y - ScrollState.v);
                            WM_MoveWindow(_aahText[y][x], 0, _y - ScrollState.v);
                        }
                    }
                    _y = ScrollState.v;
                }
            }
            break;
        case 20:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 20, _hWinManagerSysSet, _hWinManagerCommon, sysEVSESN, "eg,1122334455667788");
                //Keypad_GetValue(SYSSET_VALUE,"交流桩序列号");
                //                    EDIT_SetText(_aahEdit[0][0], pEVSE->info.strSN);
            }
            break;
        case 21:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 21, _hWinManagerSysSet, _hWinManagerCommon, sysEVSEID, "eg,1122334455667788");
                //                    memset(_tmpBuff, '\0', sizeof(_tmpBuff));
                //                    sprintf(_tmpBuff, "%d", pEVSE->info.strID);
                //                    EDIT_SetText(_aahEdit[1][0], _tmpBuff);
            }
            break;
        case 22:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 22, _hWinManagerSysSet, _hWinManagerCommon, sysServerIP, "eg,192.168.1.101");
                //                    memset(_tmpBuff, '\0', sizeof(_tmpBuff));
                //                    sprintf(_tmpBuff, "%d", pechProto->info.strServerIP);
                //                    EDIT_SetText(_aahEdit[2][0], _tmpBuff);
            }
            break;
        case 23:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 23, _hWinManagerSysSet, _hWinManagerCommon, sysServerPort, "note:1~9999");
                //                    memset(_tmpBuff, '\0', sizeof(_tmpBuff));
                //                    sprintf(_tmpBuff, "%.1f", pechProto->info.usServerPort);
                //                    EDIT_SetText(_aahEdit[3][0], _tmpBuff);
            }
            break;
        case 24:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 24, _hWinManagerSysSet, _hWinManagerCommon, sysUserName, "eg,dpc");
                //                    EDIT_SetText(_aahEdit[4][0], pechProto->info.strUserName);
            }
            break;
        case 25:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 25, _hWinManagerSysSet, _hWinManagerCommon, sysUserPwd, "eg,8888");
                //                    EDIT_SetText(_aahEdit[5][0], "******");
            }
            break;
        case 26:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 26, _hWinManagerSysSet, _hWinManagerCommon, sysDispSleepTime, "note：5~60");
                //                    memset(_tmpBuff, '\0', sizeof(_tmpBuff));
                //                    sprintf(_tmpBuff, "%d", xSysconf.ulDispSleepTime_s);
                //                    EDIT_SetText(_aahEdit[4][0], _tmpBuff);
            }
            break;
        case 27:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 27, _hWinManagerSysSet, _hWinManagerCommon, sysDispSleepTime, "1:以太网,2:GPRS");
                //                    memset(_tmpBuff, '\0', sizeof(_tmpBuff));
                //                    sprintf(_tmpBuff, "%d", xSysconf.ulDispSleepTime_s);
                //                    EDIT_SetText(_aahEdit[4][0], _tmpBuff);
            }
            break;
        case 28:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);

                Keypad_GetValueTest(SYSSET_VALUE, 28, _hWinManagerSysSet, _hWinManagerCommon, sysPasswd, "eg,8888");
            }
            break;
        case 29:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 29, _hWinManagerSysSet, _hWinManagerCommon, sysManagerPwd, "eg,8888");
            }
            break;
        case 30:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 30, _hWinManagerSysSet, _hWinManagerCommon, "枪数", "1,2");
            }
            break;
        case 31:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 31, _hWinManagerSysSet, _hWinManagerCommon, "主机名", "");
            }
            break;
        case 32:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 32, _hWinManagerSysSet, _hWinManagerCommon, "MAC", "");
            }
            break;
        case 33:
           // if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                if (CHECKBOX_GetState(_aahEdit[13][0]) == 1)
                {
                    tmpU8 = 1;
                    cfg_set_uint8(pathNetCfg, &tmpU8, "%s", jnNetDHCP);
                    for (y = 14; y < _SYSEDIT_MAX_Y; y++)
                    {
                        for (x = 0; x < _SYSEDIT_MAX_X; x++)
                        {
                            WM_HideWindow(_aahEdit[y][x]);
                            WM_HideWindow(_aahText[y][x]);
                        }
                    }
                }
                else
                {
                    tmpU8 = 0;
                    cfg_set_uint8(pathNetCfg, &tmpU8, "%s", jnNetDHCP);
                    for (y = 14; y < _SYSEDIT_MAX_Y; y++)
                    {
                        for (x = 0; x < _SYSEDIT_MAX_X; x++)
                        {
                            WM_ShowWindow(_aahEdit[y][x]);
                            WM_ShowWindow(_aahText[y][x]);
                        }
                    }
                }
//                WM_HideWindow(_hWinManagerSysSet);
//                WM_HideWindow(_hWinManagerCommon);
//                Keypad_GetValueTest(SYSSET_VALUE, 33, _hWinManagerSysSet, _hWinManagerCommon, "", "");
            }
            break;
        case 34:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 34, _hWinManagerSysSet, _hWinManagerCommon, "本机ip", "");
            }
            break;
        case 35:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 35, _hWinManagerSysSet, _hWinManagerCommon, "子网掩码", "255.255.255.0");
            }
            break;
        case 36:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 36, _hWinManagerSysSet, _hWinManagerCommon, "网关", "192.168.1.1");
            }
            break;
        case 37:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 37, _hWinManagerSysSet, _hWinManagerCommon, "DNS1", "114.215.126.16");
            }
            break;
        case 38:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
            {
                WM_HideWindow(_hWinManagerSysSet);
                WM_HideWindow(_hWinManagerCommon);
                Keypad_GetValueTest(SYSSET_VALUE, 38, _hWinManagerSysSet, _hWinManagerCommon, "DNS2", "112.124.47.27");
            }
            break;
        }
        break;
    case WM_PAINT:
        /**< 绘制滑轮围绕区颜色 */
        GUI_SetBkColor(GUI_WHITE);
        GUI_Clear();
        break;
    case MSG_MANAGERSETID0:
        EDIT_SetText(_aahEdit[0][0], pEVSE->info.strSN);
        break;
    case MSG_MANAGERSETID1:
        EDIT_SetText(_aahEdit[1][0], pEVSE->info.strID);
        break;
    case MSG_MANAGERSETID2:
        EDIT_SetText(_aahEdit[2][0], pechProto->info.strServerIP);
        break;
    case MSG_MANAGERSETID3:
        sprintf(_tmpBuff, "%d", pechProto->info.usServerPort);
        EDIT_SetText(_aahEdit[3][0], _tmpBuff);
        break;
    case MSG_MANAGERSETID4:
        EDIT_SetText(_aahEdit[4][0], pechProto->info.strUserName);
        break;
    case MSG_MANAGERSETID5:
        EDIT_SetText(_aahEdit[5][0], "******");
        break;
    case MSG_MANAGERSETID6:
        sprintf(_tmpBuff, "%d", xSysconf.ulDispSleepTime_s / 60);
        EDIT_SetText(_aahEdit[6][0], _tmpBuff);
        break;
    case MSG_MANAGERSETID7:
        if (ifconfig.info.ucAdapterSel == 1)
        {
            EDIT_SetText(_aahEdit[7][0], "以太网");
        }
        else
        {
            EDIT_SetText(_aahEdit[7][0], "GPRS");
        }
        break;
    case MSG_MANAGERSETID8:
        EDIT_SetText(_aahEdit[8][0], "******");
        break;
    case MSG_MANAGERSETID9:
        
        break;    
    case MSG_MANAGERSETIDA:
        sprintf(_tmpBuff, "%d", (int)pEVSE->info.ucTotalCON);
        EDIT_SetText(_aahEdit[10][0], _tmpBuff);
        break;   
    case MSG_MANAGERSETIDB://31
        sprintf(_tmpBuff, "%s", ifconfig.info.strHostName);
        EDIT_SetText(_aahEdit[11][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETIDC://32
        sprintf(_tmpBuff, "%s", ifconfig.info.strMAC);
        EDIT_SetText(_aahEdit[12][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETIDD://33

        break;  
    case MSG_MANAGERSETIDE://34
        sprintf(_tmpBuff, "%s", ifconfig.info.strIP);
        EDIT_SetText(_aahEdit[14][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETIDF://35
        sprintf(_tmpBuff, "%s", ifconfig.info.strMask);
        EDIT_SetText(_aahEdit[15][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETID10://36
        sprintf(_tmpBuff, "%s", ifconfig.info.strGate);
        EDIT_SetText(_aahEdit[16][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETID11://37
        sprintf(_tmpBuff, "%s", ifconfig.info.strDNS1);
        EDIT_SetText(_aahEdit[17][0], _tmpBuff);
        break;  
    case MSG_MANAGERSETID12://38
        sprintf(_tmpBuff, "%s", ifconfig.info.strDNS2);
        EDIT_SetText(_aahEdit[18][0], _tmpBuff);
        break;  
    default:
        WM_DefaultProc(pMsg);
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
    int          Id;
    int x, y, Index, _editxoff = 0;
    SCROLLBAR_Handle hScroll;
    SCROLLBAR_Handle wScroll;
    char _tmpBuff[50];
    CON_t *pCon;

    pCon = CONGetHandle(0);
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_PAINT:
//        //LCD_SetCursor(0,200);
//        WM_SetFocus(pMsg->hWin);
//        /// TODO (zshare#1#): 下面的if不起作用.\
//        但是if里嵌套的if起作用,目前先用此来规避不起作用的if
//        if(_hWinManagerSysSet == cur_win)
//        {
//            /**< 数据处理 */
//            //Data_Process(pMsg);
//            /**< 信号数据处理 */
//            Signal_Show();
//            /**< 灯光控制 */
//            Led_Show();
//            /**< 如果界面发生了切换 */
//            if(_hWinManagerSysSet == cur_win)
//            {
//                /**< 故障分析 */
//                /// TODO (zshare#1#): 滑轮页均不对故障处理.故障界面被滑轮页覆盖
//                //Err_Analy(pMsg->hWin);
//                /**< 特殊触控点分析 */
//                CaliDone_Analy(pMsg->hWin);
//            }
//        }
        break;
    case WM_INIT_DIALOG:
        _x = 0;
        _y = 0;
        // 创建窗口250
        hWindow = pMsg->hWin;//WM_CreateWindow(230, 70, 520, 350, WM_CF_SHOW, &_cbWindow, 0);
        WM_SetCallback(pMsg->hWin, &_cbWindow);
        //创建水平滑轮
//        hScroll = SCROLLBAR_CreateAttached(pMsg->hWin, 0);//水平滑轮
//        //设置滑轮条目数量
//        SCROLLBAR_SetNumItems(hScroll, _SYSEDIT_MAX_X);
//        //设置页尺寸
//        //SCROLLBAR_SetPageSize(hScroll, 220);
//        SCROLLBAR_SetWidth(hScroll,20);
        //创建垂直滑轮
        wScroll = SCROLLBAR_CreateAttached(hWindow, SCROLLBAR_CF_VERTICAL);//垂直滑轮
        //设置滑轮条目数量
        SCROLLBAR_SetPageSize(wScroll, 130);
        SCROLLBAR_SetNumItems(wScroll, 6 * 130);
        //设置页尺寸
        //SCROLLBAR_SetPageSize(wScroll, 220);
        SCROLLBAR_SetWidth(wScroll, WSCROLL_WIDTH);

        //创建文本区 -- 24号字体 4-96 5-120 6-144 7-168 8-192
        /**< 13文本固定id */
        //创建编辑区
        /**< 20-50编辑区ID */
        _editxoff = GUI_MANAGER_XLEFT + _FONT_WIDTH*(strlen(sysServerPort)) / 3;
        xSysconf.GetSysCfg((void *)&xSysconf, NULL);
        _aahText[0][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT, _FONT_WIDTH*(strlen(sysEVSESN)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysEVSESN);
        _aahEdit[0][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT, _WORD_WIDTH*(strlen("1122334455667788")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 20, strlen("1122334455667788"));
        EDIT_SetText(_aahEdit[0][0], pEVSE->info.strSN);

        _aahText[1][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF, _FONT_WIDTH*(strlen(sysEVSEID)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysEVSEID);
        _aahEdit[1][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF, _WORD_WIDTH*(strlen("1122334455667788")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 21, strlen("1122334455667788"));
        EDIT_SetText(_aahEdit[1][0], pEVSE->info.strID);

        _aahText[2][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 2, _FONT_WIDTH*(strlen(sysServerIP)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysServerIP);
        _aahEdit[2][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 2, _WORD_WIDTH*(strlen("255.255.255.255")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 22, strlen("255.255.255.255"));
//        memset(_tmpBuff,'\0',strlen(_tmpBuff));
//        sprintf(_tmpBuff,"%d",pechProto->info.strServerIP);
        EDIT_SetText(_aahEdit[2][0], pechProto->info.strServerIP);

        _aahText[3][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 3, _FONT_WIDTH*(strlen(sysServerPort)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysServerPort);
        _aahEdit[3][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 3, _WORD_WIDTH*strlen("8080"), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 23, strlen("8080"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%d", pechProto->info.usServerPort);
        EDIT_SetText(_aahEdit[3][0], _tmpBuff);

        _aahText[4][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 4, _FONT_WIDTH*(strlen(sysUserName)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysUserName);
        _aahEdit[4][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 4, _WORD_WIDTH*strlen("woshinidaye"), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 24, strlen("woshinidaye"));
        EDIT_SetText(_aahEdit[4][0], pechProto->info.strUserName);

        _aahText[5][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 5, _FONT_WIDTH*(strlen(sysUserPwd)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysUserPwd);
        _aahEdit[5][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 5, _WORD_WIDTH*strlen(pechProto->info.strUserPwd), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 25, strlen(pechProto->info.strUserPwd));
        if (managerLevel == 0)
        {
            EDIT_SetText(_aahEdit[5][0], pechProto->info.strUserPwd);
        }
        else
        {
            EDIT_SetText(_aahEdit[5][0], "******");            
        }

        _aahText[6][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 6, _FONT_WIDTH*(strlen(sysDispSleepTime)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysDispSleepTime);
        _aahEdit[6][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 6, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 26, strlen("100"));
        _aahText[6][1] = TEXT_CreateEx(_editxoff + _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 6, _FONT_WIDTH*(strlen("分")), 25, hWindow, WM_CF_SHOW, 0, 13, "分");
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%d", xSysconf.ulDispSleepTime_s / 60);
        EDIT_SetText(_aahEdit[6][0], _tmpBuff);
        //GPRS模块选择 暂时不能设置 需要将设置项进行两种分类，一种模拟量 一种状态量
        _aahText[7][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 7, _FONT_WIDTH*(strlen("网络类型")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "网络类型");
        _aahEdit[7][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 7, _WORD_WIDTH*(strlen("网络类型")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 27, strlen("网络类型"));
        if (ifconfig.info.ucAdapterSel == 1)
        {
            EDIT_SetText(_aahEdit[7][0], "以太网");
        }
        else
        {
            EDIT_SetText(_aahEdit[7][0], "GPRS");
        }

        //秘钥
        _aahText[8][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 8, _FONT_WIDTH*(strlen(sysPasswd)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysPasswd);
        _aahEdit[8][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 8, _WORD_WIDTH*strlen(pechProto->info.strKey), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 28, strlen(pechProto->info.strKey));
        if (managerLevel == 0)
        {
            EDIT_SetText(_aahEdit[8][0], pechProto->info.strKey);                        
        }
        else
        {
            EDIT_SetText(_aahEdit[8][0], "******");            
        }
        //管理员密码
        _aahText[9][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 9, _FONT_WIDTH*(strlen(sysManagerPwd)), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, sysManagerPwd);
        _aahEdit[9][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 9, _WORD_WIDTH*strlen(passwd), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 29, strlen(passwd));
        if (managerLevel == 0)
        {
            EDIT_SetText(_aahEdit[9][0], passwd);
        }
        else
        {
            EDIT_SetText(_aahEdit[9][0], "******");            
        }
        //枪数
        _aahText[10][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 10, _FONT_WIDTH*(strlen("枪数")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "枪数");
        _aahEdit[10][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 10, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 30, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%d", (int)pEVSE->info.ucTotalCON);
        EDIT_SetText(_aahEdit[10][0], _tmpBuff);
        //主机名
        _aahText[11][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 11, _FONT_WIDTH*(strlen("主机名")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "主机名");
        _aahEdit[11][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 11, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 31, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strHostName);
        EDIT_SetText(_aahEdit[11][0], _tmpBuff);
        //mac
        _aahText[12][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 12, _FONT_WIDTH*(strlen("MAC")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "MAC");
        _aahEdit[12][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 12, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 32, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strMAC);
        EDIT_SetText(_aahEdit[12][0], _tmpBuff);
        //DHCP
        _aahText[13][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 13, _FONT_WIDTH*(strlen("DHCP")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "DHCP");
        _aahEdit[13][0] = CHECKBOX_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 13, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 33);
        if (ifconfig.info.ucDHCPEnable == 1)
        {
            CHECKBOX_SetState(_aahEdit[13][0], 1);
        }
        else
        {
            CHECKBOX_SetState(_aahEdit[13][0], 0);
        }
        //本机ip
        _aahText[14][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 14, _FONT_WIDTH*(strlen("本机ip")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "本机ip");
        _aahEdit[14][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 14, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 34, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strIP);
        EDIT_SetText(_aahEdit[14][0], _tmpBuff);
        //子网掩码
        _aahText[15][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 15, _FONT_WIDTH*(strlen("子网掩码")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "子网掩码");
        _aahEdit[15][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 15, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 35, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strMask);
        EDIT_SetText(_aahEdit[15][0], _tmpBuff);
        
        _aahText[16][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 16, _FONT_WIDTH*(strlen("网关")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "网关");
        _aahEdit[16][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 16, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 36, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strGate);
        EDIT_SetText(_aahEdit[16][0], _tmpBuff);
        
        _aahText[17][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 17, _FONT_WIDTH*(strlen("DNS1")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "DNS1");
        _aahEdit[17][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 17, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 37, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strDNS1);
        EDIT_SetText(_aahEdit[17][0], _tmpBuff);

        _aahText[18][0] = TEXT_CreateEx(GUI_MANAGER_XLEFT, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 18, _FONT_WIDTH*(strlen("DNS1")), GUI_MANAGER_YOFF, hWindow, WM_CF_SHOW, 0, 13, "DNS1");
        _aahEdit[18][0] = EDIT_CreateEx(_editxoff, GUI_MANAGER_YLEFT + GUI_MANAGER_YOFF * 18, _WORD_WIDTH*(strlen("100")), GUI_MANAGER_YSIZE, hWindow, WM_CF_SHOW, 0, 38, strlen("100"));
        memset(_tmpBuff, '\0', strlen(_tmpBuff));
        sprintf(_tmpBuff, "%s", ifconfig.info.strDNS2);
        EDIT_SetText(_aahEdit[18][0], _tmpBuff);

        if (CHECKBOX_GetState(_aahEdit[13][0]) == 1)
        {
            for (y = 14; y < _SYSEDIT_MAX_Y; y++)
            {
                for (x = 0; x < _SYSEDIT_MAX_X; x++)
                {
                    WM_HideWindow(_aahEdit[y][x]);
                    WM_HideWindow(_aahText[y][x]);
                }
            }
        }
        else
        {
            for (y = 14; y < _SYSEDIT_MAX_Y; y++)
            {
                for (x = 0; x < _SYSEDIT_MAX_X; x++)
                {
                    WM_ShowWindow(_aahEdit[y][x]);
                    WM_ShowWindow(_aahText[y][x]);
                }
            }
        }
        for (x = 0; x < _SYSSTATUE_LINE; x++)
        {
            for (y = 0; y < _SYSSTATUE_CAL; y++)
            {
                TEXT_SetFont(_aahText[x][y], &SIF24_Font);
                TEXT_SetTextColor(_aahText[x][y], GUI_BLACK);
            }
        }

        for (y = 0; y < _SYSEDIT_MAX_Y; y++)
        {
            for (x = 0; x < _SYSEDIT_MAX_X; x++)
            {
                EDIT_SetTextAlign(_aahEdit[y][x], GUI_TA_HCENTER | GUI_TA_VCENTER);
                EDIT_SetFont(_aahEdit[y][x], &SIF24_Font);
                WIDGET_SetEffect(_aahEdit[y][x], &WIDGET_Effect_3D);//不需要设置的就改成 &WIDGET_Effect_None模式
            }
        }

        WM_SetStayOnTop(hWindow, 1);
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;

        switch (Id) {
        case ID_CHECKBOX_0:
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
                Index = CHECKBOX_GetState(hItem);
                if ((Index == 1)&&(!bittest(_checkbox, 0)))
                {
                    bitset(_checkbox, 0);
                    bitclr(_checkbox, 1);
                    Index = 0;
                    xSysconf.SetSysCfg(jnSysUSE_GPRSModem, (void *)&Index, ParamTypeU8);
                }
                break;
            case WM_NOTIFICATION_RELEASED:
                break;
            case WM_NOTIFICATION_VALUE_CHANGED:
                break;
            }
            break;

        case ID_CHECKBOX_1:
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
                Index = CHECKBOX_GetState(hItem);
                if ((Index == 1)&&(!bittest(_checkbox, 1)))
                {
                    bitset(_checkbox, 1);
                    bitclr(_checkbox, 0);
                    Index = 1;
                    xSysconf.SetSysCfg(jnSysUSE_GPRSModem, (void *)&Index, ParamTypeU8);
                }
                break;

            case WM_NOTIFICATION_RELEASED:
                break;

            case WM_NOTIFICATION_VALUE_CHANGED:
                break;

            }
            break;
        }
        break;
        // USER START (Optionally insert additional message handling)
//    case WM_TIMER:
//        if(pMsg->Data.v == _timerRTC)
//        {
//            /**< 显示时间和日期 */
//            Caculate_RTC_Show(pMsg, ID_TEXT_1, ID_TEXT_2);
//            TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_3), strCSQ);
//            /**< 重启定时器 */
//            WM_RestartTimer(pMsg->Data.v, 20);
//        }
//        if(pMsg->Data.v == _timerSignal)
//        {
//            WM_RestartTimer(pMsg->Data.v, 2000);
//        }
//        if(pMsg->Data.v == _timerData)
//        {
//            //Data_Flush(pMsg);
//            //Status_Content_Analy();
//            WM_RestartTimer(pMsg->Data.v,3000);
//        }
//        break;
//    case MSG_CREATERRWIN:
//        /**< 故障界面不存在则创建,存在则刷新告警 */
//        err_window(pMsg->hWin);
//        break;
//    case MSG_DELERRWIN:
//        /**< 故障界面存在则删除故障界面 */
//        if(bittest(winCreateFlag,0))
//        {
//            bitclr(winCreateFlag,0);
//            GUI_EndDialog(err_hItem,0);
//            err_hItem = 0;
//        }
//        break;
    case MSG_DELETEMANAGERWIN:
        GUI_EndDialog(_hWinManagerSysSet, 0);
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
/** @brief
 *  输出管理员界面里的系统配置
 * @param
 * @param
 * @return
 *
 *
 *       CreateManagerSysSet
*/
WM_HWIN CreateManagerSysSet(WM_HWIN srcHwin)
{
    _hWinManagerSysSet = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_GetClientWindow(srcHwin), 0, 0);
//    cur_win = _hWinManagerSysSet;
//    _timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinManagerSysSet), ID_TimerTime, 20, 0);
//    _timerData = WM_CreateTimer(WM_GetClientWindow(_hWinManagerSysSet), ID_TimerFlush,1000,0);
//    _timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinManagerSysSet), ID_TimerSignal,5000,0);
    return _hWinManagerSysSet;
}
/*************************** End of file ****************************/





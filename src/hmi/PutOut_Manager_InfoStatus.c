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
#include "xbffontcreate.h"
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
#define EDIT_MAX_X 1
#define EDIT_MAX_Y 14
#define STATUE_LINE 14
#define STATUE_CAL 1
//后续将编辑和文本的滚轮方式用链表进行封装
static uint8_t _aahStatus[EDIT_MAX_Y];
static EDIT_Handle   _aahEdit[EDIT_MAX_Y][EDIT_MAX_X];
static TEXT_Handle   _aahText[STATUE_LINE][STATUE_CAL];
static int _x,_y;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_IMAGE_0     (GUI_ID_USER + 0x1C)
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
#define ID_MULTIEDIT_0 (GUI_ID_USER + 0x18)

#define ID_TimerTime    1
#define ID_TimerFlush   2
#define ID_TimerSignal  3
// USER END
static WM_HWIN hWindow;
static WM_HWIN _hWinManagerInfoStatus;
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
    // USER START (Optionally insert additional widgets)
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
//    { TEXT_CreateIndirect, "交流电压:", ID_TEXT_5, 300, 100, 150, 30, 0, 0x0, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 477, 100, 100, 30, 0, 0x64, 0 },
//    { TEXT_CreateIndirect, "交流电流:", ID_TEXT_6, 300, 140, 150, 30, 0, 0x0, 0 },
//    { TEXT_CreateIndirect, "充电导引电压:", ID_TEXT_7, 300, 178, 160, 30, 0, 0x0, 0 },
//    { TEXT_CreateIndirect, "频    率:", ID_TEXT_8, 300, 216, 150, 30, 0, 0x0, 0 },
//    { TEXT_CreateIndirect, "A插座温度:", ID_TEXT_9, 300, 256, 150, 30, 0, 0x0, 0 },
//    { TEXT_CreateIndirect, "B插座温度:", ID_TEXT_10, 300, 296, 150, 30, 0, 0x0, 0 },
//    { TEXT_CreateIndirect, "接线温度:", ID_TEXT_11, 300, 336, 150, 30, 0, 0x0, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 477, 140, 100, 30, 0, 0x64, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 477, 178, 100, 30, 0, 0x64, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 477, 216, 100, 30, 0, 0x64, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 477, 256, 100, 30, 0, 0x64, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_5, 477, 296, 100, 30, 0, 0x64, 0 },
//    { EDIT_CreateIndirect, "Edit", ID_EDIT_6, 477, 336, 100, 30, 0, 0x64, 0 },
//      { MULTIEDIT_CreateIndirect, "Multiedit", ID_MULTIEDIT_0, 235, 90, 200, 120, 0, 0x0, 0 },
    // USER END
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
    char *dest = (char *)malloc(10);
    int x, y;
    volatile int id = 0;

    switch (pMsg->MsgId)
    {
        case WM_NOTIFY_PARENT:
            if(pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED)
            {
                id = WM_GetId(pMsg->hWinSrc);
                if(WM_GetId(pMsg->hWinSrc) == GUI_ID_HSCROLL)
                {
                    /* 得到滚动条的状态，得到的数值好像是负值 才能使得 _x - ScrollState.v是正值 */
                    WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
                    if (_x != ScrollState.v)
                    {
                        for (y = 0; y < EDIT_MAX_Y; y++)
                        {
                            for (x = 0; x < EDIT_MAX_X; x++)
                            {
                                WM_MoveWindow(_aahEdit[y][x], _x - ScrollState.v, 0);
                                WM_MoveWindow(_aahText[y][x], _x - ScrollState.v, 0);
                            }
                        }
                        _x = ScrollState.v;
                    }
                }
                else if(WM_GetId(pMsg->hWinSrc) == GUI_ID_VSCROLL)
                {
                    WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
                    if (_y != ScrollState.v)
                    {
                        for (y = 0; y < EDIT_MAX_Y; y++)
                        {
                            for (x = 0; x < EDIT_MAX_X; x++)
                            {
                                WM_MoveWindow(_aahEdit[y][x],0, _y - ScrollState.v);
                                WM_MoveWindow(_aahText[y][x],0, _y - ScrollState.v);
                            }
                        }
                        _y = ScrollState.v;
                    }
                }
            }
            break;
        case WM_PAINT:
            /**< 绘制滑轮围绕区颜色 */
            GUI_SetBkColor(GUI_WHITE);
            GUI_Clear();
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}
/** @brief 状态内容编辑分析
 *
 * @param
 * @param
 * @return
 *
 */
static void Status_Content_Analy()
{
	CON_t	*pcont;
	pcont = CONGetHandle(0);
	
    /**< 工作状态 */
	if ((pcont->status.ulSignalState & defSignalCON_State_Working) == defSignalCON_State_Working)
	{
		EDIT_SetText(_aahEdit[0][0], "充电中");
	}
	else if ((pcont->status.ulSignalState & defSignalCON_State_Standby) == defSignalCON_State_Standby)
	{
		EDIT_SetText(_aahEdit[0][0], "空闲");
	}
	else if((pcont->status.ulSignalState & defSignalCON_State_Fault) == defSignalCON_State_Fault)
	{
		EDIT_SetText(_aahEdit[0][0], "故障");
	}

	/**< 急停状态 */
	if ((pEVSE->status.ulSignalAlarm & defSignalEVSE_Alarm_Scram) == defSignalEVSE_Alarm_Scram)
	{
		EDIT_SetText(_aahEdit[1][0], "按下");		
	}
	else
	{
		EDIT_SetText(_aahEdit[1][0], "正常");
	}

	/**< 电表通信 */
	if ((pcont->status.ulSignalFault & defSignalCON_Fault_Meter) == defSignalCON_Fault_Meter)
	{
		EDIT_SetText(_aahEdit[2][0], "故障");
	}
	else
	{
		EDIT_SetText(_aahEdit[2][0], "正常");
	}
	
    /**< A插座温度1 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_SocketTemp1_Cri) == defSignalCON_Alarm_SocketTemp1_Cri)
	{
		EDIT_SetText(_aahEdit[3][0], "过温");
	}
	else 
	{
		EDIT_SetText(_aahEdit[3][0], "正常");		
	}
	
    /**< A插座温度2 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_SocketTemp2_Cri) == defSignalCON_Alarm_SocketTemp2_Cri)
	{
		EDIT_SetText(_aahEdit[4][0], "过温");
	}
	else 
	{
		EDIT_SetText(_aahEdit[4][0], "正常");		
	}
	
    /**< A枪输出电流 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_AC_A_CurrUp_Cri) == defSignalCON_Alarm_AC_A_CurrUp_Cri)
	{
		EDIT_SetText(_aahEdit[5][0],"过流");
	}
	else
	{
		EDIT_SetText(_aahEdit[5][0], "正常");
	}

	/**< RFID */
	if ((pEVSE->status.ulSignalFault & defSignalEVSE_Fault_RFID) == defSignalEVSE_Fault_RFID)
	{
		EDIT_SetText(_aahEdit[6][0], "故障");
	}
	else
	{
		EDIT_SetText(_aahEdit[6][0], "正常");
	}    
	
	/**< A枪枪锁 */
	if ((pcont->status.ulSignalState & defSignalCON_State_SocketLock) == defSignalCON_State_SocketLock)
	{
		EDIT_SetText(_aahEdit[7][0], "锁止");	
	}
	else
	{
        EDIT_SetText(_aahEdit[7][0],"解锁");	
	}
	
    /**< 枪N温度 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_AC_N_Temp_Cri) == defSignalCON_Alarm_AC_N_Temp_Cri)
	{
		EDIT_SetText(_aahEdit[8][0], "过温");
	}
	else 
	{
		EDIT_SetText(_aahEdit[8][0], "正常");		
	}

	/**< 交流电压 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_AC_A_VoltUp) == defSignalCON_Alarm_AC_A_VoltUp)
	{
		EDIT_SetText(_aahEdit[9][0],"过压");
	}
	else if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_AC_A_VoltLow) == defSignalCON_Alarm_AC_A_VoltLow)
	{
		EDIT_SetText(_aahEdit[9][0],"欠压");	
	}
	else
	{
		EDIT_SetText(_aahEdit[9][0], "正常");		
	}

	/**< 频率 */
	if ((pcont->status.ulSignalAlarm & defSignalCON_Alarm_AC_A_Freq_Cri) == defSignalCON_Alarm_AC_A_Freq_Cri)
	{
		EDIT_SetText(_aahEdit[10][0], "异常");
	}
	else
	{
		EDIT_SetText(_aahEdit[10][0], "正常");
	}
	
    /**< 防雷器状态 */
	if ((pEVSE->status.ulSignalAlarm & defSignalEVSE_Alarm_Arrester) == defSignalEVSE_Alarm_Arrester)
	{
		EDIT_SetText(_aahEdit[11][0], "故障");		
	}
	else
	{
		EDIT_SetText(_aahEdit[11][0], "正常");
	}

	/**< 输出继电器状态 */
	if ((pcont->status.ulSignalState & defSignalCON_State_AC_A_Relay) == defSignalCON_State_AC_A_Relay)
	{
		EDIT_SetText(_aahEdit[12][0], "故障");		
	}
	else
	{
		EDIT_SetText(_aahEdit[12][0], "正常");
	}

	/**< 控制导引状态 */
	if ((pcont->status.ulSignalFault & defSignalCON_Fault_CP) == defSignalCON_Fault_CP)
	{
		EDIT_SetText(_aahEdit[13][0], "故障");		
	}
	else
	{
		EDIT_SetText(_aahEdit[13][0], "正常");
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
    int x, y;
    SCROLLBAR_Handle hScroll;
    SCROLLBAR_Handle wScroll;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_PAINT:
        //LCD_SetCursor(0,200);
        WM_SetFocus(pMsg->hWin);
        /// TODO (zshare#1#): 下面的if不起作用.\
        但是if里嵌套的if起作用,目前先用此来规避不起作用的if
        if(_hWinManagerInfoStatus == cur_win)
        {
            /**< 数据处理 */
            //Data_Process(pMsg);
            /**< 信号数据处理 */
            Signal_Show();
            /**< 灯光控制 */
            Led_Show();
            /**< 如果界面发生了切换 */
            if(_hWinManagerInfoStatus == cur_win)
            {
                /**< 故障分析 */
                /// TODO (zshare#1#): 滑轮页均不对故障处理.故障界面被滑轮页覆盖
                //Err_Analy(pMsg->hWin);
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

        // 创建窗口250
        hWindow = WM_CreateWindow(230, 130, 496, 270, WM_CF_SHOW, &_cbWindow, 0);
        //创建水平滑轮
        hScroll = SCROLLBAR_CreateAttached(hWindow, 0);//水平滑轮
        //设置滑轮条目数量
        SCROLLBAR_SetNumItems(hScroll, 30 * EDIT_MAX_X);
        //设置页尺寸
        //SCROLLBAR_SetPageSize(hScroll, 220);
        SCROLLBAR_SetWidth(hScroll,20);
        //创建垂直滑轮
        wScroll = SCROLLBAR_CreateAttached(hWindow, SCROLLBAR_CF_VERTICAL);//垂直滑轮
        //设置滑轮条目数量
        SCROLLBAR_SetNumItems(wScroll, 30 * EDIT_MAX_Y);
        //设置页尺寸
        //SCROLLBAR_SetPageSize(wScroll, 220);
        SCROLLBAR_SetWidth(wScroll,20);

        //创建文本区 -- 24号字体 4-96 5-120 6-144 7-168 8-192
        _aahText[0][0] = TEXT_CreateEx(30, 20, 120, 25,hWindow,WM_CF_SHOW,0,13,"工作状态:");
        _aahText[1][0] = TEXT_CreateEx(30, 50, 120, 25,hWindow,WM_CF_SHOW,0,13,"急停状态:");
        _aahText[2][0] = TEXT_CreateEx(30, 80, 120, 25,hWindow,WM_CF_SHOW,0,13,"电表状态:");
        _aahText[3][0] = TEXT_CreateEx(30, 110, 144, 25,hWindow,WM_CF_SHOW,0,13,"插座温度1:");
        _aahText[4][0] = TEXT_CreateEx(30, 140, 144, 25,hWindow,WM_CF_SHOW,0,13,"插座温度2:");
        _aahText[5][0] = TEXT_CreateEx(30, 170, 168, 25,hWindow,WM_CF_SHOW,0,13,"输出电流:");
        _aahText[6][0] = TEXT_CreateEx(30, 200, 168, 25,hWindow,WM_CF_SHOW,0,13,"RFID状态:");
        _aahText[7][0] = TEXT_CreateEx(30, 230, 120, 25,hWindow,WM_CF_SHOW,0,13,"枪锁:");
        _aahText[8][0] = TEXT_CreateEx(30, 260, 120, 25,hWindow,WM_CF_SHOW,0,13,"零线温度:");
        _aahText[9][0] = TEXT_CreateEx(30, 290, 120, 25,hWindow,WM_CF_SHOW,0,13,"交流电压:");
        _aahText[10][0] = TEXT_CreateEx(30, 320, 120, 25,hWindow,WM_CF_SHOW,0,13,"交流频率:");
        _aahText[11][0] = TEXT_CreateEx(30, 350, 144, 25,hWindow,WM_CF_SHOW,0,13,"防雷器状态:");
        _aahText[12][0] = TEXT_CreateEx(30, 380, 144, 25,hWindow,WM_CF_SHOW,0,13,"输出继电器:");
        _aahText[13][0] = TEXT_CreateEx(30, 410, 120, 25,hWindow,WM_CF_SHOW,0,13,"控制导引:");

        for(x = 0;x < STATUE_LINE;x++)
        {
            TEXT_SetFont(_aahText[x][0], &XBF19_Font);
            TEXT_SetTextColor(_aahText[x][0], GUI_BLACK);
        }

        //创建编辑区
        _aahEdit[0][0] = EDIT_CreateEx(150, 20, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[1][0] = EDIT_CreateEx(150, 50, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[2][0] = EDIT_CreateEx(150,80, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[3][0] = EDIT_CreateEx(150, 110, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[4][0] = EDIT_CreateEx(150, 140, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[5][0] = EDIT_CreateEx(150, 170, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[6][0] = EDIT_CreateEx(150, 200, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[7][0] = EDIT_CreateEx(150,230, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[8][0] = EDIT_CreateEx(150,260, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[9][0] = EDIT_CreateEx(150, 290, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[10][0] = EDIT_CreateEx(150,320, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[11][0] = EDIT_CreateEx(150,350, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[12][0] = EDIT_CreateEx(150, 380, 96, 25,hWindow,WM_CF_SHOW,0,13,5);
        _aahEdit[13][0] = EDIT_CreateEx(150,410, 96, 25,hWindow,WM_CF_SHOW,0,13,5);

        for (y = 0; y < EDIT_MAX_Y; y++)
        {
            for (x = 0; x < EDIT_MAX_X; x++)
            {
                EDIT_SetText(_aahEdit[y][x],"无效");
                EDIT_SetTextAlign(_aahEdit[y][x], GUI_TA_HCENTER | GUI_TA_VCENTER);
                EDIT_SetFont(_aahEdit[y][x], &XBF19_Font);
            }
        }
        WM_SetStayOnTop(hWindow,1);

			//
			// ³õÊ¼»¯¶àÐÐÎÄ±¾¿Ø¼þ
			//
//			hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
//			MULTIEDIT_SetText(hItem, AddressURL);
//			MULTIEDIT_SetFont(hItem, GUI_FONT_16_ASCII);
//
//			/* Ê¹ÄÜ¶àÐÐÎÄ±¾µÄ²åÈëÄ£Ê½ */
//			MULTIEDIT_SetInsertMode(hItem, 1);
//
//			/* ½«¹ö¶¯Ìõ¸½¼þµ½¶àÐÐÎÄ±¾¿Ø¼þ */
//			hScroll = SCROLLBAR_CreateAttached(hItem, GUI_ID_VSCROLL);
//			/* ÉèÖÃ¹ö¶¯ÌõµÄ¿í¶È */
//			SCROLLBAR_SetWidth(hScroll, 15);



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
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_BLACK,BUTTON_CI_UNPRESSED,GUI_BLACK,"模拟量");

        Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5),GUI_TA_HCENTER|GUI_TA_VCENTER,
                    &XBF24_Font,BUTTON_CI_UNPRESSED,GUI_BLUE,BUTTON_CI_UNPRESSED,GUI_RED,"状态量");
        BUTTON_SetPressed(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5),1);
        BUTTON_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5),BUTTON_CI_PRESSED,GUI_RED);
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

            break;
          case WM_NOTIFICATION_RELEASED:
                /**< 跳转到历史记录查询 */
                WM_SetStayOnTop(hWindow,0);
                GUI_EndDialog(hWindow,0);
                _deleteWin(_hWinManagerInfoStatus);
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
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            /**< 跳转至home */
            WM_SetStayOnTop(hWindow,0);
            GUI_EndDialog(hWindow,0);
            _deleteWin(_hWinManagerInfoStatus);
            CreateHome();
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
                /**< 跳转到模拟量信息查询 */
                WM_SetStayOnTop(hWindow,0);
                GUI_EndDialog(hWindow,0);
                _deleteWin(_hWinManagerInfoStatus);
                CreateManagerInfoAnalog();
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
            //Data_Flush(pMsg);
            Status_Content_Analy();
            WM_RestartTimer(pMsg->Data.v,3000);
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
/** @brief
 *  输出管理员界面里的信息查询状态量部分
 * @param
 * @param
 * @return
 *
 *
 *       CreateManagerInfoStatus
*/
WM_HWIN CreateManagerInfoStatus(void);
WM_HWIN CreateManagerInfoStatus(void)
{
    _hWinManagerInfoStatus = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    cur_win = _hWinManagerInfoStatus;
    _timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoStatus), ID_TimerTime, 20, 0);
    _timerData = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoStatus), ID_TimerFlush,1000,0);
    _timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoStatus), ID_TimerSignal,5000,0);
}
/*************************** End of file ****************************/




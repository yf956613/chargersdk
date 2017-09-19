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
#define ID_BUTTON_1     (GUI_ID_USER + 0x1B)
#define ID_IMAGE_0      (GUI_ID_USER + 0x1C)
// USER START (Optionally insert additional defines)
#define ID_TEXT_1     (GUI_ID_USER + 0x01)
#define ID_TEXT_2     (GUI_ID_USER + 0x02)
#define ID_TEXT_3     (GUI_ID_USER + 0x03)
#define ID_TEXT_4     (GUI_ID_USER + 0x04)

#define ID_TEXT_5     (GUI_ID_USER + 0x05)
#define ID_TEXT_6     (GUI_ID_USER + 0x06)
#define ID_TEXT_7     (GUI_ID_USER + 0x07)
#define ID_TEXT_8     (GUI_ID_USER + 0x08)
#define ID_TEXT_9     (GUI_ID_USER + 0x09)
#define ID_TEXT_10    (GUI_ID_USER + 0x0A)
#define ID_EDIT_0     (GUI_ID_USER + 0x0B)
#define ID_EDIT_1     (GUI_ID_USER + 0x0C)
#define ID_EDIT_2     (GUI_ID_USER + 0x0D)
#define ID_EDIT_3     (GUI_ID_USER + 0x0E)
#define ID_TEXT_11    (GUI_ID_USER + 0x0F)
#define ID_TEXT_12    (GUI_ID_USER + 0x10)
#define ID_TEXT_13    (GUI_ID_USER + 0x11)
#define ID_TEXT_14    (GUI_ID_USER + 0x12)
#define ID_EDIT_4     (GUI_ID_USER + 0x13)
#define ID_TEXT_15    (GUI_ID_USER + 0x14)
#define ID_EDIT_5     (GUI_ID_USER + 0x15)
#define ID_TEXT_16    (GUI_ID_USER + 0x16)
#define ID_EDIT_6     (GUI_ID_USER + 0x17)
#define ID_TEXT_17    (GUI_ID_USER + 0x18)
#define ID_EDIT_7     (GUI_ID_USER + 0x19)
#define ID_TEXT_18    (GUI_ID_USER + 0x1A)
#define ID_TEXT_19    (GUI_ID_USER + 0x1B)

#define ID_TimerTime    1
#define ID_TimerFlush   2
#define ID_TimerSignal  3
// USER END
WM_HWIN _hWinChargDone;
static WM_HTIMER _timerRTC,_timerData,_timerSignal;
static uint8_t first_flag = 0;
static uint8_t orderFinish = 0;
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
*       _aDialogChargeDone
*/
static const GUI_WIDGET_CREATE_INFO _aDialogChargeDone[] =
{
    { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
    { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 0, 0, 789, 459, 0, 0, 0 },

    { TEXT_CreateIndirect, "Text", ID_TEXT_1, 630, 0, 80, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_2, 720, 0, 70, 16, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_3, 440, 0, 180, 16, 0, 0x0, 0 },//网络信号强度
    { TEXT_CreateIndirect, "Text", ID_TEXT_4, 225, 367, 300, 20, 0, 0x0, 0 },//最底端的说明

    { BUTTON_CreateIndirect, "退出", ID_BUTTON_1, 554, 307, 100, 36, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_18, 600, 314, 61, 24, 0, 0x0, 0 },


    { TEXT_CreateIndirect, "Text", ID_TEXT_5, 300, 40, 326, 35, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_6, 190, 100, 120, 35, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_7, 222, 159, 100, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_8, 222, 199, 120, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_9, 222, 237, 100, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_10, 222, 275, 100, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 360, 159, 88, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 360, 199, 88, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 360, 237, 88, 30, 0, 0x64, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 360, 275, 88, 30, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_11, 460, 159, 80, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_12, 460, 199, 80, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_13, 460, 237, 80, 30, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_14, 460, 275, 80, 30, 0, 0x0, 0 },
    { EDIT_CreateIndirect, "Edit", ID_EDIT_4, 290, 100, 45, 35, 0, 0x64, 0 },//小时数值
    { TEXT_CreateIndirect, "Text", ID_TEXT_15, 335, 100, 70, 35, 0, 0x0, 0 },//小时
    { EDIT_CreateIndirect, "Edit", ID_EDIT_5, 405, 100, 45, 35, 0, 0x64, 0 },//分钟数值
    { TEXT_CreateIndirect, "Text", ID_TEXT_16, 450, 100, 70, 35, 0, 0x0, 0 },//分钟
    { EDIT_CreateIndirect, "Edit", ID_EDIT_6, 500, 100, 45, 35, 0, 0x64, 0 },//秒数值
    { TEXT_CreateIndirect, "Text", ID_TEXT_17, 545, 100, 70, 35, 0, 0x0, 0 },//秒钟
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void Data_Process(WM_MESSAGE *pMsg)
{
    static uint8_t timer_count = 0;
    static uint8_t num = 0;
    uint8_t Timer_buf[10];
    uint8_t temp_buf[32];
    CON_t *pCON;
    time_t now;
    static time_t first;
    volatile uint32_t diffsec;
    volatile int8_t sec;
    EventBits_t uxBits;
    uint8_t strCSQ[32];

    WM_HWIN hWin = pMsg->hWin;

    pCON = CONGetHandle(0);

    uxBits = xEventGroupWaitBits(pCON->status.xHandleEventOrder,
								defEventBitOrderFinishToHMI,
                                pdTRUE, pdTRUE, 0);

	if ((uxBits & defEventBitOrderFinishToHMI) == defEventBitOrderFinishToHMI)//订单上传完成
	{
		orderFinish = 1;
	}

	if (orderFinish == 1)
	{
		if (first_flag == 0)
		{
			first_flag = 1;
			first = time(NULL);
		}

		now = time(NULL);

		diffsec = (uint32_t)difftime(now, first);

		sec = 10 - diffsec;
		if (sec < 0)
			sec = 0;
		xsprintf((char *)_secDown, "(%02dS)", sec);
		//xsprintf((char *)Timer_buf, "(%02dS)", sec);
		if (sec == 0)
		{
			orderFinish = 0;
			first_flag = 0;
//			xEventGroupSetBits(xHandleEventHMI, defEventBitHMITimeOutToRFID);//发送HMI显示延时到事件
			//跳到HOME
			WM_SendMessageNoPara(hWin, MSG_JUMPHOME);
		}
	}

}
// USER END

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
    CON_t *pCON;
    uint32_t time_charge;
    uint8_t temp_buf[32];
    volatile int8_t hour;
    volatile int8_t min;
    volatile int8_t sec;
    EventBits_t uxBits;

    switch (pMsg->MsgId)
    {
    case WM_PAINT://MSG_UPDATEDATA:
        /// TODO (zshare#1#): 下面的if不起作用.\
        但是if里嵌套的if起作用,目前先用此来规避不起作用的if
        if((bittest(winInitDone,0))&&(_hWinChargDone == cur_win))
        {
            /**< 数据处理 */
            Data_Process(pMsg);
            /**< 信号数据处理 */
            Signal_Show();
            /**< 灯光控制 */
            Led_Show();
            /**< 如果界面发生了切换 */
            if(_hWinChargDone == cur_win)
            {
                /**< 故障分析 */
                Err_Analy(pMsg->hWin);
                /**< 特殊触控点分析 */
                CaliDone_Analy(pMsg->hWin);
            }
        }
        break;
    case WM_INIT_DIALOG:
        first_flag = 0;
        //
        //设置本页焦点
        //
        //WM_SetFocus(pMsg->hWin);
        //
        // Initialization of 'Framewin'
        //
        FrameWin_Init(pMsg, ID_TEXT_1, ID_TEXT_2, ID_TEXT_3, ID_TEXT_4,ID_IMAGE_0);

        //Initialization of 'Text'

        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_5),&XBF36_Font,GUI_BLACK,"订单上传中。。。");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_6),&XBF24_Font,GUI_BLACK,"充电时长");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_7),&XBF24_Font,GUI_BLACK,"充入电量");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_8),&XBF24_Font,GUI_BLACK,"当前服务费");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_9),&XBF24_Font,GUI_BLACK,"当前电费");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_10),&XBF24_Font,GUI_BLACK,"消费总额");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_11),&XBF24_Font,GUI_BLACK,"度");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_12),&XBF24_Font,GUI_BLACK,"元/单");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_13),&XBF24_Font,GUI_BLACK,"元/度");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_14),&XBF24_Font,GUI_BLACK,"元");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_15),&XBF24_Font,GUI_BLACK,"小时");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_16),&XBF24_Font,GUI_BLACK,"分");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_17),&XBF24_Font,GUI_BLACK,"秒");
        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_18),&XBF24_Font,GUI_BLACK,"(10S)");
//        Text_Show(WM_GetDialogItem(pMsg->hWin, ID_TEXT_19),&XBF24_Font,GUI_RED,"正在结费中...");
        //
        // Initialization of 'Edit'
        //
        pCON = CONGetHandle(0);
        memset(temp_buf,'\0',strlen(temp_buf));
        sprintf(temp_buf, "%.2lf",  pCON->order.dTotalPower);
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_0),&XBF24_Font,temp_buf);
        memset(temp_buf,'\0',strlen(temp_buf));
        sprintf(temp_buf, "%.2lf", pCON->order.dTotalServFee);
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_1),&XBF24_Font,temp_buf);
        memset(temp_buf,'\0',strlen(temp_buf));
        sprintf(temp_buf, "%.2lf", pCON->order.dTotalPowerFee);
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_2),&XBF24_Font,temp_buf);
        memset(temp_buf,'\0',strlen(temp_buf));
        sprintf(temp_buf, "%.2lf", pCON->order.dTotalFee);
        Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_3),&XBF24_Font,temp_buf);

        uxBits = xEventGroupWaitBits(pCON->status.xHandleEventOrder,
                                     defEventBitOrderMakeFinish,
                                     pdFALSE, pdTRUE, portMAX_DELAY);
        if((uxBits & defEventBitOrderMakeFinish) == defEventBitOrderMakeFinish)
        {
                time_charge = pCON->order.tStopTime - pCON->order.tStartTime;
    //        time_charge = 0;
            hour = time_charge / 3600;
            min = time_charge % 3600 / 60;
            sec = time_charge % 3600 % 60;

            memset(temp_buf,'\0',strlen(temp_buf));
            sprintf(temp_buf, "%02d", hour);
            Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_4),&XBF24_Font,temp_buf);//小时
            memset(temp_buf,'\0',strlen(temp_buf));
            sprintf(temp_buf, "%02d", min);
            Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_5),&XBF24_Font,temp_buf);//分
            memset(temp_buf,'\0',strlen(temp_buf));
            sprintf(temp_buf, "%02d", sec);
            Edit_Show(WM_GetDialogItem(pMsg->hWin, ID_EDIT_6),&XBF24_Font,temp_buf);//秒

            Button_Show(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1),GUI_TA_LEFT|GUI_TA_VCENTER,
                        &XBF24_Font,BUTTON_CI_DISABLED,GUI_BLUE,BUTTON_CI_DISABLED,GUI_BLUE,"退出");
            xEventGroupSetBits(xHandleEventHMI,defeventBitHMI_ChargeReqDispDoneOK);
            xEventGroupSetBits(pCON->status.xHandleEventOrder, defEventBitOrder_HMIDispOK);
        }

        //_timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerTime, 20, 0);
        //_timerData = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerFlush,1000,0);
        //_timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerSignal,5000,0);
        // USER END
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id)
        {
        case ID_BUTTON_1: // Notifications sent by 'Button'
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                first_flag = 0;
                _deleteWin(_hWinChargDone);
                _hWinChargDone = 0;
//                CreateHome();
                current_page = _HOMEPAGE;
                bitset(winInitDone,7);
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
//                first_flag = 0;
//                WM_DeleteWindow(pMsg->hWin);
//                xEventGroupSetBits(xHandleEventHMI, defEventBitHMITimeOutToRFID);//发送HMI显示延时到事件
//                vTaskDelay(500);
//                //PutOut_SelAOrB();
//                PutOut_Home();
                // USER END
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
            // USER START (Optionally insert additional code for further Ids)
            // USER END
        }
        break;
    case WM_TIMER:
        if(pMsg->Data.v == _timerRTC)
        {
            /**< 显示时间和日期 */
            Caculate_RTC_Show(pMsg, ID_TEXT_1, ID_TEXT_2);
            TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_18), _secDown);
            TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_3), strCSQ);
//            WM_SendMessageNoPara(_hWinCardInfo,MSG_UPDATEDATA);
	        if(orderFinish == 1)
		        TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_5), "充电完成");

            /**< 重启定时器 */
            WM_RestartTimer(pMsg->Data.v, 20);
        }
//        if(pMsg->Data.v == _timerSignal)
//        {
//            WM_RestartTimer(pMsg->Data.v, 2000);
//        }
//        if(pMsg->Data.v == _timerData)
//        {
//            //Data_Flush(pMsg);
//            //dispbmp("system/dpc.bmp", 0, 5, 5, 1, 1);
//            WM_RestartTimer(pMsg->Data.v,100);
//        }
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
    case MSG_JUMPHOME:
        first_flag = 0;
        _deleteWin(_hWinChargDone);
        _hWinChargDone = 0;
//        CreateHome();
        current_page = _HOMEPAGE;
        bitset(winInitDone,7);
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
/** @brief 创建充电完成界面
 *
 * @param
 * @param
 * @return
 *       CreateChargeDone
*/
WM_HWIN CreateChargeDone(void);
WM_HWIN CreateChargeDone(void)
{
    _hWinChargDone = GUI_CreateDialogBox(_aDialogChargeDone, GUI_COUNTOF(_aDialogChargeDone), _cbDialog, WM_HBKWIN, 0, 0);
    cur_win = _hWinChargDone;

    _timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerTime, 20, 0);
    //_timerData = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerFlush,1000,0);
    //_timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinChargDone), ID_TimerSignal,5000,0);
	bitset(winInitDone,0);
}
/*************************** End of file ****************************/






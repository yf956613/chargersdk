/*********************************************************************
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
#include "touchtimer.h"
// USER END

#include "DIALOG.h"

#include "includes.h"

#include "order.h"
#include "interface.h"
#include "utils.h"
#include "cJSON.h"
#include "evse_config.h"
#include "cfg_parse.h"
#include "stringName.h"
#include "errorcode.h"
#include <string.h>

#define BYTES_LEN 1024

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
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

#define ID_LISTWHEEL_0  (GUI_ID_USER + 0x10)
#define ID_LISTWHEEL_1  (GUI_ID_USER + 0x11)
#define ID_LISTWHEEL_2  (GUI_ID_USER + 0x12)
#define ID_LISTWHEEL_3  (GUI_ID_USER + 0x13)
#define ID_LISTWHEEL_4  (GUI_ID_USER + 0x14)
#define ID_LISTWHEEL_5  (GUI_ID_USER + 0x15)
#define ID_MULTIEDIT_0  (GUI_ID_USER + 0x16)
#define ID_LISTVIEW_0   (GUI_ID_USER + 0x17)

#define ID_TimerTime    1
#define ID_TimerFlush   2
#define ID_TimerSignal  3

#define ALARM_COLUMNS   4
#define CHARGE_COLUMNS  20
#define DB_DEBUG    0

#define analogName "模拟量"
#define analogValue "模拟量值"
#define analogACVol "交流电压"
#define analogACCurrent "交流电流"
#define analogCPVol "充电导引电压"
#define analogACFreq "频率"
#define analogACTempL "输入端子L温度"
#define analogACTempN "输入端子N温度"
#define analogOutTempL "输出端子L温度"
#define analogOutTempN "输出端子N温度"

static WM_HTIMER _timerRTC,_timerData,_timerSignal;
uint16_t column_num,row_num;
static WM_HWIN _hWinManagerInfoAnalog;
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
{
    { WINDOW_CreateIndirect, "window", ID_WINDOW_0, 0, 40, 800, 300, 0, 0x0, 0 },
    { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 20, 40, 750, 276, 0, 0x0, 0 },//560,276
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/** @brief 状态内容编辑分析
 *
 * @param
 * @param
 * @return
 *
 */
static void Status_Content_Analy(WM_MESSAGE *pMsg)
{
    CON_t *pCon;
    uint8_t strTmp[30];
    WM_HWIN hItem;

    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
    pCon = CONGetHandle(0);

    sprintf(strTmp,"%.1f",pCon->status.dChargingVoltage);
    strcat(strTmp,"V");
    LISTVIEW_SetItemText(hItem, 1, 0, strTmp);

    sprintf(strTmp,"%.1f",pCon->status.dChargingCurrent);
    strcat(strTmp,"A");
    LISTVIEW_SetItemText(hItem, 3, 0, strTmp);

    /**< 控制导引电压确认 */
    sprintf(strTmp,"%.1f",Sys_samp.DC.CP1);
    strcat(strTmp,"V");
    LISTVIEW_SetItemText(hItem, 1, 1, strTmp);

    sprintf(strTmp,"%.1f",pCon->status.dChargingFrequence);
    strcat(strTmp,"Hz");
    LISTVIEW_SetItemText(hItem, 3, 1, strTmp);

    sprintf(strTmp,"%.1f",pCon->status.dACLTemp);
    strcat(strTmp,"℃");
    LISTVIEW_SetItemText(hItem, 1, 2, strTmp);

    sprintf(strTmp,"%.1f",pCon->status.dACNTemp);
    strcat(strTmp,"℃");
    LISTVIEW_SetItemText(hItem, 3, 2, strTmp);

    sprintf(strTmp,"%.1f",pCon->status.dBTypeSocketTemp1);//acl or acn
    strcat(strTmp,"℃");
    LISTVIEW_SetItemText(hItem, 1, 3, strTmp);

    sprintf(strTmp, "%.1f", pCon->status.dBTypeSocketTemp2);
    strcat(strTmp, "℃");
    LISTVIEW_SetItemText(hItem, 3, 3, strTmp);
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE *pMsg)
{
    const void *pData;
    volatile WM_HWIN      hItem;
    U32          FileSize;
    int          NCode;
    int          Id;
    uint16_t     i,_strNum[3];
	volatile HEADER_Handle hHeader;
	char    buf[20];
//	static char  Value = 0;
    SCROLLBAR_Handle hScroll;
    SCROLLBAR_Handle wScroll;
    CON_t	*pcont;

//    static int _x,_y;
//    WM_SCROLL_STATE ScrollState;

    switch (pMsg->MsgId)
    {
    case WM_PAINT:
//        WM_SetFocus(_hWinManagerAlarmLog);
//        /// TODO (zshare#1#): 下面的if不起作用.\
//        但是if里嵌套的if起作用,目前先用此来规避不起作用的if
//        if(_hWinManagerAlarmLog == cur_win)
//        {
//            /**< 数据处理 */
//            //Data_Process(pMsg);
//            /**< 信号数据处理 */
//            Signal_Show();
//            /**< 灯光控制 */
//            Led_Show();
//            /**< 如果界面发生了切换 */
//            if(_hWinManagerAlarmLog == cur_win)
//            {
//                /**< 故障分析 */
//                //Err_Analy(pMsg->hWin);
//                /**< 特殊触控点分析 */
//                CaliDone_Analy(pMsg->hWin);
//            }
//        }
        break;
    case WM_INIT_DIALOG:
        //
        // 初始列表控件
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
        /* 设置列表控件中header控件的所显示文本的字体 */
        hHeader = LISTVIEW_GetHeader(hItem);
        HEADER_SetFont(hHeader, &SIF16_Font);

        /*srollbar*/
//        hScroll = SCROLLBAR_CreateAttached(hItem, 0);//水平滑轮
//        SCROLLBAR_SetNumItems(hScroll, 30 * 4);
//        SCROLLBAR_SetWidth(hScroll,20);
//        wScroll = SCROLLBAR_CreateAttached(hItem, SCROLLBAR_CF_VERTICAL);//垂直滑轮
//        SCROLLBAR_SetNumItems(wScroll, 30 * 20);
//        SCROLLBAR_SetWidth(wScroll,20);
        /*end*/

        /* 设置列表控件选项中所显示文本的字体 */
        LISTVIEW_SetFont(hItem, &SIF16_Font);
        /* 设置列表控件表格可见 */
        LISTVIEW_SetGridVis(hItem, 1);

        column_num = LISTVIEW_GetNumColumns(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0));
        for(i = 0;i < column_num;i++)
        {
            LISTVIEW_DeleteColumn(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0),0);
        }
        /*模拟量   模拟值     模拟量     模拟值*/
        LISTVIEW_AddColumn(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0), 200, analogName, GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0), 200, analogValue, GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0), 200, analogName, GUI_TA_HCENTER | GUI_TA_VCENTER);
        LISTVIEW_AddColumn(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0), 200, analogValue, GUI_TA_HCENTER | GUI_TA_VCENTER);

        LISTVIEW_AddRow(hItem, NULL);//增加一行
        /**< 工作状态 */
        LISTVIEW_SetItemText(hItem, 0, 0, analogACVol);
        /**< 急停状态 */
        LISTVIEW_SetItemText(hItem, 2, 0, analogACCurrent);
        LISTVIEW_AddRow(hItem, NULL);//增加一行
        /**< 电表通信 */
        LISTVIEW_SetItemText(hItem, 0, 1, analogCPVol);
        /**< A插座温度1 */
        LISTVIEW_SetItemText(hItem, 2, 1, analogACFreq);
        LISTVIEW_AddRow(hItem, NULL);//增加一行
        /**< A插座温度2 */
        LISTVIEW_SetItemText(hItem, 0, 2, analogACTempL);
        /**< A枪输出电流 */
        LISTVIEW_SetItemText(hItem, 2, 2, analogACTempN);
        LISTVIEW_AddRow(hItem, NULL);//增加一行
        /**< RFID */
        LISTVIEW_SetItemText(hItem, 0, 3, analogOutTempL);
        /**< A枪枪锁 */
        LISTVIEW_SetItemText(hItem, 2, 3, analogOutTempN);
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id) {

        break;
    }
    case WM_TIMER:
//        if(pMsg->Data.v == _timerRTC)
//        {
//            /**< 显示时间和日期 */
//            Caculate_RTC_Show(pMsg, ID_TEXT_1, ID_TEXT_2);
//           // TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_3), strCSQ);
//            /**< 重启定时器 */
//            WM_RestartTimer(pMsg->Data.v, 20);
//        }
//        if(pMsg->Data.v == _timerSignal)
//        {
//
//            WM_RestartTimer(pMsg->Data.v, 2000);
//        }
        if(pMsg->Data.v == _timerData)
        {
            Status_Content_Analy(pMsg);
            WM_RestartTimer(pMsg->Data.v,1000);
        }
        break;
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
 *  输出管理员界面里的信息状态量部分
 * @param
 * @param
 * @return
 *       CreateManagerInfoAnalog
*/
WM_HWIN CreateManagerInfoAnalog(WM_HWIN srcHwin)
{
    _hWinManagerInfoAnalog = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_GetClientWindow(srcHwin), 0, 0);
//    _timerRTC = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerTime, 20, 0);
    _timerData = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerFlush,1000,0);
//    _timerSignal = WM_CreateTimer(WM_GetClientWindow(_hWinManagerInfoAnalog), ID_TimerSignal,5000,0);
    return _hWinManagerInfoAnalog;
}
/*************************** End of file ****************************/










﻿#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "DIALOG.h"
#include "pyinput.h"

//键盘类型，包括英文键盘，数字键盘，符号键盘，九宫格中文输入法键盘
typedef enum
{
	ENGLISH_KEYPAD,		//英文键盘
	NUMBER_KEYPAD,		//数字键盘
	SIGN_KEYPAD,		//符号键盘
	CHINESE_KEYPAD,	    //九宫格中文输入法键盘
	KEYPAD_NUM			//键盘数量
}keypad_type;

//keypad配置结构体
typedef struct
{
	keypad_type padtype;				//键盘类型
	u16 xpos;							//软键盘X坐标
	u16 ypos;							//软键盘Y坐标
	u16 width;							//软键盘宽度
	u16 height;							//软键盘高度
	WM_HWIN hKeypad;					//软键盘窗口句柄
	WM_HWIN EngButton_Handle[35];		//英文键盘上按钮句柄
	WM_HWIN NumButton_Handle[20];		//数字键盘上按钮句柄
	WM_HWIN SignButton_Handle[20];		//符号键盘上按钮句柄
    WM_HWIN ChineseButton_Handle[25];   //中文键盘上按钮句柄
    u8      inputstr[7];                //输入字符串，最大6个字符+结束符
    u8      inputlen;                   //输入长度
    u8      cur_index;                  //当前拼音索引
    u8      result_num;                 //拼音匹配数
    u8      pypagenum;                  //拼音页数
    u8      pynowpage;                  //当前选中的拼音页
    u8      dispagenum;                 //汉字显示总页数
    u8      dispagecur;                 //当前汉字显示页
    u8      *disstr;                    //横向显示的字符串指针
    u8      *cur_hz;                    //当前选中的汉字
    u8      hznum;                      //选中的拼音对应的汉字数量
    u8      disbuf[6][3];               //横向按钮缓存
    u8      *butname[6];                //按钮名字
    u8      sta;                        //记录输入法状态
                                        //bit7: 0,第一次进入中文输入法;1,前面已经进入了中文输入法
	u8 LowerCase;						//0 大写;1 小写
	u8 signpad_flag;					//符号键盘索引
	u8 signpad_num;						//符号键盘的数量

} KEYPADStructTypeDef;


#define COLOR_BACK0            0xFF3333
#define COLOR_BACK1            0x550000
#define COLOR_BORDER           0x444444
#define COLOR_KEYPAD0          0xAAAAAA
#define COLOR_KEYPAD1          0x555555
#define BUTTON_COLOR0          0xEEEEEE
#define BUTTON_COLOR1          0xCCCCCC
#define BUTTON_COLOR2          0xCCCCCC
#define BUTTON_COLOR3          0xAAAAAA
#define BUTTON_SKINFLEX_RADIUS 4

#define ID_BUTTON              (GUI_ID_USER + 0)

//自定义消息
#define CHANGE_ENGLISHPADTO_NUMPAD	   	(WM_USER+0)
#define CHANGE_ENGLISHPADTO_SIGNPAD1	(WM_USER+1)
#define CHANGE_ENGLISHPADTO_CHINESEPAD	(WM_USER+2)
#define CHANGE_NUMPADTO_ENGLISHPAD		(WM_USER+3)
#define CHANGE_SIGNPADTO_ENGLISHPAD	    (WM_USER+4)
#define CHANGE_SIGNPAD					(WM_USER+5)
#define CHANGE_CHINESEPADTO_ENGLISHPAD  (WM_USER+6)
#define CHANGE_CHINESE_PY               (WM_USER+7)


//英文键盘按键参数
#define ENG_BUTTON_WIDTH			41	//英文键盘按钮宽度
#define ENG_BUTTON_HEIGHT			72	//英文键盘按钮的高度
#define ENG_BUTTON_XPAC				5	//英文键盘按钮X轴间距

#define ENG_BUTTON_LINE1YPOS		7	//英文键盘第一行Y坐标
#define ENG_BUTTON_LINE2YPOS		85	//英文键盘第二行Y坐标
#define ENG_BUTTON_LINE3YPOS		163	//英文键盘第三行Y坐标
#define ENG_BUTTON_LINE4YPOS		241	//英文键盘第四行Y坐标

#define ENG_BUTTONLINE1_XOFFSET		7	//英文键盘第一行按钮X轴偏移
#define ENG_BUTTONLINE2_XOFFSET		30	//英文键盘第二行按钮X轴偏移
#define ENG_BUTTONLINE3_XOFFSET		7	//英文键盘第三行按钮X轴偏移
#define ENG_BUTTONLINE4_XOFFSET		7	//英文键盘第四行按钮X轴偏移

#define ENG_BUTTONSHIFT_XINC		23	//英文键盘shift键的X轴长度增量
#define ENG_BUTTONENTER_XINC		23	//英文键盘回车键的X轴长度增量
#define ENG_BUTTONFIGURE_XINC		23	//英文键盘数字键的X轴长度增量
#define ENG_BUTTONSYMBOL_XINC		23	//英文键盘符号键的X轴长度增量
#define ENG_BUTTONSPACE_XINC		45	//英文键盘空格键的X轴长度增量
#define ENG_BUTTONCE_XINC			23	//英文键盘中英文切换按键的X轴长度增量
#define ENG_BUTTONBACK_XINC			23	//英文键盘删除键的X轴长度增量

//数字键盘按键参数
#define NUM_BUTTON_WIDTH			110	//数字键盘按钮宽度
#define NUM_BUTTON_HEIGHT			72	//数字键盘按钮高度
#define NUM_BUTTON_XPAC				5	//数字键盘按钮X轴间距
#define NUM_BUTTON_XOFFSET			7	//数字键盘每行按钮X轴偏移

#define NUM_BUTTON_LINE1YPOS		7	//数字键盘第一行Y坐标
#define NUM_BUTTON_LINE2YPOS		85	//数字键盘第二行Y坐标
#define NUM_BUTTON_LINE3YPOS		163	//数字键盘第三行Y坐标
#define NUM_BUTTON_LINE4YPOS		241	//数字键盘第四行Y坐标

#define NUM_BUTTONSING_XINC			70	//数字键盘中符号的X轴长度增量
#define NUM_BUTTONBACKSPACE_XINC	42	//数字键盘中删除键的X轴长度增量
#define NUM_BUTTONSPACE_XINC		42	//数字键盘中空格键的X轴长度增量
#define NUM_BUTTONENTER_XINC		42	//数字键盘中回车键的X轴长度增量
#define NUM_BUTTONRETURN_XINC		42	//数字键盘中返回键的X轴长度增量

//符号键盘按键参数
#define SING_BUTTON_WIDTH			93	//符号键盘按钮宽度
#define SIGN_BUTTON_HEIGHT			72	//符号键盘按钮高度
#define SIGN_BUTTON_XPAC			5	//符号键盘按钮X轴间距
#define SIGN_BUTTON_XOFFSET			7	//符号键盘每行按钮X轴偏移
#define SIGN_BUTTONCONTR_XINC		28	//符号键盘中控制按键的X轴长度增量

#define SIGN_BUTTON_LINE1YPOS		7	//符号键盘第一行Y坐标
#define SIGN_BUTTON_LINE2YPOS		85	//符号键盘第二行Y坐标
#define SIGN_BUTTON_LINE3YPOS		163	//符号键盘第三行Y坐标
#define SIGN_BUTTON_LINE4YPOS		241	//符号键盘第四行Y坐标

//中文键盘按键参数1
#define CHIN1_BUTTON_WIDTH			90	//中文键盘1按钮宽度
#define CHIN1_BUTTON_HEIGHT			81	//中文键盘1按钮高度
#define CHIN1_BUTTON_XPAC			5	//中文键盘1按钮X轴间距
#define CHIN1_BUTTON_XOFFSET	    110	//中文键盘1每行按钮X轴偏移
#define CHIN1_BUTTONCONTR_XINC		15	//中文键盘1中控制按键的X轴长度增量

#define CHIN1_BUTTON_LINE1YPOS		56	//中文键盘1第一行Y坐标
#define CHIN1_BUTTON_LINE2YPOS		144	//中文键盘1第二行Y坐标
#define CHIN1_BUTTON_LINE3YPOS		232	//中文键盘1第三行Y坐标

//中文键盘按键参数2
#define CHIN2_BUTTON_WIDTH			60	//中文键盘2按钮宽度
#define CHIN2_BUTTON_HEIGHT			50	//中文键盘2按钮高度
#define CHIN2_BUTTON_XPAC			0	//中文键盘2按钮X轴间距
#define CHIN2_BUTTON_XOFFSET	    0	//中文键盘2每行按钮X轴偏移
#define CHIN2_BUTTONPY_XINC		    50	//中文键盘2中控制按键的X轴长度增量
#define CHIN2_BUTTONPY_YINC         4   //中文键盘2中控制按键的Y轴长度增量

#define CHIN2_BUTTON_LINE1YPOS		0	//中文键盘2第一行Y坐标
#define CHIN2_BUTTON_LINE2YPOS		50	//中文键盘2第二行Y坐标
#define CHIN2_BUTTON_LINE3YPOS		104	//中文键盘2第三行Y坐标
#define CHIN2_BUTTON_LINE4YPOS		158	//中文键盘2第四行Y坐标
#define CHIN2_BUTTON_LINE5YPOS		212	//中文键盘2第五行Y坐标
#define CHIN2_BUTTON_LINE6YPOS		266	//中文键盘2第五行Y坐标

/*********************************************************************
*
*       bmEnter, bmBackSpace, bmUp: Bitmaps used for keyboard
*/
static GUI_CONST_STORAGE unsigned long acEnter[] = {
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50505050, 0x50505050,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
  0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
  0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x50505050,
  0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static GUI_CONST_STORAGE GUI_BITMAP bmEnter = {
  16, // XSize
  8, // YSize
  64, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)acEnter,  // Pointer to picture data
  NULL  // Pointer to palette
 ,GUI_DRAW_BMP8888
};

static GUI_CONST_STORAGE unsigned long acBackSpace[] = {
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0A0A0A0, 0x20202020, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static GUI_CONST_STORAGE GUI_BITMAP bmBackSpace = {
  16, // XSize
  8, // YSize
  64, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)acBackSpace,  // Pointer to picture data
  NULL  // Pointer to palette
 ,GUI_DRAW_BMP8888
};

static GUI_CONST_STORAGE unsigned long acShift[] = {
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x52000000, 0x52000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xBB000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000,
        0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000,
        0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBC000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xBD000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xBD000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xBD000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000, 0xFF000000,
  0xBD000000, 0x14000000, 0xBD000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xBC000000, 0x14000000, 0xBD000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x00000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0x00000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static GUI_CONST_STORAGE GUI_BITMAP bmShift = {
  30, // xSize
  29, // ySize
  120, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)acShift,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

static GUI_CONST_STORAGE unsigned long _acReturn[] = {
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xF8000000, 0x45000000, 0x83000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xF3000000, 0x3A000000, 0x00000000, 0xB1000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xEE000000, 0x30000000, 0x05000000, 0xC8000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xE7000000, 0x2F000000, 0x1F000000, 0xE3000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xD1000000, 0x27000000, 0x00000000, 0x75000000, 0xA8000000, 0x9F000000, 0x9F000000, 0xA1000000, 0xA2000000, 0xA3000000, 0xA4000000, 0xA5000000, 0xAB000000, 0xC3000000, 0xF0000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0x7F000000, 0x00000000, 0x01000000, 0x19000000, 0x04000000, 0x02000000, 0x01000000, 0x01000000, 0x01000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x05000000, 0x69000000, 0xEF000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0x74000000, 0x00000000, 0x7C000000, 0xFB000000, 0xF1000000, 0xEE000000, 0xEE000000, 0xED000000, 0xEC000000, 0xEB000000, 0xEA000000, 0xE7000000, 0xD0000000, 0x83000000, 0x05000000, 0x1E000000, 0xDE000000, 0xFF000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0x7E000000, 0x00000000, 0x86000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xE1000000, 0x1B000000, 0x28000000, 0xF9000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x87000000, 0x00000000, 0x75000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xD2000000, 0x00000000, 0x95000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x92000000, 0x00000000, 0x6B000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x3A000000, 0x35000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x98000000, 0xA0000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x72000000, 0x16000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x65000000, 0x1C000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x1C000000, 0x51000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x92000000, 0x00000000, 0xC4000000,
  0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0x92000000, 0x00000000, 0x6E000000, 0xFF000000,
  0xFF000000, 0xA6000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8E000000, 0x8F000000, 0x8B000000, 0x6B000000, 0x1E000000, 0x00000000, 0x73000000, 0xFF000000, 0xFF000000,
  0xFF000000, 0x45000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x12000000, 0x14000000, 0x23000000, 0x5E000000, 0xC8000000, 0xFF000000, 0xFF000000, 0xFF000000
};

static GUI_CONST_STORAGE GUI_BITMAP bmReturn = {
  20, // xSize
  18, // ySize
  80, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acReturn,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMP8888
};

void Keypad_GetValue(void);
#endif


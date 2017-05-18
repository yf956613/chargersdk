#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "includes.h"

#define TP_PRES_DOWN 0x80  //����������
#define TP_CATH_PRES 0x40  //�а���������
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��
#ifndef bitset
#define bitset(var,bitno) ((var) |= (1<<(bitno)))           //��λ
#endif

#ifndef bitclr
#define bitclr(var,bitno) ((var) &= ~(1<<(bitno)))          //��0
#endif

#ifndef bittest
#define bittest(var,bitno) ((var >> bitno)& 0x01)           //λ״̬���
#endif
//������������
typedef struct
{
	uint8_t (*init)(void);			//��ʼ��������������
	uint8_t (*scan)(uint8_t);				//ɨ�败����.0,��Ļɨ��;1,��������;
	void (*adjust)(void);		//������У׼
	uint16_t x[CT_MAX_TOUCH]; 		//��ǰ����
	uint16_t y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������.
	uint8_t  sta;					//�ʵ�״̬
								//b7:����1/�ɿ�0;
	                            //b6:0,û�а�������;1,�а�������.
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////
	float xfac;
	float yfac;
	short xoff;
	short yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP)
//b1~6:����.
//b7:0,������
//   1,������
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//������оƬ��������
//#define PEN     PHin(7)    //T_PEN
//#define DOUT    PGin(3)    //T_MISO
//#define TDIN    PIout(3)   //T_MOSI
//#define TCLK    PHout(6)   //T_SCK
//#define TCS     PIout(8)   //T_CS


#define PEN     PDin(3)    //T_PEN
#define DOUT    PGin(12)    //T_MISO
#define TDIN    PGout(14)   //T_MOSI
#define TCLK    PGout(13)   //T_SCK
#define TCS     PFout(9)   //T_CS
//����������
void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//˫�����ȡ(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color);//��һ������У׼��
void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color);	//��һ�����
uint8_t TP_Save_Adjdata(void);						//����У׼����
uint8_t TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac);//��ʾУ׼��Ϣ
//������/������ ���ú���
uint8_t TP_Scan(uint8_t tp);								//ɨ��
uint8_t TP_Init(void);								//��ʼ��
void GUI_Touch_Calibrate();
#endif

















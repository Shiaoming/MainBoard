#pragma once
#include "includes.h"

#define USEOLED

/******************************OLED引脚相关宏定义******************************/
// 常规
#define OLED_GPIO_PORT      		GPIOD
#define OLED_GPIO_SDA        		GPIO_Pin_10
#define OLED_GPIO_SCL        		GPIO_Pin_8
#define OLED_GPIO_RST      			GPIO_Pin_9
#define OLED_GPIO_DC      			GPIO_Pin_11
// 时钟
#define OLED_GPIO_Port_Enable()			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
/******************************OLED引脚相关宏定义******************************/

/******************************OLED引脚相关宏定义******************************/
#define OLED_RST_Clr() 	GPIO_ResetBits(OLED_GPIO_PORT,OLED_GPIO_RST)
#define OLED_RST_Set() 	GPIO_SetBits(OLED_GPIO_PORT,OLED_GPIO_RST)    //接OLED模块RST

#define OLED_DC_Clr() 	GPIO_ResetBits(OLED_GPIO_PORT,OLED_GPIO_DC)
#define OLED_DC_Set() 	GPIO_SetBits(OLED_GPIO_PORT,OLED_GPIO_DC)     //接OLED模块D/C

#define OLED_SDA_Clr() 	GPIO_ResetBits(OLED_GPIO_PORT,OLED_GPIO_SDA)
#define OLED_SDA_Set() 	GPIO_SetBits(OLED_GPIO_PORT,OLED_GPIO_SDA)    //接OLED模块MOSI

#define OLED_SCL_Clr() 	GPIO_ResetBits(OLED_GPIO_PORT,OLED_GPIO_SCL)
#define OLED_SCL_Set() 	GPIO_SetBits(OLED_GPIO_PORT,OLED_GPIO_SCL)    //接OLED模块的CLK
/******************************OLED引脚相关宏定义******************************/

// 下面宏定义的作用是使用UCOSIII操作系统中的ms延时
#define	OLED_DLY_ms(ms)	OS_ERR err;\
	  					OSTimeDlyHMSM(0,0,0,ms,OS_OPT_TIME_HMSM_STRICT,&err);
//#define OLED_DLY_ms(ms) OLED_DLY_ms_i(ms);

#define X_WIDTH 		128
#define Y_WIDTH 		64


//OLED控制用函数
void OLED_WrDat(unsigned char data);//写数据
void OLED_WrCmd(unsigned char cmd);//写命令
void OLED_Set_Pos(unsigned char x, unsigned char y);//设置起始点坐标
void OLED_Fill(unsigned char bmp_data);//全屏填充
void OLED_CLS(void);//清屏
void OLED_DLY_ms_i(int ms);
void OLED_Init(void);//初始化
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);



void OLED_Init_Show(void);
//void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);
//void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);


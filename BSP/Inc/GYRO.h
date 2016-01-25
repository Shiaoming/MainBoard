/*******************************Copyright (c)***********************************
  *                      北京交通大学Robocon2015机器人小组
  ******************************************************************************
  * @文件	GYRO.h
  * @日期	2014-10-18
  * @说明	陀螺仪采集
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  *         UCOS版本:3.04.04(已自行修改添加FPU的支持)
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  * 引脚说明：
  * USART2：
  *		TX	 	A2
  *		RX	 	A3
  *		NRST	A5
  * 版	 本：	V1.0(原作者)
  *				V1.1:赵小铭(2014-10-18),重写接收方式，改为从缓冲区中直接读取数据帧
  *				V1.2:赵小铭(2014-12-03),修复硬件中断bug,添加陀螺仪复位函数Gyro_RST
  *				V1.3:赵小铭(2015-02-17),移植到STM32F4，UCOSIII,规范化宏定义等
  ******************************************************************************
  */

#pragma once
#include "includes.h"

/********************************串口相关宏定义********************************/
// 常规
#define Gyro_USART				USART3
#define Gyro_USART_PORT      	GPIOB
#define Gyro_USART_TX        	GPIO_Pin_10
#define Gyro_USART_RX        	GPIO_Pin_11
#define Gyro_USART_Baud      	19200
#define	Gyro_Reset_PORT			GPIOA
#define	Gyro_Reset_PIN			GPIO_Pin_8
// 复用
#define Gyro_USART_AF			GPIO_AF_USART3
#define Gyro_TX_PinSource      	GPIO_PinSource10
#define Gyro_RX_PinSource      	GPIO_PinSource11
// 时钟
#define Gyro_USART_Enable()			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE)
#define Gyro_USART_Port_Enable()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE)
#define Gyro_Reset_Port_Enable()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE)
// 中断
#define Gyro_USART_IRQn			USART3_IRQn
#define Gyro_USART_IRQHandler	USART3_IRQHandler
/********************************串口相关宏定义********************************/

void Gyro_Init(void);
void Gyro_RST(void);
extern float Theta;
extern float Angle;
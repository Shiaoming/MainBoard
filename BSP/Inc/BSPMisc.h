#pragma once
#include "includes.h"

/////////////////////////////////////按键宏定义
#define PORT_KEY1		GPIOC
#define PORT_KEY2		GPIOC
#define PORT_KEY3		GPIOC
#define PORT_KEY4		GPIOA

#define PIN_KEY1		GPIO_Pin_14
#define PIN_KEY2		GPIO_Pin_13
#define PIN_KEY3		GPIO_Pin_15
#define PIN_KEY4		GPIO_Pin_8

#define KEY_PORT_ENABLE()				{	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);\
											RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);}

/////////////////////////////////////LED宏定义
#define PORT_LED0		GPIOA
#define PORT_LED1		GPIOD
#define PORT_LED2		GPIOD
#define PORT_LED3		GPIOC
#define PORT_LED4		GPIOC

#define PIN_LED0		GPIO_Pin_3
#define PIN_LED1		GPIO_Pin_3
#define PIN_LED2		GPIO_Pin_1
#define PIN_LED3		GPIO_Pin_12
#define PIN_LED4		GPIO_Pin_10

#define LED_PORT_ENABLE()				{	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);\
											RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);\
											RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);}

/////////////////////////////////////拨码宏定义
#define PORT_STATU1		GPIOD
#define PORT_STATU2		GPIOB
#define PORT_STATU3		GPIOB
#define PORT_STATU4		GPIOB

#define PIN_STATU1		GPIO_Pin_6
#define PIN_STATU2		GPIO_Pin_5
#define PIN_STATU3		GPIO_Pin_7
#define PIN_STATU4		GPIO_Pin_9

#define STATU_PORT_ENABLE()				{	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);\
											RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);}

/////////////////////////////////////蜂鸣器宏定义
#define PORT_BEEP		GPIOC

#define PIN_BEEP		GPIO_Pin_5

#define BEEP_PORT_ENABLE()				{	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);}

/////////////////////////////////////LED闪烁宏定义
#define CORE_ON() 			GPIO_ResetBits(PORT_LED0,PIN_LED0)
#define CORE_OFF() 			GPIO_SetBits(PORT_LED0,PIN_LED0)
#define CORE_Toggle() 		GPIO_ToggleBits(PORT_LED0,PIN_LED0)
#define RED_ON() 			GPIO_ResetBits(PORT_LED1,PIN_LED1)
#define RED_OFF() 			GPIO_SetBits(PORT_LED1,PIN_LED1)
#define RED_Toggle() 		GPIO_ToggleBits(PORT_LED1,PIN_LED1)
#define YELLOW_ON() 		GPIO_ResetBits(PORT_LED2,PIN_LED2)
#define YELLOW_OFF() 		GPIO_SetBits(PORT_LED2,PIN_LED2)
#define YELLOW_Toggle() 	GPIO_ToggleBits(PORT_LED2,PIN_LED2)
#define GREEN_ON() 			GPIO_ResetBits(PORT_LED3,PIN_LED3)
#define GREEN_OFF() 		GPIO_SetBits(PORT_LED3,PIN_LED3)
#define GREEN_Toggle() 		GPIO_ToggleBits(PORT_LED3,PIN_LED3)
#define BLUE_ON() 			GPIO_ResetBits(PORT_LED4,PIN_LED4)
#define BLUE_OFF() 			GPIO_SetBits(PORT_LED4,PIN_LED4)
#define BLUE_Toggle() 		GPIO_ToggleBits(PORT_LED4,PIN_LED4)
/////////////////////////////////////蜂鸣器工作宏定义
#define BEEP_ON() 			GPIO_ResetBits(PORT_BEEP,PIN_BEEP)
#define BEEP_OFF() 			GPIO_SetBits(PORT_BEEP,PIN_BEEP)
#define BEEP_Toggle() 		GPIO_ToggleBits(PORT_BEEP,PIN_BEEP)

//范围限制
#define RANGE_LIMIT(x,min,max)	if(x > max)x = max;\
								else if(x < min)x = min;
#define abs(x)					fabs(x)
								
void delay_ms(int tmp);

void USART1_Init(void);
void LED_Init(void);
void KEY_Init(void);
void BEEP_Init(void);
void STATU_Init(void);
void Peripheral_Init(void);

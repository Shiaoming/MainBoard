/**
  ******************************************************************************
  * @文件	TASK.h
  * @日期	2015-2-15
  * @说明	系统配置
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
  */

#pragma once
#include "includes.h"

// 启动任务
#define STARTUP_TASK_PRIO 3								// 任务优先级
#define STARTUP_TASK_STK_SIZE 256						// 任务堆栈大小
extern OS_TCB TASK_START_TCB;							// 任务TCB控制块
extern CPU_STK TASK_START_STK[STARTUP_TASK_STK_SIZE];	// 任务堆栈空间

// LED任务
#define TASK_LED_BEEP_PRIO 20									// 任务优先级
#define TASK_LED_BEEP_STK_SIZE 256							// 任务堆栈大小
#define TASK_LED_BEEP_DELAY 50								// 任务延时							// 任务延时

// CAN1发送任务
#define TASK_CAN_PRIO 4									// 任务优先级
#define TASK_CAN_STK_SIZE 256							// 任务堆栈大小
#define TASK_CAN_DELAY 10								// 任务延时

// 计时任务
#define TASK_TIME_PRIO 12								// 任务优先级
#define TASK_TIME_STK_SIZE 128							// 任务堆栈大小
#define TASK_TIME_DELAY 500

// 显示任务
#define TASK_SHOW_PRIO 13								// 任务优先级
#define TASK_SHOW_STK_SIZE 128							// 任务堆栈大小
#define TASK_SHOW_DELAY 20

// 按键拨码读取任务
#define TASK_KEY_PRIO 14								// 任务优先级
#define TASK_KEY_STK_SIZE 128							// 任务堆栈大小
#define TASK_KEY_DELAY 20				// 任务延时

// 手柄读取任务
#define TASK_PS_PRIO 8								// 任务优先级
#define TASK_PS_STK_SIZE 128							// 任务堆栈大小
#define TASK_PS_DELAY 20				// 任务延时

// 手柄读取任务
#define TASK_ADC_PRIO 9								// 任务优先级
#define TASK_ADC_STK_SIZE 128							// 任务堆栈大小
#define TASK_ADC_DELAY 20				// 任务延时


// 任务声明
void TASK_START(void);
void TASK_LED_BEEP(void *p_arg);
void TASK_CAN(void *p_arg);
void TASK_TIME(void *p_arg);
void TASK_SHOW(void *p_arg);
void TASK_KEY(void *p_arg);
void TASK_PS(void *p_arg);
void TASK_ADC(void *p_arg);

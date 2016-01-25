/**
  ******************************************************************************
  * @文件	includes.h
  * @日期	2015-1-26
  * @说明	所有头文件
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "arm_math.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "arm_math.h"

/* BSP -----------------------------------------------------------------------*/
#include "BSP.h"
#include "BSPMisc.h"
#include "Usart1.h"
#include "Can1.h"
#include "Can2.h"
#include "oled.h"
#include "GYRO.h"
#include "PS_Driver.h"
#include "adc.h"


/* APP -----------------------------------------------------------------------*/
#include "Sysinit.h"
#include "os.h"
#include "TASK.h"
#include "CANQueue.h"
#include "ArmFan.h"
#include "speed.h"
#include "GP2Y0A21YK0F.h"





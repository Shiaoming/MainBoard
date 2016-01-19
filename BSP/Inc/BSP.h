/**
  ******************************************************************************
  * @文件	BSP.h
  * @日期	2015-2-15
  * @说明	UCOSIII板级支持包声明
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  */

#pragma once
#include "includes.h"
#include "os.h"

void SysTickInit(void);
void Delay_ms(unsigned int t);
#pragma once
#include "includes.h"


// 系统时间
typedef struct
{
	int hour;
	int min;
	int sec;
}Time_TypeDef;


void Struct_Init(void);

void Sys_Start(void);



// 系统运行时钟
extern	Time_TypeDef Time;

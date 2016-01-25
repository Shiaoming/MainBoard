#pragma once
#include "includes.h"

#define HEIGHT_MIN      0
#define HEIGHT_MAX      500

#define DIRECTION_MIN   0
#define DIRECTION_MAX   180

#define SPEED_MIN		0
#define SPEED_MAX		500

//风扇机械臂默认位置
#define DEFAULT_HIGHT	250
#define DEFAULT_SPEED	0
#define DEFAULT_DIR		55

// 风扇机械臂控制量
typedef struct
{
	s16 height;
	s16 FanSpeed;
	s16 FanDirection;
}Fan_TypeDef;

void Set_Fan(s16 height,s16 FanSpeed,s16 FanDirection);
void FanStruct_Init(void);

extern Fan_TypeDef FanCMD;
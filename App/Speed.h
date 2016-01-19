#include "includes.h"


#define LL1  535.0  //新底盘尺寸  
#define LL2  464.0
#define R   50.0

/**
  * @说明 速度定义
  */
typedef struct
{
	s32 vx;
    s32 vy;
    s32 wz;
}SPEEDTypeDef;

extern SPEEDTypeDef Speed;

typedef struct
{
	s32 speed0,speed1,speed2,speed3;
}RobotWspeed;

extern RobotWspeed robotw; 

#define VX 100
#define VY 100
#define WZ 50

void PS_Digital_Mode(void);
void PS_Analog_Red(void);
void Set_Speed(void);


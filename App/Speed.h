#include "includes.h"


#define LL1  535.0  //新底盘尺寸  
#define LL2  464.0
#define R   500.0

#define MAX_WHELL_SPEED		40

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

#define VX 50
#define VY 50
#define WZ 10

void PS_Digital_Mode(void);
void PS_Analog_Red(void);
void Set_Speed(void);
void Speed_Mode_Init(void);

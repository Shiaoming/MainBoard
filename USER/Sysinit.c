#include "includes.h"

Time_TypeDef Time;

// 初始化反应
void Sys_Start(void)
{
	OS_ERR err;
	
	RED_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);//这个时间显然不止80ms,大约200ms
	RED_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	YELLOW_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	CORE_Toggle();
	YELLOW_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	GREEN_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	GREEN_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	BLUE_Toggle();
	BEEP_Toggle();
	OSTimeDlyHMSM(0,0,0,80,OS_OPT_TIME_HMSM_STRICT,&err);
	BLUE_Toggle();
	BEEP_Toggle();
	CORE_Toggle();
}

/*******************************************************************************
函 数 名：App_Init(void)
描    述：系统结构体初始化指向
*******************************************************************************/
void App_Init(void)
{
	FanStruct_Init();
}


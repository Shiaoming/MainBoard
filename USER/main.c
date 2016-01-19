/**
  ******************************************************************************
  * @文件	main.c
  * @日期	2015-2-15
  * @说明	程序入口
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  *         UCOS版本:3.04.04
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  */
#include "includes.h"

/*******************************************************************************
函 数 名：main(void)
描    述：程序入口
*******************************************************************************/
void main(void)
{
    OS_ERR err;
    
    OSInit(&err); 
    
    OSTaskCreate((OS_TCB     *)&TASK_START_TCB,
                 (CPU_CHAR   *)"TASK_START",
                 (OS_TASK_PTR)TASK_START,
                 (void       *)0,
                 (OS_PRIO    ) STARTUP_TASK_PRIO,
                 (CPU_STK    *)&TASK_START_STK[0],
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE / 10,
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,
                 (OS_MSG_QTY )0,
                 (OS_TICK    )0,
                 (void       *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
                 (OS_ERR     *)&err);    
    
    OSStart(&err);
}


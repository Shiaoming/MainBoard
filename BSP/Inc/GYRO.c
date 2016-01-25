/*******************************Copyright (c)***********************************
  *                      北京交通大学Robocon2015机器人小组
  ******************************************************************************
  * @文件	Gyro.c
  * @日期	2014-10-18
  * @说明	陀螺仪采集
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
  * 引脚说明：
  * USART2：
  *		TX	 	A2
  *		RX	 	A3
  *		NRST	A5
  * 版	 本：	V1.0(原作者)
  *				V1.1:赵小铭(2014-10-18),重写接收方式，改为从缓冲区中直接读取数据帧
  *				V1.2:赵小铭(2014-12-03),修复硬件中断bug,添加陀螺仪复位函数Gyro_RST
  *				V1.3:赵小铭(2015-02-17),移植到STM32F4，UCOSIII,规范化宏定义等
  ******************************************************************************
  */
#include "includes.h"

u16 Gyro_Buffer[40];		// 数据缓存数组,内部使用
char Gyro_RecPointer = 0;	// 数据缓存指针,内部使用
s16 iAngle;					// 整型的角度数据，未除以10,内部使用
float Angle;				// 浮点型的角度，未进行规整,内部使用
float Theta;				// 浮点型的角度(弧度制)，-pi~pi范围,内部使用

/*******************************************************************************
* Function Name  : void Gyro_Usart_Init()
* Description    : 陀螺仪通信串口，串口2配置初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Gyro_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	Gyro_USART_Port_Enable();
	Gyro_USART_Enable();

    // TX，RX管脚模式配置
	GPIO_InitStructure.GPIO_Pin = Gyro_USART_TX | Gyro_USART_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;				//翻转速度为50M
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Gyro_USART_PORT,&GPIO_InitStructure);

	// 复用功能配置
	GPIO_PinAFConfig(Gyro_USART_PORT,Gyro_TX_PinSource,Gyro_USART_AF);
	GPIO_PinAFConfig(Gyro_USART_PORT,Gyro_RX_PinSource,Gyro_USART_AF);

	// Reset脚
	Gyro_Reset_Port_Enable();
	GPIO_InitStructure.GPIO_Pin = Gyro_Reset_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Gyro_Reset_PORT,&GPIO_InitStructure);

	GPIO_ResetBits(Gyro_Reset_PORT,Gyro_Reset_PIN);

    //串口工作模式配置
	USART_InitStructure.USART_BaudRate = Gyro_USART_Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(Gyro_USART,&USART_InitStructure);
	USART_Cmd(Gyro_USART,ENABLE);

    //中断配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = Gyro_USART_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    //开中断
    USART_ITConfig(Gyro_USART,USART_IT_RXNE,ENABLE);
}

/*******************************************************************************
* Function Name  : void Gyro_RST(void)
* Description    : 陀螺仪复位
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Gyro_RST(void)
{
	volatile unsigned char i=0;
	GPIO_ResetBits(Gyro_Reset_PORT,Gyro_Reset_PIN);
	//延时2S
	OS_ERR err;
	OSTimeDlyHMSM(0, 0, 2, 0,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
	GPIO_SetBits(Gyro_Reset_PORT,Gyro_Reset_PIN);
}


/*******************************************************************************
* Function Name  : TransTheta(float fAngle)
* Description    : 内部调用，用于角度转换
* Input          : Angle：浮点型的角度(角度制)，取值任意
* Return         : theta:浮点型的角度(弧度制)，范围-pi~pi
* BUG            : NoBug
*******************************************************************************/
float TransTheta(float angle)
{
    float theta;
    while(angle > 180.0)
    {
        angle -= 360.0;
    }
    while(angle < -180.0)
    {
        angle += 360.0;
    }
	theta = angle*PI/180.0;
    return theta;
}

/*******************************************************************************
* Function Name  : void Gyro_USART_IRQHandler(void)
* Description    : 串口4中断服务函数
* Input          : None
* Output         : None
* Return         : Angle
* BUG            : NoBug
*******************************************************************************/
void Gyro_USART_IRQHandler(void)
{
	CPU_SR_ALLOC();// 申请cpu_sr

	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
	OSIntEnter(); // 进入中断，中断层数加一
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

	if(USART_GetITStatus(Gyro_USART, USART_IT_RXNE) != RESET )
    {
		USART_ClearFlag(Gyro_USART, USART_FLAG_RXNE);

		// 读取当前字节,将数据存入缓冲区
		Gyro_Buffer[Gyro_RecPointer++] = USART_ReceiveData(Gyro_USART);

		// 如果收到数据在4~40间
		if((Gyro_RecPointer >= 4)&&(Gyro_RecPointer < 40))
		{
			// 如果3个字节前收到帧头，且缓冲区未满
			if((Gyro_Buffer[Gyro_RecPointer-4] == 0xff\
				||Gyro_Buffer[Gyro_RecPointer-4] == 0xfe))
			{
				// 检查校验和
				if((Gyro_Buffer[Gyro_RecPointer-1]&0xff) == \
					((Gyro_Buffer[Gyro_RecPointer-4]\
						+Gyro_Buffer[Gyro_RecPointer-3]\
							+Gyro_Buffer[Gyro_RecPointer-2])\
								&0xff))
				{
					if(Gyro_Buffer[Gyro_RecPointer-4] == 0xff)
						iAngle = (Gyro_Buffer[Gyro_RecPointer-3]<<8)\
									|Gyro_Buffer[Gyro_RecPointer-2];
					if(Gyro_Buffer[Gyro_RecPointer-4] == 0xfe)
						iAngle = -((Gyro_Buffer[Gyro_RecPointer-3]<<8)\
									|Gyro_Buffer[Gyro_RecPointer-2]);
					Angle = ((float)iAngle)/10;
					Theta = TransTheta(Angle);
					
				}
				else
				{}
			}
		}
		// 指针清零操作
		if(Gyro_RecPointer > 39)Gyro_RecPointer = 0;
    }

	OSIntExit(); // 中断层数减一，并进行中断级任务切换
}

#include "includes.h"

#define MAX_MAIL_NUM  3
u8 CAN_msg_num2[MAX_MAIL_NUM];   // 发送邮箱标记

//can接收结构体
CanRxMsg RxMessage2;

void CAN2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	// 打开GPIO时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	// 打开CAN时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,ENABLE);

	// TX、RX的配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_CAN2);

	// CAN参数配置
	CAN_DeInit(CAN2);
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM = DISABLE;// 失能时间出发通信模式
	CAN_InitStructure.CAN_ABOM = ENABLE; // 使能自动离线管理
	CAN_InitStructure.CAN_AWUM = DISABLE;// 失能自动唤醒模式
	CAN_InitStructure.CAN_NART = DISABLE;// 失能自动重传模式
	CAN_InitStructure.CAN_RFLM = DISABLE;// 失能接收FIFO锁定模式
	CAN_InitStructure.CAN_TXFP = DISABLE;// 失能发送FIFO优先级
	#ifdef CAN_DEBUG
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;// CAN工作在回环模式
	#else
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;// CAN工作在正常模式
	#endif

	// 波特率设置
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;// 重新同步跳跃宽度1个时间单位
	CAN_InitStructure.CAN_BS1 = CAN_BS1_10tq;// 时间段1为10个时间单位
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;// 时间段2为1个时间单位
	CAN_InitStructure.CAN_Prescaler = 3;// 分频数3，波特率=42M/((1+10+3)*3)=1M
	CAN_Init(CAN2,&CAN_InitStructure);

	// 报文滤波设置，这样配置所有报文均可接收
	CAN_FilterInitStructure.CAN_FilterNumber = 14;//初始化过滤器14
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;// 标识符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;// 使用一个32位过滤器
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;// 过滤器标示符0x00000000
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;// 过滤器屏蔽标示符0x0000000
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;// 过滤器FIFO0指向过滤器0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;// 使能过滤器
	CAN_FilterInit(&CAN_FilterInitStructure);

	 /* Enable CAN2 RX0 interrupt IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	 /* Enable CAN2 RX1 interrupt IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Enable CAN2 TX0 interrupt IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN2, CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0, ENABLE);  // fifo0中断
    CAN_ITConfig(CAN2, CAN_IT_FMP1 | CAN_IT_FF1 | CAN_IT_FOV1, ENABLE);  // fifo1中断
    CAN_ITConfig(CAN2, CAN_IT_TME, DISABLE);                // 发送中断
    CAN_ITConfig(CAN2, CAN_IT_EWG | CAN_IT_EPV | CAN_IT_BOF | CAN_IT_LEC
                     | CAN_IT_ERR | CAN_IT_WKU | CAN_IT_SLK, ENABLE);  // ERR中断
}


char CAN2_Send_Msg(void)
{
	u16 CAN_ID;
	u8 msg[8];
	if(GetQueue(&CAN2_TX_Queue,&CAN_ID,msg))
	{
		CanTxMsg TxMessage;
		u8 mbox;
		u32 i=0;

		TxMessage.StdId = CAN_ID;	// 标准标识符
		TxMessage.ExtId = 0x00000000;	// 设置扩展标示符（29位）
		TxMessage.IDE = CAN_ID_STD;		// 使用标准标识符
		TxMessage.RTR = CAN_RTR_DATA;	// 消息类型为数据帧，一帧8位
		TxMessage.DLC = 8;			// 发送信息的长度
		for(i = 0;i < 8;i++)
			TxMessage.Data[i] = msg[i];


		// 等待一个空的CAN发送邮箱
		while(((CAN2->TSR&CAN_TSR_TME0) != CAN_TSR_TME0)\
			&&((CAN2->TSR&CAN_TSR_TME1) != CAN_TSR_TME1)\
			&&((CAN2->TSR&CAN_TSR_TME1) != CAN_TSR_TME1));

		mbox = CAN_Transmit(CAN2,&TxMessage);

		CPU_SR_ALLOC();// 申请cpu_sr
		CPU_CRITICAL_ENTER();
		CAN_msg_num2[mbox] = 1;
		CPU_CRITICAL_EXIT();

		CAN_ITConfig(CAN2, CAN_IT_TME, ENABLE);
	}

	return 0;
}


u8 CAN2_Receive_Msg(char *buf,u8* CAN_ID)
{
	u8 i;
	if(CAN_MessagePending(CAN2,CAN_FIFO0)==0xff)
		return 0;        //没有接收到数据,直接退出
	CAN_Receive(CAN2,CAN_FIFO0, &RxMessage2);//读取数据
	for(i = 0;i < 8;i++)
		buf[i]=RxMessage2.Data[i];
	*CAN_ID = RxMessage2.StdId;
	return RxMessage2.DLC;
}

void CAN2_TX_IRQHandler(void)
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
	OSIntEnter(); // 进入中断，中断层数加一
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

    if(CAN_msg_num2[0])
    {
        if(SET == CAN_GetITStatus(CAN2,CAN_IT_RQCP0))
        {
            CAN_ClearITPendingBit(CAN2,CAN_IT_RQCP0);
            CAN_ITConfig(CAN2, CAN_IT_TME, DISABLE);
            CAN_msg_num2[0] = 0;
        }
    }

    if(CAN_msg_num2[1])
    {
        if(SET == CAN_GetITStatus(CAN2,CAN_IT_RQCP1))
        {
            CAN_ClearITPendingBit(CAN2,CAN_IT_RQCP1);
            CAN_ITConfig(CAN2, CAN_IT_TME, DISABLE);
            CAN_msg_num2[1] = 0;
        }
    }

    if(CAN_msg_num2[2])
    {
        if(SET == CAN_GetITStatus(CAN2,CAN_IT_RQCP2))
        {
            CAN_ClearITPendingBit(CAN2,CAN_IT_RQCP2);
            CAN_ITConfig(CAN2, CAN_IT_TME, DISABLE);
            CAN_msg_num2[2] = 0;
        }
    }
    OSIntExit(); // 中断层数减一，并进行中断级任务切换
}

/*******************************************************************************
函 数 名：CAN2_RX0_IRQHandler(void)
描    述：CAN接收数据中断
*******************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
	CPU_SR_ALLOC();// 申请cpu_sr

	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
	OSIntEnter(); // 进入中断，中断层数加一
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

	if(SET == CAN_GetITStatus(CAN2,CAN_IT_FF0))
   	{
        CAN_ClearITPendingBit(CAN2,CAN_IT_FF0);
   	}
   	else if(SET == CAN_GetITStatus(CAN2,CAN_IT_FOV0))
   	{
        CAN_ClearITPendingBit(CAN2,CAN_IT_FOV0);
   	}
   	else
  	{
        CAN_Receive(CAN2, CAN_FIFO0, &RxMessage2);
		InsertQueue(&CAN2_RX_Queue,RxMessage2.StdId,RxMessage2.Data);
    }

	OSIntExit(); // 中断层数减一，并进行中断级任务切换
}

/*******************************************************************************
函 数 名：CAN2_RX1_IRQHandler(void)
描    述：CAN接收数据中断
*******************************************************************************/
void CAN2_RX1_IRQHandler(void)
{
	CPU_SR_ALLOC();// 申请cpu_sr

	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
	OSIntEnter(); // 进入中断，中断层数加一
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

	if(SET == CAN_GetITStatus(CAN2,CAN_IT_FF1))
   	{
        CAN_ClearITPendingBit(CAN2,CAN_IT_FF1);
   	}
   	else if(SET == CAN_GetITStatus(CAN2,CAN_IT_FOV1))
   	{
        CAN_ClearITPendingBit(CAN2,CAN_IT_FOV1);
   	}
   	else
  	{
        CAN_Receive(CAN2, CAN_FIFO1, &RxMessage2);
		InsertQueue(&CAN2_RX_Queue,RxMessage2.StdId,RxMessage2.Data);
    }

	OSIntExit(); // 中断层数减一，并进行中断级任务切换
}


void CAN2_SCE_IRQHandler(void)
{

}


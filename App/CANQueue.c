
#include "includes.h"

//CAN1与CAN2的四个队列
_CANQUEUE CAN1_TX_Queue;
_CANQUEUE CAN1_RX_Queue;
_CANQUEUE CAN2_TX_Queue;
_CANQUEUE CAN2_RX_Queue;

/*******************************************************************
函数功能: 清除通信队列
********************************************************************/
void ClearQueue(_CANQUEUE* canqueue)
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句	
    int i;

    for(i = 0; i < MAX_CAN_QUEUE_SIZE; i++)
    {
        memset(&canqueue->Elem[i],0,sizeof(_CANMSG));
    }

    canqueue->front = 0;
    canqueue->rear = 0;
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
}
/*******************************************************************
函数功能: 判断CAN队列是否为空
返 回 值: 1: 空; 0:非空
********************************************************************/
u8 IsEmptyQueue(_CANQUEUE* canqueue)
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
    if(canqueue->front == canqueue->rear)
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 1;
    }
    else
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 0;
    }
}
/*******************************************************************
函数功能: 判队列是否满
返 回 值: 1: 满; 0:非满
********************************************************************/
u8 IsFullQueue(_CANQUEUE* canqueue)
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
    if(((MAX_CAN_QUEUE_SIZE - canqueue->front) + canqueue->rear) == (MAX_CAN_QUEUE_SIZE - 1))
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 1;
    }
    else
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 0;
    }
}
/*******************************************************************
函数功能: 将数据插入队列
入口参数: element:被插元素
返 回 值: 1: 成功; 0:失败
********************************************************************/
u8 InsertQueue(_CANQUEUE* canqueue,u16 CAN_ID,u8 Msg[8])
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
    if(!IsFullQueue(canqueue))//是否为满
    {
		_CANMSG CANMsg;
		CANMsg.CAN_ID  = CAN_ID;
		memcpy(CANMsg.Msg,Msg,2*sizeof(Msg));
		memcpy(&canqueue->Elem[canqueue->rear],&CANMsg,sizeof(CANMsg));
		
        canqueue->rear = (canqueue->rear + 1) % MAX_CAN_QUEUE_SIZE;
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 1;
    }
    else                       //队列满
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 0;
    }
}

/*******************************************************************
函数功能: 重新设置队列头指针
入口参数: head: 新头
********************************************************************/
void SetHeadQueue(_CANQUEUE* canqueue,u16 head)
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
    if(canqueue->front != canqueue->rear)
    {
        canqueue->front = head;
    }
	CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

}
/*******************************************************************
函数功能: 取队列中一个元素,fifo
入口参数: *element;数据
返 回 值: 1: 成功 0: 失败
********************************************************************/
u8 GetQueue(_CANQUEUE* canqueue,u16* CAN_ID,u8 Msg[])
{
	CPU_SR_ALLOC();// 申请cpu_sr
	////
	CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
    if(!IsEmptyQueue(canqueue))//队列非空
    {		
		_CANMSG CANMsg;
		memcpy(&CANMsg,&canqueue->Elem[canqueue->front],sizeof(_CANMSG));//得到数据
		
		*CAN_ID  = CANMsg.CAN_ID;
        memcpy(Msg,CANMsg.Msg,sizeof(CANMsg.Msg));//得到数据
		// 队头加一
		canqueue->front = (canqueue->front + 1) % MAX_CAN_QUEUE_SIZE ;
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 1;
    }
    else
    {
		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句
        return 0;                               //无指定对头数据
    }
}
/*******************************************************************
函数功能: can数据处理
********************************************************************/
void Can_data_process(_CANQUEUE* canqueue)
{
//    u16 head;
// //   u32 i;
//    CanRxMsg RxMessage;
//    CanTxMsg TxMessage;
//
//
//    head = CANQueue.front;
//
//    if(1 == GetCanQueue(&RxMessage))
//    {
//        head = (head + 1) % MAX_CAN_SIZE;     //查询头前滚
//        SetHeadCanQueue(head);
//      //  printf("RxMessage.StdId is 0x%x\r\n",RxMessage.StdId);
//      //  printf("RxMessage.DLC is 0x%x\r\n",RxMessage.DLC);
//      //  for(i = 0; i < RxMessage.DLC; i++)
//      //  {
//      //      printf("data[%d] is 0x%x\r\n",i,RxMessage.Data[i]);
//      //  }
//      //  printf("\r\n");
//        // 把接收到的数据发回去
//        /* transmit */
//      //  TxMessage.StdId=RxMessage.StdId;
//        TxMessage.StdId=0x5f1;
//        TxMessage.RTR=RxMessage.RTR;
//        TxMessage.IDE=RxMessage.IDE;
//        TxMessage.DLC=RxMessage.DLC;
//        memcpy(TxMessage.Data,RxMessage.Data,TxMessage.DLC);
//        //Can_Send_Msg(TxMessage);
//
//    }
//    else
//    {
//       // printf("CAN queue is empty\r\n");
//    }



}
#pragma once
#include "includes.h"

#define MAX_CAN_QUEUE_SIZE		256

#define fCAN1	1
#define fCAN2	2


//CAN数据的描述
typedef struct 
{
    u16 CAN_ID;//CAN数据的ID
    u8 Msg[8];
}_CANMSG;

//CAN队列数据类型
typedef struct
{
	_CANMSG Elem[MAX_CAN_QUEUE_SIZE];
	u16 front;
    u16 rear;
}_CANQUEUE;

extern _CANQUEUE CAN1_TX_Queue;
extern _CANQUEUE CAN1_RX_Queue;
extern _CANQUEUE CAN2_TX_Queue;
extern _CANQUEUE CAN2_RX_Queue;

void ClearQueue(_CANQUEUE* canqueue);
u8 IsEmptyQueue(_CANQUEUE* canqueue);
u8 IsFullQueue(_CANQUEUE* canqueue);
u8 InsertQueue(_CANQUEUE* canqueue,u16 CAN_ID,u8 Msg[8]);
void SetHeadQueue(_CANQUEUE* canqueue,u16 head);
u8 GetQueue(_CANQUEUE* canqueue,u16* CAN_ID,u8 Msg[]);
void Can_data_process(_CANQUEUE* canqueue);
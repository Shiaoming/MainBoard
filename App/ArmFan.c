#include "includes.h"

Fan_TypeDef FanCMD;

//结构体初始化
void FanStruct_Init(void)
{
	FanCMD.height = DEFAULT_HIGHT;
	FanCMD.FanSpeed = DEFAULT_SPEED;
	FanCMD.FanDirection = DEFAULT_DIR;
}

//给风扇机械臂发送数据
void Set_Fan(s16 height,s16 FanSpeed,s16 FanDirection)
{
	int CAN2_TX_id = 0x280;
	u8 CAN2_TX_data[8];
	static u8 lastfan[8];
	static u8 countfan=0;

	//范围限制
	RANGE_LIMIT(height,HEIGHT_MIN,HEIGHT_MAX);
	RANGE_LIMIT(FanSpeed,SPEED_MIN,SPEED_MAX);
	RANGE_LIMIT(FanDirection,DIRECTION_MIN,DIRECTION_MAX);
	
	//发送新的数据，重复数据不发送
	for(int i=0;i<8;i++)
	{
		if(lastfan[i]!=CAN2_TX_data[i])
			countfan++;		
	}
	if(countfan)
	{
		InsertQueue(&CAN2_TX_Queue,CAN2_TX_id,CAN2_TX_data);
		CAN2_Send_Msg();
		countfan =0;
		memcpy(lastfan,CAN2_TX_data,8);
	}
			
}
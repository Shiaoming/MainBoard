#include "includes.h"

Fan_TypeDef FanCMD;

u8 lastfan[8];
u8 countfan=0;

void Set_Fan(s16 height,s16 FanSpeed,s16 FanDirection)
{
	int CAN2_TX_id = 0x280;
	u8 CAN2_TX_data[8];

	if(height > HEIGHT_MAX)height = HEIGHT_MAX;
	else if(height < HEIGHT_MIN)height = HEIGHT_MIN;
	
	CAN2_TX_data[0] = 0;CAN2_TX_data[1] = 0;
	CAN2_TX_data[2] = (u8)(height>>8);CAN2_TX_data[3] = (u8)height;
	CAN2_TX_data[4] = (u8)(FanSpeed>>8);CAN2_TX_data[5] = (u8)FanSpeed;
	CAN2_TX_data[6] = (u8)(FanDirection>>8);CAN2_TX_data[7] = (u8)FanDirection;
	
	for(int i=0;i<8;i++)
	{
		if(lastfan[i]!=CAN2_TX_data[i])
		{countfan++;}
		else ;
		
	}
	if(countfan )
	{
		InsertQueue(&CAN2_TX_Queue,CAN2_TX_id,CAN2_TX_data);
		CAN2_Send_Msg();
		countfan =0;
		memcpy(lastfan,CAN2_TX_data,8);
	}
	else;
			
}
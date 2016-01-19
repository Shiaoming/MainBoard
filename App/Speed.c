
#include "includes.h"

SPEEDTypeDef Speed;
RobotWspeed robotw;


u16 can1id = 0;
u8 can1data[8];
u16 can2id = 0x11;
u8 can2data[8];
u8 count_speed = 0;
u8 count_PWM = 0;



u16 can1id_diceng_return = 0x10;                                         //底层板返回ID
u16 can1id_pagan_return = 0x11;                                          //爬杆初返回ID



u16 can1id_speed_diceng_1 = 0x80;        //速度配置 电机 0,1
u16 can1id_speed_diceng_2 = 0xA0;        //速度配置 电机 2,3

u16 can1id_speed_pagan_1 = 0x81;        //速度配置 电机 0,1
u16 can1id_speed_pagan_2 = 0xA1;        //速度配置 电机 2,3

u8 can1data_speed_wheel[8] ;//电机0，电机1
//u8 can1data_speed_wheel_2_3[8] ;//电机2，电机3

u8 lastspeed_1[8];
u8 lastspeed_2[8];
u8 count_1=0;
u8 count_2=0;

u16 can1id_PWM_diceng_1 = 0xC0;       //PWM配置 电机0,1
u16 can1id_PWM_diceng_2 = 0xE0;       //PWM配置 电机2,3

u16 can1id_PWM_pagan_1 = 0xC1;        //速度配置 电机 0,1
u16 can1id_PWM_pagan_2 = 0xE1;        //速度配置 电机 2,3

u8 can1data_PWM_0_1[8] = {1,1,1,1,1,1,1,1 };//电机0，电机1
u8 can1data_PWM_2_3[8] = {1,1,1,1,1,1,1,1 };//电机2，电机3

u8 FLAG ;

/*******************************************************************************
函 数 名：PS_Digital_Mode(void)
描    述：PS的数字模式
*******************************************************************************/
void PS_Digital_Mode(void)
{
	//暂时未用
	if((PS.PS_Data[2] & SLCT) == 0)
        ;
	if((PS.PS_Data[2] & STRT) == 0)
        ;
    
    //上下左右
	if((PS.PS_Data[2] & UP) == 0)
    {
        Speed.vx = VX;
    }
    else if((PS.PS_Data[2] & DOWN) == 0)
    {
        Speed.vx = -VX;
    }
    else
    {
        Speed.vx = 0;
    }
            
	if((PS.PS_Data[2] & RGHT) == 0)
    {
        Speed.vy = -VY;
    }
    else if((PS.PS_Data[2] & LEFT) == 0)
    {
        Speed.vy = VY;
    }
    else
    {
        Speed.vy = 0;
    }

    //旋转
	if((PS.PS_Data[3] & L2) == 0)
    {
        Speed.wz = WZ;
    }
	else if((PS.PS_Data[3] & R2) == 0)
    {
        Speed.wz = -WZ;
    }
    else
    {
        Speed.wz = 0;
    }

        
    //暂时未用
	if((PS.PS_Data[3] & R1) == 0)
	{
		FanCMD.FanDirection --;
		if(FanCMD.FanDirection > DIRECTION_MAX)FanCMD.FanDirection = DIRECTION_MAX;
		else if(FanCMD.FanDirection < DIRECTION_MIN)FanCMD.FanDirection = DIRECTION_MIN;
	}
	if((PS.PS_Data[3] & L1) == 0)
    {
		FanCMD.FanDirection ++;
		if(FanCMD.FanDirection > DIRECTION_MAX)FanCMD.FanDirection = DIRECTION_MAX;
		else if(FanCMD.FanDirection < DIRECTION_MIN)FanCMD.FanDirection = DIRECTION_MIN;
	}
    
    if((PS.PS_Data[3] & Triangle) == 0)
	{
		FanCMD.height ++;
		if(FanCMD.height > HEIGHT_MAX)FanCMD.height = HEIGHT_MAX;
		else if(FanCMD.height < HEIGHT_MIN)FanCMD.height = HEIGHT_MIN;
	}
	else if((PS.PS_Data[3] & Cross) == 0)
	{
		FanCMD.height --;
		if(FanCMD.height > HEIGHT_MAX)FanCMD.height = HEIGHT_MAX;
		else if(FanCMD.height < HEIGHT_MIN)FanCMD.height = HEIGHT_MIN;
	}
	
	
	if((PS.PS_Data[3] & Circular) == 0)
	{
		FanCMD.FanSpeed ++;
		if(FanCMD.FanSpeed > SPEED_MAX)FanCMD.FanSpeed = SPEED_MAX;
		else if(FanCMD.FanSpeed < SPEED_MIN)FanCMD.FanSpeed = SPEED_MIN;
	}
	else if((PS.PS_Data[3] & Square) == 0)
	{
		FanCMD.FanSpeed --;
		if(FanCMD.FanSpeed > SPEED_MAX)FanCMD.FanSpeed = SPEED_MAX;
		else if(FanCMD.FanSpeed < SPEED_MIN)FanCMD.FanSpeed = SPEED_MIN;
	}
}

/*******************************************************************************
函 数 名：PS_Analog_Red(void)
描    述：PS的模拟红灯模式
*******************************************************************************/
void PS_Analog_Red(void)
{
	char D2 = 0;
	if((PS.PS_Data[2] & SLCT) == 0)
      D2 = 1;
//		printf("SLCT DOWN!\n");
	if((PS.PS_Data[2] & STRT) == 0)
      D2 = 1;
//		printf("STRT DOWN!\n");
	if((PS.PS_Data[2] & UP) == 0)
      D2 = 1;
//		printf("UP DOWN!\n");
	if((PS.PS_Data[2] & RGHT) == 0)
      D2 = 1;
//		printf("RGHT DOWN!\n");
	if((PS.PS_Data[2] & DOWN) == 0)
      D2 = 1;
//		printf("DOWN DOWN!\n");
	if((PS.PS_Data[2] & LEFT) == 0)
      D2 = 1;
//		printf("LEFT DOWN!\n");

	if((PS.PS_Data[3] & L2) == 0)
      D2 = 1;
//		printf("L2 DOWN!\n");
	if((PS.PS_Data[3] & R2) == 0)
      D2 = 1;
//		printf("R2 DOWN!\n");
	if((PS.PS_Data[3] & R1) == 0)
	  D2 = 1;
//		printf("R1 DOWN!\n");
	if((PS.PS_Data[3] & L1) == 0)
		D2 = 1;
//		printf("L1 DOWN!\n");
	if((PS.PS_Data[3] & Triangle) == 0)
		D2 = 1;
//		printf("Triangle DOWN!\n");
	if((PS.PS_Data[3] & Circular) == 0)
		D2 = 1;
//		printf("Circular DOWN!\n");
	if((PS.PS_Data[3] & Cross) == 0)
		D2 = 1;
//		printf("Cross DOWN!\n");
	if((PS.PS_Data[3] & Square) == 0)
		D2 = 1;
//		printf("Square DOWN!\n");

	if(D2)
		;//LED1_ON();
	else
		;//LED1_OFF();
}

void WSpeed(float vx, float vy,float wz)    //麦克纳姆轮运动方程
{  
  robotw.speed0=(s32)(((vx-vy)+(LL1+LL2)*wz/550)/PI/R/2*1000);//0
  robotw.speed1=(s32)((-(vx+vy)+(LL1+LL2)*wz/550)/PI/R/2*1000);//1
  robotw.speed2=(s32)(((vx-vy)-(LL1+LL2)*wz/550)/PI/R/2*1000);//2
  robotw.speed3=(s32)((-(vx+vy)-(LL1+LL2)*wz/550)/PI/R/2*1000);//3
  
  if(robotw.speed0 > MAX_WHELL_SPEED)robotw.speed0 = MAX_WHELL_SPEED;
  else if(robotw.speed0 < -MAX_WHELL_SPEED)robotw.speed0 = -MAX_WHELL_SPEED;
  
  if(robotw.speed1 > MAX_WHELL_SPEED)robotw.speed1 = MAX_WHELL_SPEED;
  else if(robotw.speed1 < -MAX_WHELL_SPEED)robotw.speed1 = -MAX_WHELL_SPEED;
  
  if(robotw.speed2 > MAX_WHELL_SPEED)robotw.speed2 = MAX_WHELL_SPEED;
  else if(robotw.speed2 < -MAX_WHELL_SPEED)robotw.speed2 = -MAX_WHELL_SPEED;
  
  if(robotw.speed3 > MAX_WHELL_SPEED)robotw.speed3 = MAX_WHELL_SPEED;
  else if(robotw.speed3 < -MAX_WHELL_SPEED)robotw.speed3 = -MAX_WHELL_SPEED;
  
}

void Set_Speed(void)
{
    WSpeed(Speed.vx,Speed.vy,Speed.wz);
    
    
    
    can1data_speed_wheel[0] = robotw.speed0 >> 8;
    can1data_speed_wheel[1] = robotw.speed0 ;
    can1data_speed_wheel[2] = robotw.speed1 >> 8;
    can1data_speed_wheel[3] = robotw.speed1;
    can1data_speed_wheel[4] = robotw.speed2 >> 8;
    can1data_speed_wheel[5] = robotw.speed2;
    can1data_speed_wheel[6] = robotw.speed3 >> 8;
    can1data_speed_wheel[7] = robotw.speed3;
    
//    can1data_speed_wheel_2_3[0] = robotw.speed2 >> 24;
//    can1data_speed_wheel_2_3[1] = robotw.speed2 >> 16;
//    can1data_speed_wheel_2_3[2] = robotw.speed2 >> 8;
//    can1data_speed_wheel_2_3[3] = robotw.speed2;
//    can1data_speed_wheel_2_3[4] = robotw.speed3 >> 24;
//    can1data_speed_wheel_2_3[5] = robotw.speed3 >> 16;
//    can1data_speed_wheel_2_3[6] = robotw.speed3 >> 8;
//    can1data_speed_wheel_2_3[7] = robotw.speed3;
    

    
    if(!IsEmptyQueue(&CAN2_RX_Queue))
    {
        
        
        GetQueue(&CAN2_RX_Queue,&can1id,can1data);
        FLAG =1;
        if( (can1id == can1id_diceng_return )||(FLAG ==1 ))
        {    
            for ( int i=0;i<8;i++ )
            {
                if( can1data[i] == 0x55 ) 
                { 
                    count_speed++;
                }   
                else if( can1data[i] == 0xAA ) 
                { 
                    count_PWM++;
                } 
                else if( can1data[i] == 0 )
                {
                    break;
                }
                else ;
            }
        }
    }
        if(FLAG == 1)
        {
           // OS_ERR err;
            
             
            for(int i=0;i<8;i++)
            {
                if(lastspeed_1[i]!=can1data_speed_wheel[i])
                {count_1++;}
                else ;
                
            }
            if(count_1 )
            {
                InsertQueue(&CAN2_TX_Queue,can1id_speed_diceng_1,can1data_speed_wheel);
                CAN2_Send_Msg();
                count_1 =0;
                memcpy(lastspeed_1,can1data_speed_wheel,8);
            }
            else;
            
            
           // OSTimeDly(100,OS_OPT_TIME_MATCH,&err);
            
//            for(int i=0;i<8;i++)
//            {
//                if(lastspeed_2[i]!=can1data_speed_wheel_2_3[i])
//                {count_2++;}
//                else ;
//                
//            }
//            if(count_2)
//            {
//                InsertQueue(&CAN2_TX_Queue,can1id_speed_diceng_2,can1data_speed_wheel_2_3);
//                CAN2_Send_Msg();
//                count_2 =0;
//                memcpy(lastspeed_2,can1data_speed_wheel_2_3,8);
//            }
//            else;
            count_speed = 0;
        }
        else ;
//        if(count_PWM == 8)
//        {
//            InsertQueue(&CAN2_TX_Queue,can1id_PWM_diceng_1,can1data_PWM_0_1); 
//            CAN2_Send_Msg();
//            InsertQueue(&CAN2_TX_Queue,can1id_PWM_diceng_2,can1data_PWM_2_3); 
//            CAN2_Send_Msg();
//            count_PWM =0 ;
//        }
//        else ;
        
    
}

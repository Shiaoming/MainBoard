
#include "includes.h"

float infrared_data1;
float infrared_data2;
float infrared_data3;
double distance1 ;
double distance2 ;
double fanheight ;
double ave_distance ;
double xielv ;

void Avoid_Confict(void)
{
	infrared_data1 = Get_Adc_Average(0);  
	infrared_data2 = Get_Adc_Average(1);

	distance1 = -17.59*log(infrared_data1)+ 146.48;
	distance2 = -15.95*log(infrared_data2)+ 134.42;


	infrared_data3 = Get_Adc_Average(2);   //风扇机械臂红外数据

	fanheight = -15.95*log(infrared_data3)+ 134.42;                             //最佳离跑道高度15
		
	ave_distance = (distance1+distance2)/2.0 ;

	xielv = (distance1-distance2)/50.0;    //底盘机器人红外安装间距50mm

	if(ave_distance<25)
	{
		if(ave_distance<10)
		{
			Speed.vy = -20;

		}
		else if(ave_distance>15)
		{
				
			Speed.vy = 20;
		}
		else 
		{
			Speed.vy = 0;
		}
		
		if(xielv<0)
		{
			Speed.wz = -5;

		}
		else if(xielv>0)
		{
				
			Speed.wz = 5;
		}
		else 
		{
			Speed.wz = 0;
		}	
	}
	else
	{
		Speed.vy = 0;
		Speed.wz = 0;
		
	}	
}
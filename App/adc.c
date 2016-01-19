#include "adc.h"

	


#define ADC1_DR_Address  ((uint32_t)0X4001204C)

#define  N   20      //每通道采20次 
#define  M  3      //为2个通道   
vu16  AD_Value[N][M];   //用来存放ADC转换结果，也是DMA的目标地址

void ADC_Configuration(void)

{    
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
    DMA_InitTypeDef       DMA_InitStructure;
    
	ADC_InitTypeDef       ADC_InitStructure;
	
	
	
	//①开启ADC和GPIO相关时钟和初始化GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_DMA2, ENABLE);//使能GPIOA时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG |RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	
	
	
	//先初始化ADC1通道10-13 IO口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PC0-3 通道11-14
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 
	
	
	
	// RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);        //ADC1复位
	
    // RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);     //复位结束    
	
	
	
	//②初始化通用配置
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =
		
		ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
		
		//ADC_DMAAccessMode_Disabled; //DMA失能
	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。
	
	//ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
	
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	
	DMA_InitStructure.DMA_BufferSize = N*M;
    
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&AD_Value;   //目标数据位
    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//DMA_MemoryInc_Enable
    
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    
    DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)ADC1_DR_Address;  //ADC->DR地址
    
    DMA_InitStructure.DMA_PeripheralBurst =DMA_PeripheralBurst_Single;
    
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(DMA2_Stream0,&DMA_InitStructure);
    
    DMA_Cmd(DMA2_Stream0,ENABLE);
    
	//③初始化ADC1相关参数
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	
	ADC_InitStructure.ADC_ScanConvMode =  ENABLE;   //DISABLE;//非扫描模式  //多通道模式使能
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//关闭连续转换
	
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	
	//禁止触发检测，使用软件触发
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐      
	
	ADC_InitStructure.ADC_NbrOfConversion = 3;//2个转换在规则序列中
	
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
    
    
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_480Cycles);
    
    ADC_RegularChannelConfig(ADC1,ADC_Channel_12,2,ADC_SampleTime_480Cycles);
	
    ADC_RegularChannelConfig(ADC1,ADC_Channel_13,3,ADC_SampleTime_480Cycles);
	
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);  //if not have this function , can't get new value
     
    ADC_DMACmd(ADC1, ENABLE);  //make enable ADC1 WITH DMA2 
    //④开启ADC转换
    
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器  
    
    
    ADC_SoftwareStartConv(ADC1);         //使能指定的ADC1的软件转换启动功能
  
    
    
	
	
	
}                         
//获得ADC值

//ch:通道值 0~16: ch: @ref ADC_channels

//返回值:转换结果
//u16 Get_Adc(u8 ch)  
//
//{
//	
//	//设置指定ADC的规则组通道，一个序列，采样时间
//
//	
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);              
//	
//	ADC_SoftwareStartConv(ADC1);         //使能指定的ADC1的软件转换启动功能 
//	
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
//	
//	return ADC_GetConversionValue(ADC1);     //返回最近一次ADC1规则组的转换结果
//	
//}
u32 temp_val[20];

u16 Get_Adc_Average(u8 ch)
{
	
    u32 temp;
    u16 minAverage;
	u8 t;
	for(t=0;t<20;t++)
	{
		temp_val[t]=AD_Value[t][ch]*3300/4096;
      //  delay_us(5000);
        
	}
    for(t=0;t<20;t++)
    {
      temp=temp_val[t];
      for(int j=t+1;j<20;j++)
      {
        if(temp>temp_val[j])
      {
        temp_val[t] = temp_val[j]; 
        temp_val[j] = temp;
       // temp = temp_val[j];
         
        
      }
      else ;
      }
      
    }
    
    for (t=5;t<10;t++)
    {
      minAverage+=temp_val[t];
    }
	return (minAverage/5);
} 	 


//void delay_us(u32 us) 
//{
//	u32 temp;
//      
//	SysTick_Config(us*21);
//	do
//    
//	{
//	   
//		temp = SysTick->CTRL;  //时间到了之后,该位将被硬件置1,但被查询后自动清0
//    
//	}
//    
//	while(temp & 0x01 && !(temp &(1<<16))); //查询
//    
//	SysTick->CTRL = 0x00;  //关闭计数器
//    
//	SysTick->VAL = 0x00;   //清空val
//}











/**
  ******************************************************************************
  * @文件	stm32f4xx_conf.h
  * @日期	2015-2-9
  * @说明	配置外设的使用，需要使用某一个外设时，到此文件中取消其注释
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  * 功能描述：
  *           配置外设的使用，需要使用某一个外设时，到此文件中取消其注释
  ******************************************************************************
  */
#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

// 晶振频率
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000) /*!< 外部晶振频率，单位Hz */
#endif

#define _ADC
#define _CAN
//#define _CRC
//#define _CRYP
//#define _DAC
//#define _DBGMCU
//#define _DCMI
#define _DMA
//#define _EXTI
//#define _FLASH
//#define _FSMC
#define _GPIO
//#define _HASH
//#define _I2C
//#define _IWDG
//#define _PWR
#define _RCC
//#define _RNG
//#define _RTC
//#define _SDIO
//#define _SPI
//#define  _SYSCFG
//#define _SysTick
//#define _TIM
#define _USART
//#define _WWDG

#ifdef _ADC
 	#include "stm32f4xx_adc.h"
#endif
#ifdef _CRC
 	#include "stm32f4xx_crc.h"
#endif
#ifdef _DBGMCU
 	#include "stm32f4xx_dbgmcu.h"
#endif
#ifdef _DMA
 	#include "stm32f4xx_dma.h"
#endif
#ifdef _EXTI
 	#include "stm32f4xx_exti.h"
#endif
#ifdef _FLASH
 	#include "stm32f4xx_flash.h"
#endif
#ifdef _GPIO
 	#include "stm32f4xx_gpio.h"
#endif
#ifdef _I2C
 	#include "stm32f4xx_i2c.h"
#endif
#ifdef _IWDG
 	#include "stm32f4xx_iwdg.h"
#endif
#ifdef _PWR
 	#include "stm32f4xx_pwr.h"
#endif
#ifdef _RCC
 	#include "stm32f4xx_rcc.h"
#endif
#ifdef _RTC
 	#include "stm32f4xx_rtc.h"
#endif
#ifdef _SDIO
 	#include "stm32f4xx_sdio.h"
#endif
#ifdef _SPI
 	#include "stm32f4xx_spi.h"
#endif
#ifdef _SYSCFG
 	#include "stm32f4xx_syscfg.h"
#endif
#ifdef _TIM
 	#include "stm32f4xx_tim.h"
#endif
#ifdef _USART
 	#include "stm32f4xx_usart.h"
#endif
#ifdef _WWDG
 	#include "stm32f4xx_wwdg.h"
#endif
#include "misc.h" 

#if defined (STM32F429_439xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_ltdc.h"
#include "stm32f4xx_sai.h"
#endif 

#if defined (STM32F427_437xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_sai.h"
#endif 

#if defined (STM32F40_41xxx)
#ifdef _CRYP
 	#include "stm32f4xx_cryp.h"
#endif
#ifdef _HASH
 	#include "stm32f4xx_hash.h"
#endif
#ifdef _RNG
 	#include "stm32f4xx_rng.h"
#endif
#ifdef _CAN
 	#include "stm32f4xx_can.h"
#endif
#ifdef _DAC
 	#include "stm32f4xx_dac.h"
#endif
#ifdef _DCMI
 	#include "stm32f4xx_dcmi.h"
#endif
#ifdef _FSMC
 	#include "stm32f4xx_fsmc.h"
#endif
#endif 



/* 如果使用外部时钟，下面的值应与外部时钟一样；否则，保持其注释不变 */
//#define I2S_EXTERNAL_CLOCK_VAL   12288000  // 单位Hz


//断言失能，在标准库的实现中均含有断言，因此使用标准库可以使能断言。
//其中，assert_failed函数要自己实现
#define USE_FULL_ASSERT    0 


#if USE_FULL_ASSERT

/**
  * @说明  断言宏是用来判断参数的合法性
  * @参数  expr: 	expr为假，断言失败，返回文件名和对应行数 
  * 				expr为真，断言成功
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif

#endif


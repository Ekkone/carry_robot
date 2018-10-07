/**
  ******************************************************************************
  * @file    bsp_SysTick.c   
  * @brief   SysTick 系统滴答时钟1us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  */
 
#include "./SysTick/bsp_SysTick.h"


volatile uint32_t g_ul_us_ticks=0;//DMP，用于获取系统时间

static __IO u32 TimingDelay;


/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick,1us中断一次
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次,使用这个中断频率下载程序后没反应，不知道什么原因
	 */
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}


/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,1us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1 * 1us = 1us 
 */

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime/10;	
	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay != 0);
}

/*
 * 函数名：Delay_ms
 * 描述  ：ms延时程序,1ms为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_ms( 1 ) 则实现的延时为 1 * 1ms = 1ms 
 */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = 100*nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}


/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */  
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay--;
	}
}

//////////////////////////////////////////////////DMP//////////////////////////////////////////////////////////

int get_tick_count(unsigned long *count)
{
        count[0] = g_ul_us_ticks*10;
	return 0;
}

void TimeStamp_Increment(void)
{
	g_ul_us_ticks++;
}

/*********************************************END OF FILE**********************/

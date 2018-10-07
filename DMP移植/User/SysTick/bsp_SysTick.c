/**
  ******************************************************************************
  * @file    bsp_SysTick.c   
  * @brief   SysTick ϵͳ�δ�ʱ��1us�жϺ�����,�ж�ʱ����������ã�
  *          ���õ��� 1us 10us 1ms �жϡ�     
  ******************************************************************************
  */
 
#include "./SysTick/bsp_SysTick.h"


volatile uint32_t g_ul_us_ticks=0;//DMP�����ڻ�ȡϵͳʱ��

static __IO u32 TimingDelay;


/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick,1us�ж�һ��
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��,ʹ������ж�Ƶ�����س����û��Ӧ����֪��ʲôԭ��
	 */
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
		// �رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}


/*
 * ��������Delay_us
 * ����  ��us��ʱ����,1usΪһ����λ
 * ����  ��- nTime
 * ���  ����
 * ����  ��Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1us = 1us 
 */

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime/10;	
	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay != 0);
}

/*
 * ��������Delay_ms
 * ����  ��ms��ʱ����,1msΪһ����λ
 * ����  ��- nTime
 * ���  ����
 * ����  ��Delay_ms( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1ms = 1ms 
 */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = 100*nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}


/*
 * ��������TimingDelay_Decrement
 * ����  ����ȡ���ĳ���
 * ����  ����
 * ���  ����
 * ����  ���� SysTick �жϺ��� SysTick_Handler()����
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

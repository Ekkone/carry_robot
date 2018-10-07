#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
void Delay_ms(__IO u32 nTime);
void TimingDelay_Decrement(void);
////////////////////////////DMP//////////////////////////////
int get_tick_count(unsigned long *count);
uint32_t GetSysTime_us(void);
void TimeStamp_Increment(void);

//void Cycle_Time_Init();
u32 Get_Cycle_T(u8 item);

#endif /* __SYSTICK_H */

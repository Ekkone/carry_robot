#include "./SysTick/Delay.h"

//vu32 TimingDelay=0;

//void TimingDelay_Decrement(void)
//{
//	if(TimingDelay!=0x00)
//		TimingDelay--;
//}

//void Delay_us(vu32 nus)
//{
//	TimingDelay=nus/10;
//	while(TimingDelay!=0);
//}

//void Delay_ms(vu32 nms)
//{
//	//TimingDelay=100*nms;
//	TimingDelay=nms;
//	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
//	while(TimingDelay!=0);
//}

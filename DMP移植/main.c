#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./DMP/DMP.h"
#include "./SysTick/bsp_SysTick.h"
#include "./usart/bsp_usart.h"
#include "./usart/send_data_to_ano.h"
#include "./i2c/bsp_i2c.h"
#include "./exti/bsp_exti.h"
#include "./led/bsp_led.h"

u8 NewGyro=0;//MPU6050数据知否准备好，1表示有新数据，0表示没有新数据

int main(void)
{
   
    SysTick_Init();//系统时钟初始化
//    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
//    LED_Init();
    USART_Config();	//串口初始化
    EXTI_Pxy_Config();  //MPU6050外部中断初始化
    I2C_Bus_Init();//模拟iic初始化
    DMP_Init(); 	//初始化DMP 
//    LED_BLUE;
    while(1)
    {
        Read_DMP();
    }
    
}

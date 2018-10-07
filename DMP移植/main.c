#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./DMP/DMP.h"
#include "./SysTick/bsp_SysTick.h"
#include "./usart/bsp_usart.h"
#include "./usart/send_data_to_ano.h"
#include "./i2c/bsp_i2c.h"
#include "./exti/bsp_exti.h"
#include "./led/bsp_led.h"

u8 NewGyro=0;//MPU6050����֪��׼���ã�1��ʾ�������ݣ�0��ʾû��������

int main(void)
{
   
    SysTick_Init();//ϵͳʱ�ӳ�ʼ��
//    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
//    LED_Init();
    USART_Config();	//���ڳ�ʼ��
    EXTI_Pxy_Config();  //MPU6050�ⲿ�жϳ�ʼ��
    I2C_Bus_Init();//ģ��iic��ʼ��
    DMP_Init(); 	//��ʼ��DMP 
//    LED_BLUE;
    while(1)
    {
        Read_DMP();
    }
    
}

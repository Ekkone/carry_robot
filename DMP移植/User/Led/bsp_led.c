/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  
  * @version V1.0
  * @date    2017-07-25
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"
#include "./SysTick/bsp_SysTick.h"

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_Init(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		/* �ر�����led��	*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
		
		/* �ر�����led��	*/
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	 
    
    /* �ر�����led��	*/
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}

void LED1_FLASH(void)
{
	u8 i;
	for(i=0;i<10;i++)
    {
        LED1(0);
        Delay_ms(40);
        LED1(1);
        Delay_ms(40);
    }
}

void LED2_FLASH(void)
{
	u8 i;
	for(i=0;i<10;i++)
    {
        LED2(0);
        Delay_ms(40);
        LED2(1);
        Delay_ms(40);
    }
}

void LED3_FLASH(void)
{
    u8 i;
	for(i=0;i<10;i++)
    {
        LED3(0);
        Delay_ms(40);
        LED3(1);
        Delay_ms(40);
    }
}

void LED_ALL_FLASH(void)
{
   u8 i;
	 for(i=0;i<10;i++)
    {
        LED1(0);
        LED2(0);
        LED3(0);
        Delay_ms(40);
		LED1(1);
        LED2(1);
		LED3(1);
        Delay_ms(40);
    }
}

/*********************************************END OF FILE**********************/

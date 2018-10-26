/*************************************************************************************
*	@file			bsp.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "bsp.h"

/* Private function prototypes -----------------------------------------------*/

void BSP_Init(void)
{
  LED_Init();
  ROC_LCD_Init();
  HAL_UART_Receive_IT(&huart1,Pixy_Temp,1);   //��PIXY���ݽ����ж�
  HAL_UART_Receive_IT(&huart4,&Laser_buff,1);   //�򿪼��������ݽ����ж�
//  HAL_UART_Receive_IT(&huart5,ch,7);  //AX-12A���ݽ����ж�
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


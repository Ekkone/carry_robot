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
  HAL_UART_Receive_IT(&huart1,Pixy_Temp,1);   //打开PIXY数据接受中断
  HAL_UART_Receive_IT(&huart4,&buff,1);   //打开激光测距数据接受中断
  HAL_UART_Receive_IT(&huart5,ch,10);  //AX-12A数据接受中断
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


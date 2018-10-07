/*************************************************************************************
*	@file			radar.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/10/3
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "radar.h"

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
volatile ReplyTypedef  reply_message;
/* Internal variables --------------------------------------------------------*/
uint8_t radar_temp[20] = {0};
uint16_t DISTANCE[360] = {0};
/* Private function prototypes -----------------------------------------------*/

void Send_Request(void)
{
  uint16_t message;
  AskTypedef    ask_message;
  ask_message.begin_flag = BEGIN_FLAG_1;
  ask_message.command    = SCAN;
  
  message = ask_message.begin_flag << 8 | ask_message.command;
  HAL_UART_Transmit(&huart1,&ask_message.begin_flag,1,10);
  HAL_UART_Transmit(&huart1,&ask_message.command,1,10);
}

void RADAR_IRQHandler(void)
{
  uint16_t angle;
  uint16_t distance;
  uint8_t count = 0;
  do count++;
  while (radar_temp[count] == 0xa5 && radar_temp[count + 1] == 0x5a);
  angle = (radar_temp[count + 4] << 8) | (radar_temp[count + 3] >> 1);
  distance = (radar_temp[count + 6] << 8) | (radar_temp[count + 5]);
  
  DISTANCE [angle] = distance;
  
  HAL_UART_Receive_IT(&huart1,radar_temp,20);
}













/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


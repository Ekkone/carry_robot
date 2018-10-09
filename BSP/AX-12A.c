/*************************************************************************************
*	@file			AX12-A.c
* @author	 	
*	@version 	V1.0
*	@date			2018/10/8
* @brief		数字总线舵机驱动程序
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "AX-12A.h"
/* External variables --------------------------------------------------------------*/
extern UART_HandleTypeDef huart5;

/* Internal variables --------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------------*/
/**
  * @} 给指定id的电机的指定地址写参数
  */
void Write_AX(uint8_t id,uint16_t adress,uint16_t data,UART_HandleTypeDef *huart)
{
  AX_TxMsgTypeDef transmit;
  uint8_t *num =  (uint8_t *)&transmit;
  uint8_t  sum = 0;
  
  transmit.begin_1        = BEGIN;
  transmit.begin_2        = BEGIN;
  transmit.ID             = id;
  transmit.LENGTH         = 5;
  transmit.INSTRUCTION    = 0x03;
  transmit.PARAMETER[0]   = adress;
  transmit.PARAMETER[1]   = data >> 8;
  transmit.PARAMETER[2]   = data;
  
  for(uint8_t i = 2;i < 9;i++)
  { 
    sum += num[i];
  }
    
  transmit.CHECK_SUM  = ~sum;

  HAL_UART_Transmit(huart,(uint8_t*)&transmit,9,10);
  
}

/**
  * @} 给指定id的电机设定转动速度和目标位置
  */
void Set_AX(uint8_t id,uint16_t speed,uint16_t position)
{
  
  Write_AX(id,0x1e,position * 3.413,&huart5);
  Write_AX(id,0x20,speed,&huart5);
  
}
















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


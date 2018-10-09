/*************************************************************************************
*	@file			AX12-A.h
* @author	 	
*	@version 	V1.0
*	@date			2018/10/8
* @brief		�������߶����������
*************************************************************************************/
#ifndef __ax12_a_h
#define __ax12_a_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private function prototypes -----------------------------------------------------*/
#define BEGIN 0XFF

typedef enum
{
  LEFT_ID  = 0x1,
  RIGHT_ID = 0x2,
  HAND_ID  = 0x3
}AX_ID;

typedef struct
{
  uint8_t begin_1;
  uint8_t begin_2;
  uint8_t ID;
  uint8_t LENGTH;
  uint8_t INSTRUCTION;
  uint8_t PARAMETER[3];
  uint8_t CHECK_SUM;
  
}AX_TxMsgTypeDef;

typedef struct
{
  uint8_t begin_1;
  uint8_t begin_2;
  uint8_t ID;
  uint8_t LENGTH;
  uint8_t ERROR;
  uint8_t PARAMETER[10];
  uint8_t CHECK_SUM;
  
}AX_RxMsgTypeDef;



void Set_AX(uint8_t id,uint16_t speed,uint16_t position);
void Write_AX(uint8_t id,uint16_t adress,uint16_t data,UART_HandleTypeDef *huart);







#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


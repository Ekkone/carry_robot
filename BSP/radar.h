/*************************************************************************************
*	@file			radar.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/10/3
* @brief		NONE
*************************************************************************************/
#ifndef __radar_h
#define __radar_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types -----------------------------------------------------------------*/
#define BEGIN_FLAG_1 0XA5
#define BEGIN_FLAG_2 0X5A

typedef enum 
{
  STOP           = 0X25U,
  RRESET         = 0X40U,
  SCAN           = 0X20U,
  EXPRESS_SCAN   = 0X82U,      //需要包含5个字节的负载数据：0(working mode):0,1-4(Reserved):0
  FORCE_SCAN     = 0X21U,
  GET_INFO       = 0X50U,
  GET_HEALTH     = 0X52U,
  GET_SAMPLERATE = 0X59U
}CommandTypedef;

typedef struct
{
  uint8_t        begin_flag;
  uint8_t        command;
  uint8_t        data[20];
  uint8_t        crc;
  
}AskTypedef;

typedef struct
{
  uint8_t  begin_flag_1;
  uint8_t  begin_flag_2;
  uint32_t message:30;
  uint32_t mode:2;
  uint8_t style:1;
  
}ReplyTypedef;

/* Private function prototypes ---------------------------------------------------*/

void Send_Request(void);
void RADAR_IRQHandler(void);









#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

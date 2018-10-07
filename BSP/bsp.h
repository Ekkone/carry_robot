/*************************************************************************************
*	@file			bsp.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __bsp_h
#define __bsp_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "rbc_lcd.h"
#include "gpio.h"

/* Private function prototypes ---------------------------------------------------*/
extern uint8_t Pixy_Temp[18];
extern uint8_t RePixy_buf[18],Re_Counter;
extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart4;
extern uint8_t Laser_buff[20];    //»º´æ
extern uint8_t buff;

void BSP_Init(void);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


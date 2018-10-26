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
#include "Pixy_Camera.h"

/* Private function prototypes ---------------------------------------------------*/
extern UART_HandleTypeDef huart1;
/*激光参数*/
extern UART_HandleTypeDef huart4;
extern uint8_t Laser_buff;    //缓存
/*AX-12A参数*/
extern UART_HandleTypeDef huart5;
extern uint8_t ch[20];

void BSP_Init(void);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


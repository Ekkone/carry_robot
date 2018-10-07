/*************************************************************************************
*	@file			fuzzy_pid.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/10/7
* @brief		NONE
*************************************************************************************/
#ifndef __fuzzy_pid_h
#define __fuzzy_pid_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "math.h"
/* Private function prototypes ---------------------------------------------------*/


float FUZZY_Calc_Kp(float e,float ec,float e_max,float ec_max,float fuzzy_max);
float FUZZY_Calc_Ki(float e,float ec,float e_max,float ec_max,float fuzzy_max);
float FUZZY_Calc_Kd(float e,float ec,float e_max,float ec_max,float fuzzy_max);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


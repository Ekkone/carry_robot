/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "test_task.h"

/* External variables --------------------------------------------------------*/

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Test_Task(void const * argument)
{
  for(;;)
  {
//    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);
    
    osDelay(500);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

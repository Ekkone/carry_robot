/*************************************************************************************
*	@file			display_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "display_task.h"

/* External variables --------------------------------------------------------*/

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument)
{
  uint8_t string[]="hello world";
  for(;;)
  {
    //LCD_set_XY(6,6);
    //LCD_Display_float(1.11f,10,1);
    //LCD_write_char('C');
    LCD_Write_string(string,0,0);
    osDelay(5);
  }
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


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
extern Pixy_Color Pixy;
extern uint8_t RePixy_buf[18];
extern float Distance;				       //æ‡¿Î
/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument)
{
  
  for(;;)
  {
    Pixy_Camera_Data();
    LCD_Display_float(Pixy.Pixy_Color_Sig,1,1);
    LCD_Display_float(Pixy.Pixy_Color_PosX,1,2);
    LCD_Display_float(Pixy.Pixy_Color_PosY,1,3);
    LCD_Display_int(Distance,1,4);
//    LCD_Display_int(Pixy.Pixy_Color_Height,1,5);
//    LCD_Display_int(RePixy_buf[0],1,1);
//    LCD_Display_int(RePixy_buf[1],1,2);
//    LCD_Display_int(RePixy_buf[2],1,3);
//    LCD_Display_int(RePixy_buf[3],1,4);
//    LCD_Display_int(RePixy_buf[4],1,5);
//    LCD_Display_int(RePixy_buf[5],1,6);
    osDelay(5);
  }
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


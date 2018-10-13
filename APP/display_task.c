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
  AX_Init();
  for(;;)
  {
//    Pixy_Camera_Data();
//    LCD_Display_float(Pixy.Pixy_Color_Sig,1,1);
//    LCD_Display_float(Pixy.Pixy_Color_PosX,1,2);
//    LCD_Display_float(Pixy.Pixy_Color_PosY,1,3);
//    LCD_Display_int(angle * 0.293,1,1);
    
    Set_AX11(0x3ff,1024,1);


    


     osDelay(5);
  }
  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


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
  AX_Init();
	
	
	//单位：角度：限制角度0~300
	//      RPM：最大转速114RPM
	float servo[7][6] = {
					{100,100,100,100,100,50},//稳定姿态
					{100,100,100,100,100,50},//抓取物块
					{100,100,100,100,100,50},//放下物块
					{100,100,100,100,100,50},//中间姿态
					{100,100,100,100,100,50},//放开爪子
					{100,100,100,100,100,50},//抓紧爪子
					{100,100,100,100,100,50},//预留姿态
					};
	servo_set(servo);
					
  for(;;)
  {
    LCD_Display_float(Pixy.Pixy_Color_Sig,1,1);
    LCD_Display_float(Pixy.Pixy_Color_PosX,1,2);
    LCD_Display_float(Pixy.Pixy_Color_PosY,1,3);
    
    
    printf("sign:%d\n",Pixy.Pixy_Color_Sig);
    printf("x:%d\n",Pixy.Pixy_Color_PosX);
    printf("y:%d\n",Pixy.Pixy_Color_PosY);

    //LCD_Display_int(angle * 0.293,1,1);
		
//    Set_AX14(0x0,0xff);
//    Set_AX11(0x0,0x3ff);


//		 StablePose();	//0

     osDelay(5);
  }
  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


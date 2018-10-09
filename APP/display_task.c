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
extern float Distance;				       //距离
extern AX_RxMsgTypeDef receive;  //接受结构体

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument)
{
  


//    taskEXIT_CRITICAL();	//退出临界段

  HAL_Delay(100);
  int num = 0;
  uint8_t re[11];
  uint8_t cc[11];
  for(;;)
  {
//    Pixy_Camera_Data();
//    LCD_Display_float(Pixy.Pixy_Color_Sig,1,1);
//    LCD_Display_float(Pixy.Pixy_Color_PosX,1,2);
//    LCD_Display_float(Pixy.Pixy_Color_PosY,1,3);
    LCD_Display_int(receive.ID,1,1);
    LCD_Display_int(receive.ERROR,1,2);
    LCD_Display_int(receive.LENGTH,1,3);
    LCD_Display_int(receive.PARAMETER[0],1,4);
    LCD_Display_int(receive.PARAMETER[1],1,5);
    LCD_Display_int(receive.PARAMETER[2],1,6);
    LCD_Display_int(receive.PARAMETER[3],1,7);
    //Set_AX(11,1024,299);
    
    
    cc[0] = 0xff;
    cc[1] = 0xff;
    cc[2] = 0x0b;
    cc[3] = 0x07;
    cc[4] = 0x03;
    cc[5] = 0x1e;
    cc[6] = 0x00;
    cc[7] = 0x02;
    cc[8] = 0x00;
    cc[9] = 0x02;
    cc[10]= 0xd3;
//  	taskENTER_CRITICAL();  //进入临界段
    HAL_HalfDuplex_EnableTransmitter(&huart5);

    
    HAL_UART_Transmit(&huart5,cc,11,10);
    
    HAL_HalfDuplex_EnableReceiver(&huart5);
    
    HAL_UART_Receive(&huart5,re,11,2000);
    
    /*左手给右手。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。*/
    
    osDelay(5);
  }
  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


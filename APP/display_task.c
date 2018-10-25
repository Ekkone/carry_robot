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
	
	
	//��λ���Ƕȣ����ƽǶ�0~300
	//      RPM�����ת��114RPM
	float servo[7][6] = {
					{100,100,100,100,100,50},//�ȶ���̬
					{100,100,100,100,100,50},//ץȡ���
					{100,100,100,100,100,50},//�������
					{100,100,100,100,100,50},//�м���̬
					{100,100,100,100,100,50},//�ſ�צ��
					{100,100,100,100,100,50},//ץ��צ��
					{100,100,100,100,100,50},//Ԥ����̬
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


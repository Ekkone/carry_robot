#ifndef __Pixy_Camera_H
#define __Pixy_Camera_H
#include "stm32f4xx_hal.h"

//Pixy�ṹ��
typedef struct Pixy_Color//��ɫ��λ�ô�С��Ϣ
{
	int16_t Pixy_Color_Sig;   //1-7 for normal signatures
	int16_t Pixy_Color_PosX;  //0 to 319
	int16_t Pixy_Color_PosY;  //0 to 199
	int16_t Pixy_Color_Width; //1 to 320
	int16_t Pixy_Color_Height;//1 to 200
	int16_t Pixy_Color_Angle; //����CCs��ɫ����ģʽ�²ſ���
}Pixy_Color;

extern Pixy_Color Pixy;

extern uint8_t Pixy_Temp[18];


uint8_t Pixy_Camera_Data(uint8_t resign_ok);


#endif /*__Pixy_Camera_H*/





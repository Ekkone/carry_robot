#ifndef __PIXYCAMERA_H
#define __PIXYCAMERA_H
#include "stm32f4xx_hal.h"//Pixy�ṹ��
typedef struct//��ɫ��λ�ô�С��Ϣ
{
	int16_t Sig;   //1-7 for normal signatures
	int16_t PosX;  //0 to 319
	int16_t PosY;  //0 to 199
	int16_t Width; //1 to 320
	int16_t Height;//1 to 200
	int16_t Area;
	int16_t Angle; //����CCs��ɫ����ģʽ�²ſ���
	double Distance;
}Pixycolor;
#define Pixy_A 0	
#define Pixy_B 1
#define Pixy_A_UASRT USART2
#define Pixy_B_UASRT UART4

extern Pixycolor PixyCam[2];
extern int Pixy_X[2][5];//���X��ֵ
extern int Pixy_Y[2][5];//���Y��ֵ

float Pixy_Recdata(unsigned char Pixy_N);
void Pixydata_Manage(Pixycolor* PIXY,unsigned char Pixy_N);
static void Measure_Distance(double Area);
void Pixy_Run(unsigned char Pixy_N);
void ModeServo_Control_Front(float P,float D);
#endif /*__Pixy_Camera_H*/

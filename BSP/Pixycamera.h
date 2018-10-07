#ifndef __PIXYCAMERA_H
#define __PIXYCAMERA_H
#include "stm32f4xx_hal.h"//Pixy结构体
typedef struct//单色块位置大小信息
{
	int16_t Sig;   //1-7 for normal signatures
	int16_t PosX;  //0 to 319
	int16_t PosY;  //0 to 199
	int16_t Width; //1 to 320
	int16_t Height;//1 to 200
	int16_t Area;
	int16_t Angle; //仅在CCs颜色代码模式下才可用
	double Distance;
}Pixycolor;
#define Pixy_A 0	
#define Pixy_B 1
#define Pixy_A_UASRT USART2
#define Pixy_B_UASRT UART4

extern Pixycolor PixyCam[2];
extern int Pixy_X[2][5];//存放X的值
extern int Pixy_Y[2][5];//存放Y的值

float Pixy_Recdata(unsigned char Pixy_N);
void Pixydata_Manage(Pixycolor* PIXY,unsigned char Pixy_N);
static void Measure_Distance(double Area);
void Pixy_Run(unsigned char Pixy_N);
void ModeServo_Control_Front(float P,float D);
#endif /*__Pixy_Camera_H*/

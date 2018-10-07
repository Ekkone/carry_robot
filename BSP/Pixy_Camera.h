#ifndef __Pixy_Camera_H
#define __Pixy_Camera_H
#include "stm32f4xx_hal.h"
//Pixy结构体
typedef struct Pixy_Color//单色块位置大小信息
{
	int16_t Pixy_Color_Sig;   //1-7 for normal signatures
	int16_t Pixy_Color_PosX;  //0 to 319
	int16_t Pixy_Color_PosY;  //0 to 199
	int16_t Pixy_Color_Width; //1 to 320
	int16_t Pixy_Color_Height;//1 to 200
	int16_t Pixy_Color_Angle; //仅在CCs颜色代码模式下才可用
}Pixy_Color;
#define Pixy_init_Xval 150 	    //
#define Pixy_init_Yval 150      //蓝场150   红场115
#define Area_Pixy      1    //河道面积阈值
extern signed int lift_height;
extern int Area_Pixy_ball;
extern int Pixy_PosX;
extern int Pixy_PosY;
extern signed int flex_length;
extern int Pixy_Pos_XY[2][5];

extern signed int lift_height;

extern float Side_length;
extern float Ratio_W_H;   //宽与高的比值
extern float Distance;

extern int Lost_map;
extern unsigned char Lost_Flag;   //丢图标志位

void Pixy_Camera_Data(void);
int Ten_to_Octal(uint32_t ten_data,uint32_t octal_data);

//float PixyAngle_To_AreaAngle(int8_t Angle);
//void Blocks_Distance(float Data_MianJi);
//void Rand_to_Zero(int16_t data_width,int16_t data_height,int16_t data_angle);
//void Control_Car(void);
//void LCD_Pixy(void);
//void Pixy_Distance(void);
//void ModeServo_Direction_Control(float P,float D);
//void ModeServo_Direction_Control_Inside(float P,float D);
//void Jungle_ModeServo_Control(float P,float D);
//void Servo_Updown_Control(float P,float D);
//void Servo_Flex_Control(float P,float D);
// void Wind_Control(int Max_PWM);
//void  Wind_Control_Flat(int Max_PWM_Flat);
//void  Wind_Control_Right(int Max_PWM_Right);
//void Pixy_Partial_location(void);
//void Pixy_Tracing(float P_ro,float D_ro,float P_fl,float D_fl);
//void RED_ModeServo_Direction_Control(float P,float D);
//void RED_Jungle_ModeServo_Control(float P,float D);
#endif /*__Pixy_Camera_H*/





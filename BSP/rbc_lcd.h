#ifndef __RBC_LCD_H
#define __RBC_LCD_H
#include "stm32f4xx_hal.h"

#define RBC_LCD_GPIOX	GPIOF

#define RBC_LCD_PINX	GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4

#define RBC_LCD_CS		GPIO_PIN_0
#define RBC_LCD_SDA		GPIO_PIN_1
#define RBC_LCD_RS		GPIO_PIN_2
#define RBC_LCD_SCK		GPIO_PIN_3
#define RBC_LCD_RST		GPIO_PIN_4

#define CS(a)	if (a)	\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_CS,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_CS,GPIO_PIN_RESET)
#define RES(a)	if (a)	\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_RST,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_RST,GPIO_PIN_RESET)
#define RS(a)	if (a)	\
          HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_RS,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_RS,GPIO_PIN_RESET)
#define SCLK(a)	if (a)	\
          HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_SCK,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_SCK,GPIO_PIN_RESET)
#define SID(a)	if (a)	\
          HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_SDA,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(	RBC_LCD_GPIOX,RBC_LCD_SDA,GPIO_PIN_RESET)


void LCD_GPIO_Config(void);
void ROC_LCD_Init(void);
void Send_Command(unsigned char command);
void Send_data(unsigned char data);
void Clear_LCD(void);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_write_char(unsigned char c);
void LCD_Write_string(unsigned char *table,unsigned char X, unsigned char Y);
void LCD_Display_float(float Data,unsigned char X, unsigned char Y);
void LCD_Display_int(signed int Data,unsigned char X, unsigned char Y);
void float2str(float data,unsigned char*s);
void int2str(signed int data,unsigned char*s);					
					
#endif					
					
					
	


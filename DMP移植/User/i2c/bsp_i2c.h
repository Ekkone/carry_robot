#ifndef __BSP_I2C_H
#define	__BSP_I2C_H

#include "stm32f10x.h"
#include "./usart/bsp_usart.h"


//MPU6050的AD0引脚接GND时，地址为0x68 ,接3.3V时，地址为0x69，注意要匹配。
#define MPU6050_ADDR   0x68


/*********************软件IIC使用的宏****************************/
#define Soft_I2C_SDA 		GPIO_Pin_11
#define Soft_I2C_SCL 		GPIO_Pin_10
#define Soft_I2C_PORT       GPIOB

#define Soft_I2C_SCL_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SCL)
#define Soft_I2C_SCL_1 		GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SCL)
#define Soft_I2C_SDA_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SDA)
#define Soft_I2C_SDA_1   	GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SDA)

#define Soft_I2C_SDA_STATE      GPIO_ReadInputDataBit(Soft_I2C_PORT, Soft_I2C_SDA)
#define Soft_I2C_DELAY 			Soft_I2C_Delay(100000)
#define Soft_I2C_NOP			Soft_I2C_Delay(10) 
//
#define Soft_I2C_READY		    0x00
#define Soft_I2C_BUS_BUSY	    0x01	
#define Soft_I2C_BUS_ERROR	    0x02
//
#define Soft_I2C_NACK	        0x00 
#define Soft_I2C_ACK	        0x01

void I2C_Bus_Init(void);

static void Soft_I2C_Configuration(void);
static void Soft_I2C_Delay(uint32_t dly);
static uint8_t Soft_I2C_START(void);
static void Soft_I2C_STOP(void);
static void Soft_I2C_SendACK(void);
static void Soft_I2C_SendNACK(void);
static uint8_t Soft_I2C_SendByte(uint8_t anbt_i2c_data);
static uint8_t Soft_I2C_ReceiveByte_WithACK(void);
static uint8_t Soft_I2C_ReceiveByte(void);
static uint8_t Soft_DMP_I2C_Write(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf);
static uint8_t Soft_DMP_I2C_Read(uint8_t soft_dev_addr, uint8_t soft_reg_addr, uint8_t soft_i2c_len,unsigned char *soft_i2c_data_buf);

																					
void Set_I2C_Retry(unsigned short ml_sec);
unsigned short Get_I2C_Retry(void);
int Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, 
                                          unsigned short RegisterLen, unsigned char *RegisterValue);
int Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, 
                                           unsigned short RegisterLen, const unsigned char *RegisterValue);
																					

#endif /* __BSP_I2C_H */

																					

																					

																					


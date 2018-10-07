#ifndef _SEND_DATA_TO_ANO
#define _SEND_DATA_TO_ANO

#include "stm32f10x.h"
#include "./usart/bsp_usart.h"


#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

typedef struct
{
    u8 msg_id;
    u8 msg_data;
    u8 send_check;
    u8 send_version;
    u8 send_status;
    u8 send_senser;
    u8 send_senser2;
    u8 send_pid1;
    u8 send_pid2;
    u8 send_pid3;
    u8 send_pid4;
    u8 send_pid5;
    u8 send_pid6;
    u8 send_rcdata;
    u8 send_offset;
    u8 send_motopwm;
    u8 send_power;
    u8 send_user;
    u8 send_speed;
    u8 send_location;

} send_data_flag_t;
/**
  * @brief  控制串口发送1个字符
  * @param  c:要发送的字符
  * @retval none
  */
void usart_send_char(uint8_t c);

/**
  * @brief 根据匿名上位机协议写的显示姿态的程序（上位机0512版本）
           *具体协议说明请查看上位机软件的帮助说明。
  * @param 
  * @retval none
  */
void Data_Send_Status(float Roll,float Pitch,float Yaw);

/**
  * @brief 根据匿名上位机协议写的显示姿态的程序（上位机0512版本）
           *具体协议说明请查看上位机软件的帮助说明。
  * @param  
  * @retval none
  */
void Data_Send_RawData(int16_t *Gyro_LSB,int16_t *Accel_LSB);
void Data_Send_RC(short thr,short yaw,short rol,short pit,short aux1,short aux2,short aux3,short aux4,short aux5,short aux6);
//发送外环PID参数，即角度的PID值
void Data_Send_ExPID(short Roll_P,short Roll_I,short Roll_D,short Pitch_P,short Pitch_I,short Pitch_D,short Yaw_P,short Yaw_I,short Yaw_D);
//发送内环PID参数，即角速率的PID值
void Data_Send_PID(u8 group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);

void Data_Send_User(short USER_DATA1,short USER_DATA2,short USER_DATA3,
	                  short USER_DATA4,short USER_DATA5,short USER_DATA6,
		                float USER_DATA7,float USER_DATA8,float USER_DATA9);
void Data_Send_RawData_ViaNRF(int16_t *Gyro,int16_t *Accel);
void Data_Send_MotoPWM(u16 m_1,u16 m_2,u16 m_3,u16 m_4,u16 m_5,u16 m_6,u16 m_7,u16 m_8);                      
#endif

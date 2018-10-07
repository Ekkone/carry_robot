/**
  ******************************************************************************
  * @file    send_data_to_ano.c
  * @version V1.0
  * @date    2017-07-23
  * @brief   将数据送到匿名上位机
  ******************************************************************************
  */ 
 
 #include "./usart/send_data_to_ano.h"

u16 flash_save_en_cnt = 0;
send_data_flag_t send_data_flag;					//需要发送数据的标志

void usart_send_char(uint8_t c)
{
	while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE)==RESET); //循环发送,直到发送完毕
	USART_SendData(DEBUG_USARTx,c);
}

void Data_Send_Status(float Roll,float Pitch,float Yaw)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
	unsigned int _temp;
	u8 data_to_send[50];

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(Roll*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0-(int)(Pitch*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(Yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;
	data_to_send[_cnt++]=BYTE3(_temp);
	data_to_send[_cnt++]=BYTE2(_temp);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=0xA0;
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}

void Data_Send_RawData(int16_t *Gyro,int16_t *Accel)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
//	unsigned int _temp;
	u8 data_to_send[50];

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	

	data_to_send[_cnt++]=BYTE1(Accel[0]);
	data_to_send[_cnt++]=BYTE0(Accel[0]);
	data_to_send[_cnt++]=BYTE1(Accel[1]);
	data_to_send[_cnt++]=BYTE0(Accel[1]);
	data_to_send[_cnt++]=BYTE1(Accel[2]);
	data_to_send[_cnt++]=BYTE0(Accel[2]);
	
	data_to_send[_cnt++]=BYTE1(Gyro[0]);
	data_to_send[_cnt++]=BYTE0(Gyro[0]);
	data_to_send[_cnt++]=BYTE1(Gyro[1]);
	data_to_send[_cnt++]=BYTE0(Gyro[1]);
	data_to_send[_cnt++]=BYTE1(Gyro[2]);
	data_to_send[_cnt++]=BYTE0(Gyro[2]);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}



void Data_Send_RC(short thr,short yaw,short rol,short pit,
	                short aux1,short aux2,short aux3,short aux4,short aux5,short aux6)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
	u8 data_to_send[50];

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE1(thr);
	data_to_send[_cnt++]=BYTE0(thr);
	data_to_send[_cnt++]=BYTE1(yaw);
	data_to_send[_cnt++]=BYTE0(yaw);
	data_to_send[_cnt++]=BYTE1(rol);
	data_to_send[_cnt++]=BYTE0(rol);
	data_to_send[_cnt++]=BYTE1(pit);
	data_to_send[_cnt++]=BYTE0(pit);
	data_to_send[_cnt++]=BYTE1(aux1);
	data_to_send[_cnt++]=BYTE0(aux1);
	data_to_send[_cnt++]=BYTE1(aux2);
	data_to_send[_cnt++]=BYTE0(aux2);
	data_to_send[_cnt++]=BYTE1(aux3);
	data_to_send[_cnt++]=BYTE0(aux3);
	data_to_send[_cnt++]=BYTE1(aux4);
	data_to_send[_cnt++]=BYTE0(aux4);
	data_to_send[_cnt++]=BYTE1(aux5);
	data_to_send[_cnt++]=BYTE0(aux5);
	data_to_send[_cnt++]=BYTE1(aux6);
	data_to_send[_cnt++]=BYTE0(aux6);
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}

void Data_Send_ExPID(short Roll_P,short Roll_I,short Roll_D,
	                 short Pitch_P,short Pitch_I,short Pitch_D,
					 short Yaw_P,short Yaw_I,short Yaw_D)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
	u8 data_to_send[50];

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE1(Roll_P);
	data_to_send[_cnt++]=BYTE0(Roll_P);
	data_to_send[_cnt++]=BYTE1(Roll_I);
	data_to_send[_cnt++]=BYTE0(Roll_I);
	data_to_send[_cnt++]=BYTE1(Roll_D);
	data_to_send[_cnt++]=BYTE0(Roll_D);
	data_to_send[_cnt++]=BYTE1(Pitch_P);
	data_to_send[_cnt++]=BYTE0(Pitch_P);
	data_to_send[_cnt++]=BYTE1(Pitch_I);
	data_to_send[_cnt++]=BYTE0(Pitch_I);
	data_to_send[_cnt++]=BYTE1(Pitch_D);
	data_to_send[_cnt++]=BYTE0(Pitch_D);
	data_to_send[_cnt++]=BYTE1(Yaw_P);
	data_to_send[_cnt++]=BYTE0(Yaw_P);
	data_to_send[_cnt++]=BYTE1(Yaw_I);
	data_to_send[_cnt++]=BYTE0(Yaw_I);
	data_to_send[_cnt++]=BYTE1(Yaw_D);
	data_to_send[_cnt++]=BYTE0(Yaw_D);
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}




//group=1,角速度PID；group=2,角度PID
void Data_Send_PID(u8 group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
    vs16 _temp;
	u8 data_to_send[50];

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10+group-1;
	data_to_send[_cnt++]=0;
	
	_temp = p1_p * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_i  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_d  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_p  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_i  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_d * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_p  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_i  * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_d * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}

void Data_Send_User(short USER_DATA1,short USER_DATA2,short USER_DATA3,
	                  short USER_DATA4,short USER_DATA5,short USER_DATA6,
		                float USER_DATA7,float USER_DATA8,float USER_DATA9)
{
	unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
	u8 data_to_send[50];
	vs16 _temp;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xf1;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE1(USER_DATA1);
	data_to_send[_cnt++]=BYTE0(USER_DATA1);
	data_to_send[_cnt++]=BYTE1(USER_DATA2);
	data_to_send[_cnt++]=BYTE0(USER_DATA2);
	data_to_send[_cnt++]=BYTE1(USER_DATA3);
	data_to_send[_cnt++]=BYTE0(USER_DATA3);
	data_to_send[_cnt++]=BYTE1(USER_DATA4);
	data_to_send[_cnt++]=BYTE0(USER_DATA4);
	data_to_send[_cnt++]=BYTE1(USER_DATA5);
	data_to_send[_cnt++]=BYTE0(USER_DATA5);
	data_to_send[_cnt++]=BYTE1(USER_DATA6);
	data_to_send[_cnt++]=BYTE0(USER_DATA6);
	
	_temp = (s16)USER_DATA7;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
//	_temp = (s16)USER_DATA8;
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	
//	_temp = (s16)USER_DATA9;
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	//和校验
	for(i=0;i<_cnt;i++)
		sum+= data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	//串口发送数据
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}
//把电机输出PWM波发送到上位机
void Data_Send_MotoPWM(u16 m_1,u16 m_2,u16 m_3,u16 m_4,u16 m_5,u16 m_6,u16 m_7,u16 m_8)
{
    unsigned char i=0;
	unsigned char _cnt=0,sum = 0;
	u8 data_to_send[50];
	vs16 _temp;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE1(m_1);
	data_to_send[_cnt++]=BYTE0(m_1);
	data_to_send[_cnt++]=BYTE1(m_2);
	data_to_send[_cnt++]=BYTE0(m_2);
	data_to_send[_cnt++]=BYTE1(m_3);
	data_to_send[_cnt++]=BYTE0(m_3);
	data_to_send[_cnt++]=BYTE1(m_4);
	data_to_send[_cnt++]=BYTE0(m_4);
//	data_to_send[_cnt++]=BYTE1(m_5);
//	data_to_send[_cnt++]=BYTE0(m_5);
//	data_to_send[_cnt++]=BYTE1(m_6);
//	data_to_send[_cnt++]=BYTE0(m_6);
//	data_to_send[_cnt++]=BYTE1(m_7);
//	data_to_send[_cnt++]=BYTE0(m_7);
//	data_to_send[_cnt++]=BYTE1(m_8);
//	data_to_send[_cnt++]=BYTE0(m_8);
	
	data_to_send[3] = _cnt-4;
	
	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
    
	for(i=0;i<_cnt;i++)
		usart_send_char(data_to_send[i]);
}

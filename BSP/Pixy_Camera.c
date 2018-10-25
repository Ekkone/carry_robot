/**********************************************
* @file    Pixy_Camera.c 
* @author  ncurm
* @version V1.0
* @date    2015/12/11	
* @brief   Pixy Camera����
***********************************************/
#include "Pixy_Camera.h"

Pixy_Color Pixy;
uint8_t Pixy_Temp[18] = {0};
/**********************************************************
��������Pixy_Camera_Data
����  ��Pixy�������ݴ���
����  ������ģʽ
���  �����ܵ���һ������ĵ����ݷ���1�����ܵ��ڶ������Ժ�����ݷ���2������ʧ�ܷ���0
**********************************************************/

uint8_t Pixy_Camera_Data(uint8_t resign_ok)
{
	uint8_t *Temp = Pixy_Temp;
	uint8_t flag = 0; 
	int32_t sum = 0;
	switch(resign_ok )
	{
		//��һģʽ1
		case 0x01:
							{
								for(uint8_t i = 6;i < 16;i += 2)
								{
									sum += Temp[i] | (Temp[i + 1] << 8);
								}
								if(sum == (Temp[4] | Temp[5] << 8))
								{
									Pixy.Pixy_Color_Sig    = Temp[6] | Temp[7] << 8;    //��ɫ�Ǻ�
									Pixy.Pixy_Color_PosX   = Temp[8] | Temp[9] << 8;   //X����
									Pixy.Pixy_Color_PosY   = Temp[10] | Temp[11] << 8; //Y����
									Pixy.Pixy_Color_Width  = Temp[12] | Temp[13] << 8; //��
									Pixy.Pixy_Color_Height = Temp[14] | Temp[15] << 8;//�� 
									flag = 1;
								}
								else
								{
									flag = 0;
									//filed
								}

							}
		 break;

		//��һģʽ2��
		case 0x02:
							{
								for(uint8_t i = 4;i < 14;i += 2)
								{
									sum += Temp[i] | (Temp[i + 1] << 8);
								}
								if(sum == (Temp[2] | Temp[3] << 8))
								{
									Pixy.Pixy_Color_Sig=Temp[4] | Temp[5] << 8;   //��ɫ�Ǻ�
									Pixy.Pixy_Color_PosX=Temp[6] | Temp[7] << 8;  //X����
									Pixy.Pixy_Color_PosY=Temp[8] | Temp[9] << 8; //Y����
									Pixy.Pixy_Color_Width=Temp[10] | Temp[11] << 8; //��
									Pixy.Pixy_Color_Height=Temp[12] | Temp[13] << 8;//�� 
									flag = 2;

								}
								else
								{
									flag = 0;
									//failed
								}
							}
		break;
		
		default:break;
	}
	
	return flag;
}


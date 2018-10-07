/**********************************************
* @file    Pixy_Camera.c 
* @author  ycb
* @version V1.0
* @date    2015/12/11	
* @brief   Pixy Camera����
***********************************************/
#include "Pixy_Camera.h"
Pixy_Color Pixy;
extern uint8_t ReSign_OK;
extern uint8_t RePixy_buf[18],Re_Counter;


double Zero_Width=0; //���ʱ�Ŀ�
double Zero_Height=0;//���ʱ�ĸ�
double Zero_MianJi=0;//���ʱ�����=���ʱ�ĸ�*���ʱ�Ŀ�
double Pixy_angle=0;

float Side_length=0;
float Ratio_W_H=0;   //����ߵı�ֵ
//float Distance=0;
float Ave_length=0;

int Lost_map=0;
int Camera_Flag=0;
unsigned char Lost_Flag=0;   //��ͼ��־λ

int Error2_Y;
int Error1_Y;
int Error1_X;
int Error2_X;
int Area_Pixy_ball=0;
int32_t Pixy_Pos_XY[2][5]={{Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval},\
{Pixy_init_Yval,Pixy_init_Yval,Pixy_init_Yval,Pixy_init_Yval,Pixy_init_Yval}};
int Pixy_PosX=Pixy_init_Xval;
int Pixy_PosY=Pixy_init_Yval;
/**********************************************************
��������Pixy_Camera_Data
����  ��Pixy�������ݴ���
����  ����
���  ����
**********************************************************/

void Pixy_Camera_Data(void)
{
	uint8_t Temp[18];
	Camera_Flag++;               //��ͼ
    switch(ReSign_OK )
	{
		//��һģʽ1
		case 0x01:*Temp = *RePixy_buf;
		          Pixy.Pixy_Color_Sig=Temp[6] | Temp[7] << 8;    //��ɫ�Ǻ�
		          Pixy.Pixy_Color_PosX=Temp[8] | Temp[9] << 8;   //X����
		          Pixy.Pixy_Color_PosY=Temp[10] | Temp[11] << 8; //Y����
		          Pixy.Pixy_Color_Width=Temp[12] | Temp[13] << 8; //��
		          Pixy.Pixy_Color_Height=Temp[14] | Temp[15] << 8;//�� 
				  ReSign_OK=0x00;
		          Camera_Flag=0;   //��ͼ
		          break;
		//CCģʽ
		case 0x03:*Temp = *RePixy_buf;
		          Pixy.Pixy_Color_Sig=Ten_to_Octal(Temp[6]+Temp[7]*256,Pixy.Pixy_Color_Sig);   //��ɫ�Ǻ�
		          Pixy.Pixy_Color_PosX=Temp[8]+Temp[9]*256;  //X����
		          Pixy.Pixy_Color_PosY=Temp[10]+Temp[11]*256; //Y����
		          Pixy.Pixy_Color_Width=Temp[12]+Temp[13]*256; //��
		          Pixy.Pixy_Color_Height=Temp[14]+Temp[15]*256;//�� 
				 if(Temp[17]==0x00) Pixy.Pixy_Color_Angle=Temp[16]+Temp[17]*256; //��
				 else               Pixy.Pixy_Color_Angle=Temp[16]-255; //��
				 break;

		//��һģʽ2��
		case 0x02:*Temp = *RePixy_buf;
              Pixy.Pixy_Color_Sig=Temp[4] | Temp[5] << 8;   //��ɫ�Ǻ�
		          Pixy.Pixy_Color_PosX=Temp[6] | Temp[7] << 8;  //X����
		          Pixy.Pixy_Color_PosY=Temp[8] | Temp[9] << 8; //Y����
		          Pixy.Pixy_Color_Width=Temp[10] | Temp[11] << 8; //��
		          Pixy.Pixy_Color_Height=Temp[12] | Temp[13] << 8;//�� 
		          break;
		
		//CCģʽ+��һģʽ
		case 0x04:*Temp = *RePixy_buf;
							Pixy.Pixy_Color_Sig=Ten_to_Octal(Temp[4]+Temp[5]*256,Pixy.Pixy_Color_Sig);   //��ɫ�Ǻ�
		          Pixy.Pixy_Color_PosX=Temp[6]+Temp[7]*256;  //X����
		          Pixy.Pixy_Color_PosY=Temp[8]+Temp[9]*256; //Y����
		          Pixy.Pixy_Color_Width=Temp[10]+Temp[11]*256; //��
		          Pixy.Pixy_Color_Height=Temp[12]+Temp[13]*256;//�� 
					if(Temp[17]==0x00) 
						Pixy.Pixy_Color_Angle=Temp[14]+Temp[15]*256; //��
					else               
						Pixy.Pixy_Color_Angle=Temp[14]-255; //��
					break;
		default:break;
	}
}

///**********************************************************
//��������PixyAngle_To_AreaAngle
//����  ��Pixy����ͷ�Ƕ�ת��Ϊ��������һ���ĳ��ؽǶ�����ϵ
//����  ��Pixy�ĽǶ�
//���  ��ת����ĽǶ�
//**********************************************************/
//float PixyAngle_To_AreaAngle(int8_t Angle)
//{
//	if(Angle>0)   Angle=360-Angle;
//	if(Angle<=0)  Angle=-Angle;
//	return Angle;
//}

///**********************************************************
//��������Servo_Direction_Control
//����  ����ģ����ķ���ջ�����
//����  ��P����,D����
//���  ����
//����ຽģ����Ƕȿ���
//**********************************************************/
//void ModeServo_Direction_Control(float P,float D)
//{
//  static signed int PWM,PWM_Num=1910;//
//	static signed int ek_now=0,ek_last=0;
//	
//	ek_now=Pixy_PosX-Pixy_init_Xval;     //�õ��Ƕ�ƫ��
//	PWM=P*ek_now+D*(ek_now-ek_last);   //PD����
//	if(ABS(PWM)<3)  PWM=0;//10
//	//�������
//	PWM_Num+=PWM;
//	if(PWM_Num>2000) PWM_Num=2000;
//	if(PWM_Num<900)  PWM_Num=900;
//	Servo1_PWM=PWM_Num;
//	//���¸�ֵ
//	ek_last=ek_now;
//}
///**********************************************************
//��������RED_ModeServo_Direction_Control
//����  ����ģ����ķ���ջ�����     //�쳡
//����  ��P����,D����
//���  ����
//����ຽģ����Ƕȿ���
//**********************************************************/
//void RED_ModeServo_Direction_Control(float P,float D)
//{
//    static signed int PWM,PWM_Num=1350;//
//	static signed int ek_now=0,ek_last=0;
//	
//	ek_now=Pixy_PosX-Pixy_init_Xval;     //�õ��Ƕ�ƫ��
//	PWM=P*ek_now+D*(ek_now-ek_last);   //PD����
//	if(ABS(PWM)<3)  PWM=0;//10
//	//�������
//	PWM_Num+=PWM;
//	if(PWM_Num>1900) PWM_Num=1900;
//	if(PWM_Num<1250)  PWM_Num=1250;
//	Servo1_PWM=PWM_Num;
//	//���¸�ֵ
//	ek_last=ek_now;
//}
///**********************************************************
//��������Servo_Direction_Control
//����  ����ģ����ķ���ջ�����
//����  ��P����,D����
//���  ����
//�ڲຽģ����Ƕȿ���
//**********************************************************/
//void ModeServo_Direction_Control_Inside(float P,float D)
//{
//  static signed int PWM,PWM_Num=2100;
//	static signed int ek_now=0,ek_last=0;
//	
//	ek_now=Pixy_PosX-Pixy_init_Xval;     //�õ��Ƕ�ƫ��
//	PWM=P*ek_now+D*(ek_now-ek_last);   //PD����
//	if(ABS(PWM)<5)  PWM=0;
//	//�������
//	PWM_Num+=PWM;
//	if(PWM_Num>1980) PWM_Num=1980;
//	if(PWM_Num<900)  PWM_Num=900;
//	Servo3_PWM=PWM_Num;
//	//���¸�ֵ
//	ek_last=ek_now;
//}

///**********************************************************
//��������Servo_Direction_Control
//����  �����˺�ģ�����ƫ
//����  ��P����,D����
//���  ����
//**********************************************************/
//void Jungle_ModeServo_Control(float P,float D)
//{
//    static signed int PWM,PWM_Num=1925;
//	static signed int ek_now=0,ek_last=0;
//	if(Re_Start==3)
//		ek_now=GetSida_Offset_New(0);     //�õ��Ƕ�ƫ��Jungle_Sida
//	else
//	    ek_now=GetSida_Offset_New(Jungle_Sida);     //�õ��Ƕ�ƫ��Jungle_Sida
//	PWM=P*ek_now+D*(ek_now-ek_last);   //PD����
//	if(ABS(PWM)<5)  PWM=0;
//	//�������
//	PWM_Num-=PWM;
//	if(PWM_Num>2100) PWM_Num=2100;
//	if(PWM_Num<1700) PWM_Num=1700;   //1380
//	Servo2_PWM=PWM_Num;
//	//���¸�ֵ
//	ek_last=ek_now;
//}
///**********************************************************
//��������RED_Jungle_ModeServo_Control
//����  �����˺�ģ�����ƫ      //�쳡
//����  ��P����,D����
//���  ����
//**********************************************************/
//void RED_Jungle_ModeServo_Control(float P,float D)
//{
//    static signed int PWM,PWM_Num=1400;
//	static signed int ek_now=0,ek_last=0;
//	
//	if(Re_Start==3)
//		ek_now=GetSida_Offset_New(0);                   //�õ��Ƕ�ƫ��Jungle_Sida
//	else		
//		ek_now=GetSida_Offset_New(RED_Jungle_Sida);     //�õ��Ƕ�ƫ��Jungle_Sida
//	PWM=P*ek_now+D*(ek_now-ek_last);   //PD����
//	if(ABS(PWM)<5)  PWM=0;
//	//�������
//	PWM_Num-=PWM;
//	if(PWM_Num>1700) PWM_Num=1700;
//	if(PWM_Num<1100) PWM_Num=1100;   //1380
//	Servo2_PWM=PWM_Num;
//	//���¸�ֵ
//	ek_last=ek_now;
//}
///**********************************************************
//��������Servo_Direction_Control
//����  �������������ջ�����
//����  ��P����,D����
//���  ����

//signed int Ramp1_Angle=-765;
//signed int Ramp2_Angle=-1350;
//signed int Ramp3_Angle=-1490;
//#define  Flex_MotorID            35   //�������ID
//**********************************************************/
//signed int lift_height=0;
//signed int height_difference = 0;
//signed int ek_now=0;
//signed int ek_last=0;
//void Servo_Updown_Control(float P,float D)
//{
//	ek_now=Pixy_init_Yval-Pixy_PosY;             //�õ��߶�ƫ��
//	height_difference=P*ek_now+D*(ek_now-ek_last);       //PD����
//	if(ABS(height_difference)<5)
//		height_difference=0;
//	lift_height -= height_difference;
//	if(lift_height>=-30) 			lift_height= -30;
//	if(lift_height<=Ramp3_Angle) 	lift_height =Ramp3_Angle;
//	ek_last=ek_now;
//	Servo_Set_Absolute_Angle(lift_height ,RE35_Ratio ,UpDown_MotorID);
//}

///**********************************************************
//��������void Servo_Flex_Control(float P,float D)
//����  �������������ջ�����
//����  ��P����,D����
//���  ����
//#define  Flex_MotorID            35   //�������ID
//**********************************************************/

//signed int flex_length=0;
//void Servo_Flex_Control(float P,float D)
//{
//  signed int flex_difference = 0;
//	signed int ek_now=0;
//	static signed int ek_last=0;
//	
//	ek_now=Pixy_PosX-185;             //�õ��߶�ƫ��
//	flex_difference=P*ek_now+D*(ek_now-ek_last);       //PD����
//	if(ABS(flex_difference)<5)  flex_difference=0;
//	flex_length -= flex_difference;
//	if(flex_length>=0) 			flex_length=0;
//	if(flex_length<=-650) 	flex_length=-650;
//	ek_last=ek_now;
//	Servo_Set_Absolute_Angle(flex_length,RE25_Ratio,Flex_MotorID);
//}

///**********************************************************
//��������void Pixy_Tracing(float P_ro,float D_ro,float P_fl,float D_fl)
//����  ��Pixy����
//����  ��float P_ro,float D_ro,float P_fl,float D_fl
//���  ����ת������
//**********************************************************/
//void Pixy_Tracing(float P_ro,float D_ro,float P_fl,float D_fl)
//{	
//	static signed int PWM,PWM_Num=1860;
//	signed int flex_difference = 0;
//	signed int ek_now=0;
//	static signed int ek_last=0;
//	
//	ek_now=Pixy_PosX-Pixy_init_Xval;             //�õ��߶�ƫ��
//	flex_difference=P_fl*ek_now+D_fl*(ek_now-ek_last);  //PD����
//	if(ABS(flex_difference)<10)  flex_difference=0;
//	flex_length -= flex_difference;
//	if(flex_length>=0) 			flex_length=0;
//	if(flex_length<=-650) 	flex_length=-650;
//		
//	PWM=P_ro*ek_now+D_ro*(ek_now-ek_last);//PD����
//	if(ABS(PWM)<5)  PWM=0;
//	//�������
//	PWM_Num+=PWM;
//	if(PWM_Num>1980)
//	{
//		Servo_Set_Absolute_Angle(flex_length,RE25_Ratio,Flex_MotorID);
//	}		
//		
//	if(PWM_Num<1700)
//	{
//		Servo_Set_Absolute_Angle(flex_length,RE25_Ratio,Flex_MotorID);
//	} 
//	else
//	{
//		Servo1_PWM=PWM_Num;
//	} 	
//	
//	
//	ek_last=ek_now;	
//}

///******************************************************************************
//Function Name: Ten_to_Octal
//Author       : ����
//Date         : 2015-11-27
//Description  : ʮ����ת��Ϊ�˽���
//Inputs       : ten_data:ʮ������   octal_data���˽�����
//Outputs      : None
//*****************************************************************************/
int Ten_to_Octal(uint32_t ten_data,uint32_t octal_data)
{
    int i,j; 
    int tmp;	
		octal_data=0;
    for(i=1;;i++) 
    {
        tmp=ten_data%8;           /*���λ��ת��Ϊ�˽���ʱ�ĸ�λ��������ʮ����λ����������*/
        for(j=1;j<=i;j++) tmp*=10;
        tmp/=10;
        octal_data+=tmp;               /*�洢ת���õ�ʮ������*/
        ten_data/=8;
        if(ten_data==0)   break;           /*�����һλ����8�������ѭ��*/
    }
	return octal_data;
}
///******************************************************************************
//Function Name: Blocks_Distance
//Author       : ����
//Date         : 2015-12-11
//Description  : �������*����=����    - 1.29e8*x^2 + 2.06e5*x + 19.7
//                   - 1.3e8*x^2 + 2.1e5*x + 20.0    2.88e11*x^3 - 3.97e8*x^2 + 2.7e5*x + 16.3
//                    2.87e10*x^3 - 1.08e8*x^2 + 1.78e5*x + 22.8
//                    - 2.6e7*x^2 + 1.2e5*x + 30.0
//               ��ʽ��d=2.06*100000/S-1.29*100000000/S/S+19.7
//Inputs       : None
//Outputs      : None
//Notes        : 
//Revision     : 
//*****************************************************************************/
//void Blocks_Distance(float Data_MianJi)
//{
////  	Distance=2.96*1000000/(Data_MianJi*Data_MianJi) + 5.07*10000/Data_MianJi + 18.1 -6.23*100000000/(Data_MianJi*Data_MianJi*Data_MianJi);
//     Distance=5.3*100000000/(Data_MianJi*Data_MianJi*Data_MianJi) - 8.6*1000000/(Data_MianJi*Data_MianJi) + 6.5*10000/Data_MianJi + 15.0 ;
//}
///******************************************************************************
//Function Name: Rand_to_Zero
//Author       : ����
//Date         : 2015-12-9
//Description  : ��������ĽǶȶ�Ӧ��0��ʱ�̵�ԭʼ���
//               ���㹫ʽΪ�� Zero_Height*sin angle + Zero_Width*cos angle = data_width
//                            Zero_Height*cos angle + Zero_Width*sin angle = data_height
//               ��width��height��ʽΪ��
//                 Zero_Height = (data_height * cos angle - data_width *sin angle)/(cos angle *cos angle -sin angle *sin angle)
//                 Zero_Width  = (data_height - data_height * cos angle)/sin angle  
//Inputs       : None
//Outputs      : None
//Notes        : 
//Revision     : 
//*****************************************************************************/
//void Rand_to_Zero(s16 data_width,s16 data_height,s16 data_angle)
//{ 
//	 if(data_angle!=0)
//	 {
//		 if(data_angle<0)  data_angle=-data_angle;
//     if(data_angle==45 || data_angle==46) data_angle=44;//45��Ƕ��޷������������ĸΪ0��������44����档    		 
////		 if(data_angle-90>0) data_angle=data_angle-90;//90-180��֮�������ȥ90�������㡣 
//		 if(data_angle>90) 
//		 {
//			  data_angle=180-data_angle;//90-180��֮�����180���ȥ������
//			  if(data_angle==45 || data_angle==46) data_angle=44;
//		 }
//		 //45���5�㷶Χ�ڵ�����ͷ���صĿ�͸߶���΢��һ�����ݶԹ�ʽ�������ֵ�ܲ����ϴ�Ӱ�죬���Կ��Ǹ�������ͷ���ص�ֵ���ó��Ϳ�ֵ�ӽ�
//		 if(ABS(data_angle-45)<=8)
//		 {
//        if(data_width > data_height) 
//				{				
//					 if((data_width-data_height)%2==0)  data_width-=(data_width-data_height)/2;//��ֵΪż�� 
//					 else  data_width-=(data_width-data_height+1)/2;//����
//        }
//        else 
//        {				
//					 if((data_height - data_width)%2==0)  data_height=data_height-(data_height - data_width)/2;//��ֵΪż�� 
//					 else  data_height=data_height-(data_height - data_width+1)/2;//����
//        }					
//     }	 
//		 Pixy_angle = (((double)data_angle)/180) *3.1415926;		 
//     //���ʱ������һ�����������Σ�Ҫ��Ȼ��������д�ƫ��		 
//		 Zero_Height = (data_height * cos(Pixy_angle) -  data_width *sin(Pixy_angle))/(cos(Pixy_angle*2)) ;
//		 Zero_Width  = (data_height - Zero_Height * cos(Pixy_angle))/sin(Pixy_angle) ; 
//		 Zero_MianJi = Zero_Height * Zero_Width;	 
//	 }
//	 else  
//	 {
//		 Zero_Height=data_height;
//		 Zero_Width=data_width;
//		 Zero_MianJi=data_height*data_width;
//	 }
//}


//void Pixy_Distance(void)
//{
//	 Pixy_Camera_Data();	
//	 Error1_Y=Pixy.Pixy_Color_PosY + Pixy.Pixy_Color_Height/2;
//	 Error2_Y=Pixy.Pixy_Color_PosY - Pixy.Pixy_Color_Height/2;
//	 Error1_X=Pixy.Pixy_Color_PosX + Pixy.Pixy_Color_Width/2;
//	 Error2_X=Pixy.Pixy_Color_PosX - Pixy.Pixy_Color_Width/2;
//	 if(Camera_Flag>8)  //��ͼ 
//	 {		 
//			 if(Error2_Y<=5 && Error2_Y>=0)             //��Y�������涪ͼ   
//			 {	
//				 Lost_Flag=1;
//			 }
//			 else if(Error1_Y<=199 && Error1_Y>=194)    //��Y�������涪ͼ
//			 {	
//				 Lost_Flag=2;
//			 }
//             
//			 if(Error2_X<=5 && Error2_X>=0)	            //��X������߶�ͼ
//			 {
//				 Lost_Flag=3;
//			 }		
//             else if(Error1_X<=319 && Error1_X>=314)	//��X�����ұ߶�ͼ
//			 {
//				 Lost_Flag=4;
//			 }
//			 Pixy.Pixy_Color_PosX=Pixy_init_Xval;
//			 Pixy.Pixy_Color_PosY=Pixy_init_Yval;		 	
//			 Lost_map++;			 
//	 }
//	 else if(Camera_Flag==0)
//	 { 
//           if(Error2_X>5&&Error1_X<314 && Error2_Y>5&&Error1_Y<194)  //��ͼ����
//	       {
//			 Ratio_W_H=(float)Pixy.Pixy_Color_Width/Pixy.Pixy_Color_Height;  //��ȡ����ߵı���
//			 Ave_length=(float)(Pixy.Pixy_Color_Width+Pixy.Pixy_Color_Height)/2;
//			
//			 if(Ave_length>=27 && Ratio_W_H>=1.35)  Side_length=Pixy.Pixy_Color_Width;//90cm����
//			 else if(Ave_length<27 && Ratio_W_H>1.5)  Side_length=Side_length;//90cm�Ժ�����ֵ����1.5����ȡ��һ��ֵ
//			 else Side_length=Ave_length;
//				
//			 Area_Pixy_ball=Side_length*Side_length;
//			 Blocks_Distance(Area_Pixy_ball); 		
//	       }
//		   Lost_map=0;
//	 } 
//	 Pixy_PosX = Mid_Value((int *)(Pixy_Pos_XY[0]),5);
//	 Pixy_PosY = Mid_Value((int *)(Pixy_Pos_XY[1]),5);
// } 
///**********************************************************
//�������� void Wind_Control(vind)
//����  ��б�·����ּ�����
//����  ����
//���  ����
//**********************************************************/
//#define  Max_Distance    100
//#define  Min_Distance    30
////#define  Max_PWM         1500        //180 1500   220 1750    
// void Wind_Control(int Max_PWM)
//{
//	static unsigned char Wind_Num=0;  //��������
//	if(Distance>=Max_Distance)  Wind_Num=1;
//	if(Distance<Max_Distance && Distance>=(Max_Distance-20))
//		                       Wind_Num=2;
//	if(Distance<(Max_Distance-20) && Distance>=(Max_Distance-40))
//		                       Wind_Num=3;
//	if(Distance<(Max_Distance-40) && Distance>=(Max_Distance-60))
//		                       Wind_Num=4;
//	if(Distance<(Max_Distance-60))  Wind_Num=5;
//	switch(Wind_Num)
//	{
//		case 1:Model_PWM=Max_PWM-100;break;
//		case 2:Model_PWM=Max_PWM-75;break;
//		case 3:Model_PWM=Max_PWM-50;break;
//		case 4:Model_PWM=Max_PWM-25;break;
//		case 5:Model_PWM=Max_PWM;break;
//		default:Model_PWM=1600; break;
//	}
//}
///**********************************************************
//�������� void Wind_Control(vind)
//����  ��ƽ�ط����ּ�����
//����  ����
//���  ����
//**********************************************************/
////#define  Max_PWM_Flat         1400               //180 1400  220 1550     
//void  Wind_Control_Flat(int Max_PWM_Flat)
//{
//	static unsigned char Wind_Num=0;  //��������
//	if(Distance>=Max_Distance)  Wind_Num=1;
//	if(Distance<Max_Distance && Distance>=(Max_Distance-20))
//		                        Wind_Num=2;
//	if(Distance<(Max_Distance-20) && Distance>=(Max_Distance-40))
//		                       Wind_Num=3;
//	if(Distance<(Max_Distance-40) && Distance>=(Max_Distance-60))
//		                       Wind_Num=4;
//	if(Distance<(Max_Distance-60))  Wind_Num=5;
//	switch(Wind_Num)
//	{
//		case 1:Model_PWM=Max_PWM_Flat-100;break;
//		case 2:Model_PWM=Max_PWM_Flat-75;break;
//		case 3:Model_PWM=Max_PWM_Flat-50;break;
//		case 4:Model_PWM=Max_PWM_Flat-25;break;
//		case 5:Model_PWM=Max_PWM_Flat;break;
//		default:Model_PWM=1600; break;
//	}
//}

///**********************************************************
//�������� void Wind_Control(vind)
//����  ��ֱ�Ƿ����ּ�����
//����  ����
//���  ����
//**********************************************************/
//#define  Suit_Distance   60
////#define  Max_PWM_Right  1700
//void  Wind_Control_Right(int Max_PWM_Right)
//{
////	static char Wind_Num=0;  //��������
////	if(Distance>=Suit_Distance+30)  Wind_Num=1;
////	if(Distance<Suit_Distance+30 && Distance>=(Max_Distance+10))
////		                       Wind_Num=2;
////	if(Distance<(Suit_Distance+10) && Distance>=(Suit_Distance-10))
////		                       Wind_Num=3;
////	if(Distance<(Suit_Distance-10) && Distance>=(Suit_Distance-30))
////		                       Wind_Num=4;
////	if(Distance<(Suit_Distance-30))  Wind_Num=5;
////	switch(Wind_Num)
////	{
////		case 1:Model_PWM=Max_PWM_Right+40;	break;
////		case 2:Model_PWM=Max_PWM_Right+20;	break;
////		case 3:Model_PWM=Max_PWM_Right;			break;
////		case 4:Model_PWM=Max_PWM_Right-20;	break;
////		case 5:Model_PWM=Max_PWM_Right-40;	break;
////		default:Model_PWM=1600; 						break;
////	}
//	Max_PWM_Right-=0.3;
//	if(Max_PWM_Right<1550)                                 //220 1420   180 1550
//		Max_PWM_Right=1550;
//	Model_PWM=Max_PWM_Right;
//}

///**********************************************************
//�������� void Pixy_Partial_location(void)
//����  ��Pixy�ֲ���λB��
//����  ����
//���  ����
//**********************************************************/
//#define  distance_one    1085//mm
//#define  distance_two    965
//#define  distance_three  1000
//#define  distance_four   1520
//#define  distance_five   1035
//#define  distance_six    515
//void Pixy_Partial_location(void)
//{
//	switch(white2_line_num)
//	{
//		case 0: 		break;				
//		case 1:
//						break;
//		case 2:
//						if(Distance*10+ABS(Robot_Y)>distance_two)
//						{
//							Wind_Control(1430);
//						}
//						else
//						{
//							Wind_Control_Flat(1400);
//						}
//						break;
//		case 3:
//						if(Distance*10+ABS(Robot_Y)<distance_three)
//						{
//							Wind_Control(1430);
//						}
//						else
//						{
//							Wind_Control_Flat(1380);
//						}
//						break;
//		case 4:
////						if(Distance*10+ABS(Robot_Y)>distance_four)
////						{
////							Wind_Control();
////						}
////						else
////						{
//							Wind_Control_Flat(1540);
////						}
//						break;
//		case 5:
//						Wind_Control_Right(1540);
//						break;
//		case 6:
//						if(Distance*10+ABS(Robot_Y)>distance_six)
//						{
//							Wind_Control(1580);
//						}
//						else
//						{
//							Wind_Control_Flat(1650);
//						}
//						break;
//		default:Model_PWM=1600; break;
//	}
//}

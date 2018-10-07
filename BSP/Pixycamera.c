
#include "Pixycamera.h"
static int Error2_Y[2];
static int Error1_Y[2];
static int Error1_X[2];
static int Error2_X[2];
extern char Time5_cnt[2];
char Camera_cnt[2]={0};
Pixycolor PixyCam[2];
unsigned char Mode_OK[2]={0};
static unsigned char Pixy_Temp[2][16]={0};//临时接受数据的数组
static unsigned char Pixy_Data[2][16]={0};//接受数据的数组
int Pixy_X[2][5]={0,0,0,0,0,Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval,Pixy_init_Xval};//存放X的值
int Pixy_Y[2][5]={0};//存放Y的值
/**********************************************************
函数名： bool Pixy_Recdata(unsigned char Pixy_N)
功能  ：Pixy接收数据
输入  ：无
输出  ：无
**********************************************************/
float Pixy_Recdata(unsigned char Pixy_N)
{
	static char Counter=0; 
	USART_TypeDef *UASRT_N;
	/*选择串口*/
	switch(Pixy_N)
	{
	 case Pixy_A:UASRT_N=Pixy_A_UASRT;break;
	 case Pixy_B:UASRT_N=Pixy_B_UASRT;break;
	 default:break;
	}
	/*接收数据*/
	Pixy_Temp[Pixy_N][Counter]=USART_ReceiveData(UASRT_N);
	/*判断帧头*/
	if(Counter==0&&Pixy_Temp[Pixy_N][0]!=0x55)  
	{
		Counter = 0; //如果不是帧头返回
		return FALSE;
	}
	else 
	{
		Counter++;
		if(Counter==16&&Pixy_Temp[Pixy_N][0]==0x55&&Pixy_Temp[Pixy_N][1]==0xAA&&Pixy_Temp[Pixy_N][2]==0x55&&Pixy_Temp[Pixy_N][3]==0xAA)
			{
				memcpy(Pixy_Data[Pixy_N],Pixy_Temp[Pixy_N],16);
				Counter=0;//重新赋值，准备下一帧数据的接收
				Mode_OK[Pixy_N]=0x01;
			}
		return TRUE;
	}
}			

/**********************************************************
函数名：Pixydata_Manage(Pixy PIXY,unsigned char *std)
功能  ：Pixy接收数据
输入  ：无
输出  ：无
**********************************************************/
void Pixydata_Manage(Pixycolor* PIXY,unsigned char Pixy_N)
{
	unsigned char Temp[16];	
	if(Mode_OK[Pixy_N]==0x01)
	{	
		memcpy(Temp,(unsigned char *)Pixy_Temp[Pixy_N],16);
		PIXY->Sig=Temp[6]+Temp[7]*256;    //颜色记号
		PIXY->PosX=Temp[8]+Temp[9]*256;   //X坐标
		PIXY->PosY=Temp[10]+Temp[11]*256; //Y坐标
		PIXY->Width=Temp[12]+Temp[13]*256; //长
		PIXY->Height=Temp[14]+Temp[15]*256;//高 
		Camera_cnt[Pixy_N]++;
	  Mode_OK[Pixy_N]=0x00;
	}
	
	Error1_Y[Pixy_N]=PIXY->PosY + PIXY->Height/2;
	Error2_Y[Pixy_N]=PIXY->PosY - PIXY->Height/2;
	Error1_X[Pixy_N]=PIXY->PosX + PIXY->Width/2;
	Error2_X[Pixy_N]=PIXY->PosX - PIXY->Width/2;
	
	if(Time5_cnt[Pixy_N]-Camera_cnt[Pixy_N]>9)  //丢图 
	 {	
			 if(Error2_Y[Pixy_N]<=5 && Error2_Y[Pixy_N]>=0)             //从Y方向上面丢图   
			 {	
				 
			 }
			 else if(Error1_Y[Pixy_N]<=199 && Error1_Y[Pixy_N]>=194)    //从Y方向下面丢图
			 {	
				 
			 }
             
			 if(Error2_X[Pixy_N]<=5 && Error2_X[Pixy_N]>=0)	            //从X方向左边丢图
			 {
				 
			 }		
       else if(Error1_X[Pixy_N]<=319 && Error1_X[Pixy_N]>=314)	//从X方向右边丢图
			 {
				 
			 }
			 
			 PixyCam[Pixy_N].PosX=150;
			 PixyCam[Pixy_N].PosY=Pixy_init_Yval;			 
			 Camera_cnt[Pixy_N]=0;
			 Time5_cnt[Pixy_N]=0;
			 
	 }
	 else 
	 {
			if(Error2_X[Pixy_N]>5&&Error1_X[Pixy_N]<314 && Error2_Y[Pixy_N]>5&&Error1_Y[Pixy_N]<194)  //在图像中
			{
			 PIXY->Area=PIXY->Height*PIXY->Width;//球面积
			 PIXY->Distance=2.96*1000000/(PIXY->Area*PIXY->Area) + 5.07*10000/PIXY->Area + 18.1 -6.23*100000000/(PIXY->Area*PIXY->Area*PIXY->Area);	  		
			}
	 } 
	 
	 if(Time5_cnt[Pixy_N]-Camera_cnt[Pixy_N]<=9 && Camera_cnt[Pixy_N]==100) 
	 {
		 Camera_cnt[Pixy_N]=0;
		 Time5_cnt[Pixy_N]=0;	
	 } 	
} 
/**********************************************************
函数名：void Pixy_Run(unsigned char Pixy_N)
功能  ：运行Pixy
输入  ：无
输出  ：无
**********************************************************/
void Pixy_Run(unsigned char Pixy_N)
{
	static char times={0};
	Pixydata_Manage(&PixyCam[Pixy_N],Pixy_N);
	Pixy_X[Pixy_N][times]=PixyCam[Pixy_N].PosX;
	Pixy_Y[Pixy_N][times]=PixyCam[Pixy_N].PosY;
	times++;
	if(times==5)
	{
		times=0;
	}
	PixyCam[Pixy_N].PosX=Mid_Value((int *)(Pixy_X[Pixy_N]),5);
	PixyCam[Pixy_N].PosY=Mid_Value((int *)(Pixy_Y[Pixy_N]),5);		
}
/**********************************************************
函数名：Servo_Direction_Control
功能  ：航模舵机的方向闭环控制
输入  ：P参数,D参数
输出  ：无
内侧航模电机角度控制
**********************************************************/
void ModeServo_Control_Front(float P,float D)
{
  static signed int PWM,PWM_Num=1070;
	static signed int ek_now=0,ek_last=0;
	
	ek_now=PixyCam[Pixy_B].PosX-Pixy_init_Xval;     //得到角度偏差
	PWM=P*ek_now+D*(ek_now-ek_last);   //PD控制
	if(ABS(PWM)<5)  PWM=0;
	//驱动舵机
	PWM_Num+=PWM;
	if(PWM_Num>2070) PWM_Num=2070;
	if(PWM_Num<70)  PWM_Num=70;
	Servo2_PWM=PWM_Num;
	//重新赋值
	ek_last=ek_now;
}

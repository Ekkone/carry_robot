/****************************************************************************
*
*�ļ�����FUZZY_PID.c
*
*��  �ܣ����ļ���ģ������Ӧ����PID���Ƴ���
*
*��  ��: Sahara
*
****************************************************************************/

#include "fuzzy_pid.h"

/****************************************************************************
*
*�ļ�����FUZZY_Calc_Kp(float e,float ec,uint16_t e_max,uint16_t ec_max,uint8_t fuzzy_max)
*
*��  �ܣ�ģ������ �����崦�����������趨��
*
*��  ��: Sahara   Ekko
* 
*��ڲ�����float e,float ec��e_max(���仯��ΧΪ+-e_max),ec_maxͬ��fuzzy_maxΪ������������ֵ
*
*���ڲ�����fuzzy
*
****************************************************************************/

float FUZZY_Calc_Kp(float e,float ec,float e_max,float ec_max,float fuzzy_max)
{
	float eRule[7]  = {-e_max, -e_max * 0.667f, -e_max * 0.333f, 0, e_max * 0.333f, e_max * 0.667f, e_max};
	float ecRule[7] = {-ec_max, -ec_max * 0.667f, -ec_max * 0.333f, 0, ec_max * 0.333f, ec_max * 0.667f, ec_max};
	float uRule[7]  = {fuzzy_max, fuzzy_max * 0.667f, fuzzy_max * 0.333f, 0, fuzzy_max * 0.333f, fuzzy_max * 0.667f, fuzzy_max};
	
	float eFuzzy[7];
	float eFuzzy_Out[6];
	float ecFuzzy[7];	
	float ecFuzzy_Out[6];
	float uFuzzy[7];
	int   Pe,Pec;
	float Rule[7][7];
	float a1, a2;//����ģ�������Ŀɵ�����
  float fuzzy; //���ֵ
	/*int Rule[6][6]={{3, 2, 2, 1, 0, 0},
					{3, 2, 1, 1, 0, -1},
					{2, 2, 1, 0, -1, -1},
					{2, 1, 0, -1, -2, -2},
					{1, 0, -1, -1, -2, -2},
					{0, -1, -2, -2, -2, -3},
					};
	*/
	/*int Rule[7][7]={{3, 3, 2, 2, 1, 0, 0},
					{3, 3, 2, 1, 1, 0, -1},
					{2, 2, 2, 1, 0, -1, -1},
					{2, 2, 1, 0, -1, -2, -2},
					{1, 1, 0, -1, -1, -2, -2},
					{1, 0, -1, -2, -2, -2, -3},
					{0, 0, -2, -2, -2, -3, -3},
					};
	*/
	int i;
  static uint8_t xp = 0,yp = 0;
	for(i=0;i<7;i++)
	{
		eFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		ecFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		uFuzzy[i]=0;
	}
	for(i=0;i<2;i++)
	{
		eFuzzy_Out[i]=0;	
	}
	for(i=0;i<2;i++)
	{
		ecFuzzy_Out[i]=0;	
	}
/****************************************************************************
*
* ���������������
* ���������������������������������������
*
****************************************************************************/		
	if(e < eRule[0])
	{
		eFuzzy_Out[0] = 1.0;
		Pe = 0;
	}
	else if(e > eRule[0] && e < eRule[1])
	{
		eFuzzy[0] = (e - eRule[1])/(eRule[0] - eRule[1]);
		eFuzzy[1] = (e - eRule[0])/(eRule[1] - eRule[0]);
		eFuzzy_Out[0] = eFuzzy[0] > eFuzzy[1] ? eFuzzy[0] : eFuzzy[1];
		Pe = 0;
	}
	else if(e > eRule[1] && e < eRule[2])
	{
		eFuzzy[1] = (e - eRule[2])/(eRule[1] - eRule[2]);
		eFuzzy[2] = (e - eRule[1])/(eRule[2] - eRule[1]);
		eFuzzy_Out[1] = eFuzzy[1] > eFuzzy[2] ? eFuzzy[1] : eFuzzy[2];
		Pe = 1;
	}
	else if(e > eRule[2] && e < eRule[3])
	{
		eFuzzy[2] = (e - eRule[3])/(eRule[2] - eRule[3]);
		eFuzzy[3] = (e - eRule[2])/(eRule[3] - eRule[2]);
		eFuzzy_Out[2] = eFuzzy[2] > eFuzzy[3] ? eFuzzy[2] : eFuzzy[3];
		Pe = 2;
	}
	else if(e > eRule[3] && e < eRule[4])
	{
		eFuzzy[3] = (e - eRule[4])/(eRule[3] - eRule[4]);
		eFuzzy[4] = (e - eRule[3])/(eRule[4] - eRule[3]);
		eFuzzy_Out[3] = eFuzzy[3] > eFuzzy[4] ? eFuzzy[3] : eFuzzy[4];
		Pe = 3;
	}
	else if(e > eRule[4] && e < eRule[5])
	{
		eFuzzy[4] = (e - eRule[5])/(eRule[4] - eRule[5]);
		eFuzzy[5] = (e - eRule[4])/(eRule[5] - eRule[4]);
		eFuzzy_Out[4] = eFuzzy[4] > eFuzzy[5] ? eFuzzy[4] : eFuzzy[5];
		Pe = 4;
	}
	else if(e > eRule[5] && e < eRule[6])
	{
		eFuzzy[5] = (e - eRule[6])/(eRule[5] - eRule[6]);
		eFuzzy[6] = (e - eRule[5])/(eRule[6] - eRule[5]);
		eFuzzy_Out[5] = eFuzzy[5] > eFuzzy[6] ? eFuzzy[5] : eFuzzy[6];
		Pe =  5;
	}
	else 
	{
		eFuzzy_Out[5] = 1.0;
		Pe = 5;
	}	
	//eFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
	
/****************************************************************************
*
* ���仯������������
* ���仯����������������������������������
*
****************************************************************************/		
	if(ec < ecRule[0])
	{
		ecFuzzy_Out[0]=1.0;
		Pec = 0;
	}
	else if(ec > ecRule[0] && ec < ecRule[1])
	{
		ecFuzzy[0] = (ec - ecRule[1])/(ecRule[0] - ecRule[1]);
		ecFuzzy[1] = (ec - ecRule[0])/(ecRule[1] - ecRule[0]);
		ecFuzzy_Out[0] = ecFuzzy[0] > ecFuzzy[1] ? ecFuzzy[0] : ecFuzzy[1];
		Pec = 0;
	}
	else if(ec > ecRule[1] && ec < ecRule[2])
	{
		ecFuzzy[1] = (ec - ecRule[2])/(ecRule[1] - ecRule[2]);
		ecFuzzy[2] = (ec - ecRule[1])/(ecRule[2] - ecRule[1]);
		ecFuzzy_Out[1] = ecFuzzy[1] > ecFuzzy[2] ? ecFuzzy[1] : ecFuzzy[2];
		Pec = 1;
	}
	else if(ec > ecRule[2] && ec < ecRule[3])
	{
		ecFuzzy[2] = (ec - ecRule[3])/(ecRule[2] - ecRule[3]);
		ecFuzzy[3] = (ec - ecRule[2])/(ecRule[3] - ecRule[2]);
		ecFuzzy_Out[2] = ecFuzzy[2] > ecFuzzy[3] ? ecFuzzy[2] : ecFuzzy[3];
		Pec = 2;
	}
	else if(ec > ecRule[3] && ec < ecRule[4])
	{
		ecFuzzy[3] = (ec - ecRule[4])/(ecRule[3] - ecRule[4]);
		ecFuzzy[4] = (ec - ecRule[3])/(ecRule[4] - ecRule[3]);
		ecFuzzy_Out[3] = ecFuzzy[3] > ecFuzzy[4] ? ecFuzzy[3] : ecFuzzy[4];
		Pec = 3;
	}
	else if(ec > ecRule[4] && ec < ecRule[5])
	{
		ecFuzzy[4] = (ec - ecRule[5])/(ecRule[4] - ecRule[5]);
		ecFuzzy[5] = (ec - ecRule[4])/(ecRule[5] - ecRule[4]);
		ecFuzzy_Out[4] = ecFuzzy[4] > ecFuzzy[5] ? ecFuzzy[4] : ecFuzzy[5];
		Pec = 4;
	}
	else if(ec > ecRule[5] && ec < ecRule[6])
	{
		ecFuzzy[5] = (ec - ecRule[6])/(ecRule[5] - ecRule[6]);
		ecFuzzy[6] = (ec - ecRule[5])/(ecRule[6] - ecRule[5]);
		ecFuzzy_Out[5] = ecFuzzy[5] > ecFuzzy[6] ? ecFuzzy[5] : ecFuzzy[6];
		Pec = 5;
	}
	else 
	{
		ecFuzzy_Out[5] = 1.0;
		Pec = 5;
	}
	//ecFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����ĳ�����û�м���ɵ�����
*
****************************************************************************/		
/*
	for ( i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			Rule[i][j] = -( eRule[i] + eRule[j] ) / 2;
			if ( Rule[i][j] < 0)
			{
				Rule[i][j] = floor ( Rule[i][j] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
			}
			else 
			{
				Rule[i][j] = ceil ( Rule[i][j] );//�����������ֵ��������ΪС��ʱ����ȡ��
			}
		}
	}
*/
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����һ������Ķ�ά���������ԣ��ڿ��ƹ��̵ĳ�ʼ�׶Σ�ϵͳ����������ϴ�
* ����ϵͳ����ҪĿ��������������ϣ�����ֵ�ڿ��ƹ����еļ�Ȩϵ��Ӧ��Щ��
* ��֮�����ƹ��������ȶ��׶Σ�ϵͳ����Ѿ���С������ϵͳ����Ҫ�����Ǽ�С��������
* ʹϵͳ�����ȶ������Ҫ���ڿ��ƹ����У������仯ֵ�ü�Ȩϵ������
* ��ʽ��ֻ��һ���ɵ��������޷�������һҪ��ġ���˿��Բ��������ɵ�����a1��a2�ķ�����
* ������Ե����ӵĳ���Ϊ a1<a2
* U1=-��a1E+��1-a1��EC������|E|<=m/2;
* U2=-��a2E+��1-a2��EC������|E|>m/2;
*
****************************************************************************/		
	for (xp = 0; xp < 7; xp++ )
	{
		for ( yp = 0; yp < 7; yp++)
		{
			if ( eRule[xp] > -1 && eRule[xp] < 1)
			{
				Rule[xp][yp] = -( a1 * eRule[xp] + ( 1 - a1 ) * eRule[yp] ) ;
				if ( Rule[xp][yp] < 0)
				{
					Rule[xp][yp] = floor ( Rule[xp][yp] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xp][yp] = ceil ( Rule[xp][yp] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
			else
			{
				Rule[xp][yp] = -( a2 * eRule[xp] + ( 1 - a2 ) * eRule[yp] ) ;
				if ( Rule[xp][yp] < 0)
				{
					Rule[xp][yp] = floor ( Rule[xp][yp] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xp][yp] = ceil ( Rule[xp][yp] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
		}
	}
/****************************************************************************
*
* ��ѯģ�������
*
****************************************************************************/		
	uFuzzy[0] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec];
	uFuzzy[1] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec];
	uFuzzy[2] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec + 1];
	uFuzzy[3] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec + 1];
	uFuzzy[4] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec];
	uFuzzy[5] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec - 1];
	uFuzzy[6] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec- 1];
/****************************************************************************
*
* ��ģ��
*
****************************************************************************/		
	fuzzy = uFuzzy[0] * uRule[0] + uFuzzy[1] * uRule[1] + uFuzzy[2] * uRule[2] 
			+ uFuzzy[3] * uRule[3] + uFuzzy[4] * uRule[4] + uFuzzy[5] * uRule[5]
			+ uFuzzy[6] * uRule[6];
	return fuzzy;
}

float FUZZY_Calc_Ki(float e,float ec,float e_max,float ec_max,float fuzzy_max)
{
	float eRule[7]  = {-e_max, -e_max * 0.667f, -e_max * 0.333f, 0, e_max * 0.333f, e_max * 0.667f, e_max};
	float ecRule[7] = {-ec_max, -ec_max * 0.667f, -ec_max * 0.333f, 0, ec_max * 0.333f, ec_max * 0.667f, ec_max};
	float uRule[7]  = {fuzzy_max, fuzzy_max * 0.667f, fuzzy_max * 0.333f, 0, fuzzy_max * 0.333f, fuzzy_max * 0.667f, fuzzy_max};
	
	float eFuzzy[7];
	float eFuzzy_Out[6];
	float ecFuzzy[7];	
	float ecFuzzy_Out[6];
	float uFuzzy[7];
	int   Pe,Pec;
	float Rule[7][7];
	float a1, a2;//����ģ�������Ŀɵ�����
  float fuzzy; //���ֵ
	/*int Rule[6][6]={{3, 2, 2, 1, 0, 0},
					{3, 2, 1, 1, 0, -1},
					{2, 2, 1, 0, -1, -1},
					{2, 1, 0, -1, -2, -2},
					{1, 0, -1, -1, -2, -2},
					{0, -1, -2, -2, -2, -3},
					};
	*/
	/*int Rule[7][7]={{3, 3, 2, 2, 1, 0, 0},
					{3, 3, 2, 1, 1, 0, -1},
					{2, 2, 2, 1, 0, -1, -1},
					{2, 2, 1, 0, -1, -2, -2},
					{1, 1, 0, -1, -1, -2, -2},
					{1, 0, -1, -2, -2, -2, -3},
					{0, 0, -2, -2, -2, -3, -3},
					};
	*/
	int i;
  static uint8_t xi = 0,yi = 0;
	for(i=0;i<7;i++)
	{
		eFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		ecFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		uFuzzy[i]=0;
	}
	for(i=0;i<2;i++)
	{
		eFuzzy_Out[i]=0;	
	}
	for(i=0;i<2;i++)
	{
		ecFuzzy_Out[i]=0;	
	}
/****************************************************************************
*
* ���������������
* ���������������������������������������
*
****************************************************************************/		
	if(e < eRule[0])
	{
		eFuzzy_Out[0] = 1.0;
		Pe = 0;
	}
	else if(e > eRule[0] && e < eRule[1])
	{
		eFuzzy[0] = (e - eRule[1])/(eRule[0] - eRule[1]);
		eFuzzy[1] = (e - eRule[0])/(eRule[1] - eRule[0]);
		eFuzzy_Out[0] = eFuzzy[0] > eFuzzy[1] ? eFuzzy[0] : eFuzzy[1];
		Pe = 0;
	}
	else if(e > eRule[1] && e < eRule[2])
	{
		eFuzzy[1] = (e - eRule[2])/(eRule[1] - eRule[2]);
		eFuzzy[2] = (e - eRule[1])/(eRule[2] - eRule[1]);
		eFuzzy_Out[1] = eFuzzy[1] > eFuzzy[2] ? eFuzzy[1] : eFuzzy[2];
		Pe = 1;
	}
	else if(e > eRule[2] && e < eRule[3])
	{
		eFuzzy[2] = (e - eRule[3])/(eRule[2] - eRule[3]);
		eFuzzy[3] = (e - eRule[2])/(eRule[3] - eRule[2]);
		eFuzzy_Out[2] = eFuzzy[2] > eFuzzy[3] ? eFuzzy[2] : eFuzzy[3];
		Pe = 2;
	}
	else if(e > eRule[3] && e < eRule[4])
	{
		eFuzzy[3] = (e - eRule[4])/(eRule[3] - eRule[4]);
		eFuzzy[4] = (e - eRule[3])/(eRule[4] - eRule[3]);
		eFuzzy_Out[3] = eFuzzy[3] > eFuzzy[4] ? eFuzzy[3] : eFuzzy[4];
		Pe = 3;
	}
	else if(e > eRule[4] && e < eRule[5])
	{
		eFuzzy[4] = (e - eRule[5])/(eRule[4] - eRule[5]);
		eFuzzy[5] = (e - eRule[4])/(eRule[5] - eRule[4]);
		eFuzzy_Out[4] = eFuzzy[4] > eFuzzy[5] ? eFuzzy[4] : eFuzzy[5];
		Pe = 4;
	}
	else if(e > eRule[5] && e < eRule[6])
	{
		eFuzzy[5] = (e - eRule[6])/(eRule[5] - eRule[6]);
		eFuzzy[6] = (e - eRule[5])/(eRule[6] - eRule[5]);
		eFuzzy_Out[5] = eFuzzy[5] > eFuzzy[6] ? eFuzzy[5] : eFuzzy[6];
		Pe =  5;
	}
	else 
	{
		eFuzzy_Out[5] = 1.0;
		Pe = 5;
	}	
	//eFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
	
/****************************************************************************
*
* ���仯������������
* ���仯����������������������������������
*
****************************************************************************/		
	if(ec < ecRule[0])
	{
		ecFuzzy_Out[0]=1.0;
		Pec = 0;
	}
	else if(ec > ecRule[0] && ec < ecRule[1])
	{
		ecFuzzy[0] = (ec - ecRule[1])/(ecRule[0] - ecRule[1]);
		ecFuzzy[1] = (ec - ecRule[0])/(ecRule[1] - ecRule[0]);
		ecFuzzy_Out[0] = ecFuzzy[0] > ecFuzzy[1] ? ecFuzzy[0] : ecFuzzy[1];
		Pec = 0;
	}
	else if(ec > ecRule[1] && ec < ecRule[2])
	{
		ecFuzzy[1] = (ec - ecRule[2])/(ecRule[1] - ecRule[2]);
		ecFuzzy[2] = (ec - ecRule[1])/(ecRule[2] - ecRule[1]);
		ecFuzzy_Out[1] = ecFuzzy[1] > ecFuzzy[2] ? ecFuzzy[1] : ecFuzzy[2];
		Pec = 1;
	}
	else if(ec > ecRule[2] && ec < ecRule[3])
	{
		ecFuzzy[2] = (ec - ecRule[3])/(ecRule[2] - ecRule[3]);
		ecFuzzy[3] = (ec - ecRule[2])/(ecRule[3] - ecRule[2]);
		ecFuzzy_Out[2] = ecFuzzy[2] > ecFuzzy[3] ? ecFuzzy[2] : ecFuzzy[3];
		Pec = 2;
	}
	else if(ec > ecRule[3] && ec < ecRule[4])
	{
		ecFuzzy[3] = (ec - ecRule[4])/(ecRule[3] - ecRule[4]);
		ecFuzzy[4] = (ec - ecRule[3])/(ecRule[4] - ecRule[3]);
		ecFuzzy_Out[3] = ecFuzzy[3] > ecFuzzy[4] ? ecFuzzy[3] : ecFuzzy[4];
		Pec = 3;
	}
	else if(ec > ecRule[4] && ec < ecRule[5])
	{
		ecFuzzy[4] = (ec - ecRule[5])/(ecRule[4] - ecRule[5]);
		ecFuzzy[5] = (ec - ecRule[4])/(ecRule[5] - ecRule[4]);
		ecFuzzy_Out[4] = ecFuzzy[4] > ecFuzzy[5] ? ecFuzzy[4] : ecFuzzy[5];
		Pec = 4;
	}
	else if(ec > ecRule[5] && ec < ecRule[6])
	{
		ecFuzzy[5] = (ec - ecRule[6])/(ecRule[5] - ecRule[6]);
		ecFuzzy[6] = (ec - ecRule[5])/(ecRule[6] - ecRule[5]);
		ecFuzzy_Out[5] = ecFuzzy[5] > ecFuzzy[6] ? ecFuzzy[5] : ecFuzzy[6];
		Pec = 5;
	}
	else 
	{
		ecFuzzy_Out[5] = 1.0;
		Pec = 5;
	}
	//ecFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����ĳ�����û�м���ɵ�����
*
****************************************************************************/		
/*
	for ( i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			Rule[i][j] = -( eRule[i] + eRule[j] ) / 2;
			if ( Rule[i][j] < 0)
			{
				Rule[i][j] = floor ( Rule[i][j] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
			}
			else 
			{
				Rule[i][j] = ceil ( Rule[i][j] );//�����������ֵ��������ΪС��ʱ����ȡ��
			}
		}
	}
*/
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����һ������Ķ�ά���������ԣ��ڿ��ƹ��̵ĳ�ʼ�׶Σ�ϵͳ����������ϴ�
* ����ϵͳ����ҪĿ��������������ϣ�����ֵ�ڿ��ƹ����еļ�Ȩϵ��Ӧ��Щ��
* ��֮�����ƹ��������ȶ��׶Σ�ϵͳ����Ѿ���С������ϵͳ����Ҫ�����Ǽ�С��������
* ʹϵͳ�����ȶ������Ҫ���ڿ��ƹ����У������仯ֵ�ü�Ȩϵ������
* ��ʽ��ֻ��һ���ɵ��������޷�������һҪ��ġ���˿��Բ��������ɵ�����a1��a2�ķ�����
* ������Ե����ӵĳ���Ϊ a1<a2
* U1=-��a1E+��1-a1��EC������|E|<=m/2;
* U2=-��a2E+��1-a2��EC������|E|>m/2;
*
****************************************************************************/		
	for (xi = 0; xi < 7; xi++ )
	{
		for ( yi = 0; yi < 7; yi++)
		{
			if ( eRule[xi] > -1 && eRule[xi] < 1)
			{
				Rule[xi][yi] = -( a1 * eRule[xi] + ( 1 - a1 ) * eRule[yi] ) ;
				if ( Rule[xi][yi] < 0)
				{
					Rule[xi][yi] = floor ( Rule[xi][yi] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xi][yi] = ceil ( Rule[xi][yi] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
			else
			{
				Rule[xi][yi] = -( a2 * eRule[xi] + ( 1 - a2 ) * eRule[yi] ) ;
				if ( Rule[xi][yi] < 0)
				{
					Rule[xi][yi] = floor ( Rule[xi][yi] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xi][yi] = ceil ( Rule[xi][yi] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
		}
	}
/****************************************************************************
*
* ��ѯģ�������
*
****************************************************************************/		
	uFuzzy[0] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec];
	uFuzzy[1] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec];
	uFuzzy[2] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec + 1];
	uFuzzy[3] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec + 1];
	uFuzzy[4] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec];
	uFuzzy[5] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec - 1];
	uFuzzy[6] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec- 1];
/****************************************************************************
*
* ��ģ��
*
****************************************************************************/		
	fuzzy = uFuzzy[0] * uRule[0] + uFuzzy[1] * uRule[1] + uFuzzy[2] * uRule[2] 
			+ uFuzzy[3] * uRule[3] + uFuzzy[4] * uRule[4] + uFuzzy[5] * uRule[5]
			+ uFuzzy[6] * uRule[6];
	return fuzzy;
}

float FUZZY_Calc_Kd(float e,float ec,float e_max,float ec_max,float fuzzy_max)
{
	float eRule[7]  = {-e_max, -e_max * 0.667f, -e_max * 0.333f, 0, e_max * 0.333f, e_max * 0.667f, e_max};
	float ecRule[7] = {-ec_max, -ec_max * 0.667f, -ec_max * 0.333f, 0, ec_max * 0.333f, ec_max * 0.667f, ec_max};
	float uRule[7]  = {fuzzy_max, fuzzy_max * 0.667f, fuzzy_max * 0.333f, 0, fuzzy_max * 0.333f, fuzzy_max * 0.667f, fuzzy_max};
	
	float eFuzzy[7];
	float eFuzzy_Out[6];
	float ecFuzzy[7];	
	float ecFuzzy_Out[6];
	float uFuzzy[7];
	int   Pe,Pec;
	float Rule[7][7];
	float a1, a2;//����ģ�������Ŀɵ�����
  float fuzzy; //���ֵ
	/*int Rule[6][6]={{3, 2, 2, 1, 0, 0},
					{3, 2, 1, 1, 0, -1},
					{2, 2, 1, 0, -1, -1},
					{2, 1, 0, -1, -2, -2},
					{1, 0, -1, -1, -2, -2},
					{0, -1, -2, -2, -2, -3},
					};
	*/
	/*int Rule[7][7]={{3, 3, 2, 2, 1, 0, 0},
					{3, 3, 2, 1, 1, 0, -1},
					{2, 2, 2, 1, 0, -1, -1},
					{2, 2, 1, 0, -1, -2, -2},
					{1, 1, 0, -1, -1, -2, -2},
					{1, 0, -1, -2, -2, -2, -3},
					{0, 0, -2, -2, -2, -3, -3},
					};
	*/
	int i;
  static uint8_t xd = 0,yd = 0;
	for(i=0;i<7;i++)
	{
		eFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		ecFuzzy[i]=0;
	}
	for(i=0;i<7;i++)
	{
		uFuzzy[i]=0;
	}
	for(i=0;i<2;i++)
	{
		eFuzzy_Out[i]=0;	
	}
	for(i=0;i<2;i++)
	{
		ecFuzzy_Out[i]=0;	
	}
/****************************************************************************
*
* ���������������
* ���������������������������������������
*
****************************************************************************/		
	if(e < eRule[0])
	{
		eFuzzy_Out[0] = 1.0;
		Pe = 0;
	}
	else if(e > eRule[0] && e < eRule[1])
	{
		eFuzzy[0] = (e - eRule[1])/(eRule[0] - eRule[1]);
		eFuzzy[1] = (e - eRule[0])/(eRule[1] - eRule[0]);
		eFuzzy_Out[0] = eFuzzy[0] > eFuzzy[1] ? eFuzzy[0] : eFuzzy[1];
		Pe = 0;
	}
	else if(e > eRule[1] && e < eRule[2])
	{
		eFuzzy[1] = (e - eRule[2])/(eRule[1] - eRule[2]);
		eFuzzy[2] = (e - eRule[1])/(eRule[2] - eRule[1]);
		eFuzzy_Out[1] = eFuzzy[1] > eFuzzy[2] ? eFuzzy[1] : eFuzzy[2];
		Pe = 1;
	}
	else if(e > eRule[2] && e < eRule[3])
	{
		eFuzzy[2] = (e - eRule[3])/(eRule[2] - eRule[3]);
		eFuzzy[3] = (e - eRule[2])/(eRule[3] - eRule[2]);
		eFuzzy_Out[2] = eFuzzy[2] > eFuzzy[3] ? eFuzzy[2] : eFuzzy[3];
		Pe = 2;
	}
	else if(e > eRule[3] && e < eRule[4])
	{
		eFuzzy[3] = (e - eRule[4])/(eRule[3] - eRule[4]);
		eFuzzy[4] = (e - eRule[3])/(eRule[4] - eRule[3]);
		eFuzzy_Out[3] = eFuzzy[3] > eFuzzy[4] ? eFuzzy[3] : eFuzzy[4];
		Pe = 3;
	}
	else if(e > eRule[4] && e < eRule[5])
	{
		eFuzzy[4] = (e - eRule[5])/(eRule[4] - eRule[5]);
		eFuzzy[5] = (e - eRule[4])/(eRule[5] - eRule[4]);
		eFuzzy_Out[4] = eFuzzy[4] > eFuzzy[5] ? eFuzzy[4] : eFuzzy[5];
		Pe = 4;
	}
	else if(e > eRule[5] && e < eRule[6])
	{
		eFuzzy[5] = (e - eRule[6])/(eRule[5] - eRule[6]);
		eFuzzy[6] = (e - eRule[5])/(eRule[6] - eRule[5]);
		eFuzzy_Out[5] = eFuzzy[5] > eFuzzy[6] ? eFuzzy[5] : eFuzzy[6];
		Pe =  5;
	}
	else 
	{
		eFuzzy_Out[5] = 1.0;
		Pe = 5;
	}	
	//eFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
	
/****************************************************************************
*
* ���仯������������
* ���仯����������������������������������
*
****************************************************************************/		
	if(ec < ecRule[0])
	{
		ecFuzzy_Out[0]=1.0;
		Pec = 0;
	}
	else if(ec > ecRule[0] && ec < ecRule[1])
	{
		ecFuzzy[0] = (ec - ecRule[1])/(ecRule[0] - ecRule[1]);
		ecFuzzy[1] = (ec - ecRule[0])/(ecRule[1] - ecRule[0]);
		ecFuzzy_Out[0] = ecFuzzy[0] > ecFuzzy[1] ? ecFuzzy[0] : ecFuzzy[1];
		Pec = 0;
	}
	else if(ec > ecRule[1] && ec < ecRule[2])
	{
		ecFuzzy[1] = (ec - ecRule[2])/(ecRule[1] - ecRule[2]);
		ecFuzzy[2] = (ec - ecRule[1])/(ecRule[2] - ecRule[1]);
		ecFuzzy_Out[1] = ecFuzzy[1] > ecFuzzy[2] ? ecFuzzy[1] : ecFuzzy[2];
		Pec = 1;
	}
	else if(ec > ecRule[2] && ec < ecRule[3])
	{
		ecFuzzy[2] = (ec - ecRule[3])/(ecRule[2] - ecRule[3]);
		ecFuzzy[3] = (ec - ecRule[2])/(ecRule[3] - ecRule[2]);
		ecFuzzy_Out[2] = ecFuzzy[2] > ecFuzzy[3] ? ecFuzzy[2] : ecFuzzy[3];
		Pec = 2;
	}
	else if(ec > ecRule[3] && ec < ecRule[4])
	{
		ecFuzzy[3] = (ec - ecRule[4])/(ecRule[3] - ecRule[4]);
		ecFuzzy[4] = (ec - ecRule[3])/(ecRule[4] - ecRule[3]);
		ecFuzzy_Out[3] = ecFuzzy[3] > ecFuzzy[4] ? ecFuzzy[3] : ecFuzzy[4];
		Pec = 3;
	}
	else if(ec > ecRule[4] && ec < ecRule[5])
	{
		ecFuzzy[4] = (ec - ecRule[5])/(ecRule[4] - ecRule[5]);
		ecFuzzy[5] = (ec - ecRule[4])/(ecRule[5] - ecRule[4]);
		ecFuzzy_Out[4] = ecFuzzy[4] > ecFuzzy[5] ? ecFuzzy[4] : ecFuzzy[5];
		Pec = 4;
	}
	else if(ec > ecRule[5] && ec < ecRule[6])
	{
		ecFuzzy[5] = (ec - ecRule[6])/(ecRule[5] - ecRule[6]);
		ecFuzzy[6] = (ec - ecRule[5])/(ecRule[6] - ecRule[5]);
		ecFuzzy_Out[5] = ecFuzzy[5] > ecFuzzy[6] ? ecFuzzy[5] : ecFuzzy[6];
		Pec = 5;
	}
	else 
	{
		ecFuzzy_Out[5] = 1.0;
		Pec = 5;
	}
	//ecFuzzy_Out[1] = 1.0 - eFuzzy_Out[0];
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����ĳ�����û�м���ɵ�����
*
****************************************************************************/		
/*
	for ( i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			Rule[i][j] = -( eRule[i] + eRule[j] ) / 2;
			if ( Rule[i][j] < 0)
			{
				Rule[i][j] = floor ( Rule[i][j] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
			}
			else 
			{
				Rule[i][j] = ceil ( Rule[i][j] );//�����������ֵ��������ΪС��ʱ����ȡ��
			}
		}
	}
*/
/****************************************************************************
*
* ����ģ�������
* ģ���������Բ��ù�ʽU=-��E+EC��/2����
* ��ʽ���ɵĹ����һ�����ɲ����޸ģ������ڴ�ʽ�Ļ����ϼ���ɵ�����a
* U=-��aE+��1-a��EC��/2��a��ȡֵ��Χ��0��1֮��
* ����һ������Ķ�ά���������ԣ��ڿ��ƹ��̵ĳ�ʼ�׶Σ�ϵͳ����������ϴ�
* ����ϵͳ����ҪĿ��������������ϣ�����ֵ�ڿ��ƹ����еļ�Ȩϵ��Ӧ��Щ��
* ��֮�����ƹ��������ȶ��׶Σ�ϵͳ����Ѿ���С������ϵͳ����Ҫ�����Ǽ�С��������
* ʹϵͳ�����ȶ������Ҫ���ڿ��ƹ����У������仯ֵ�ü�Ȩϵ������
* ��ʽ��ֻ��һ���ɵ��������޷�������һҪ��ġ���˿��Բ��������ɵ�����a1��a2�ķ�����
* ������Ե����ӵĳ���Ϊ a1<a2
* U1=-��a1E+��1-a1��EC������|E|<=m/2;
* U2=-��a2E+��1-a2��EC������|E|>m/2;
*
****************************************************************************/		
	for (xd = 0; xd < 7; xd++ )
	{
		for ( yd = 0; yd < 7; yd++)
		{
			if ( eRule[xd] > -1 && eRule[xd] < 1)
			{
				Rule[xd][yd] = -( a1 * eRule[xd] + ( 1 - a1 ) * eRule[yd] ) ;
				if ( Rule[xd][yd] < 0)
				{
					Rule[xd][yd] = floor ( Rule[xd][yd] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xd][yd] = ceil ( Rule[xd][yd] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
			else
			{
				Rule[xd][yd] = -( a2 * eRule[xd] + ( 1 - a2 ) * eRule[yd] ) ;
				if ( Rule[xd][yd] < 0)
				{
					Rule[xd][yd] = floor ( Rule[xd][yd] );//�����������ֵ�Ǹ�����ΪС��ʱ����ȡ��
				}
				else 
				{
					Rule[xd][yd] = ceil ( Rule[xd][yd] );//�����������ֵ��������ΪС��ʱ����ȡ��
				}
			}
		}
	}
/****************************************************************************
*
* ��ѯģ�������
*
****************************************************************************/		
	uFuzzy[0] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec];
	uFuzzy[1] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec];
	uFuzzy[2] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec + 1];
	uFuzzy[3] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe + 1][Pec + 1];
	uFuzzy[4] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec];
	uFuzzy[5] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe][Pec - 1];
	uFuzzy[6] = eFuzzy_Out[Pe] * ecFuzzy_Out[Pec] * Rule[Pe - 1][Pec- 1];
/****************************************************************************
*
* ��ģ��
*
****************************************************************************/		
	fuzzy = uFuzzy[0] * uRule[0] + uFuzzy[1] * uRule[1] + uFuzzy[2] * uRule[2] 
			+ uFuzzy[3] * uRule[3] + uFuzzy[4] * uRule[4] + uFuzzy[5] * uRule[5]
			+ uFuzzy[6] * uRule[6];
	return fuzzy;
}





#include "./DMP/DMP.h"
#include "./usart/bsp_usart.h"
#include "./usart/send_data_to_ano.h"
#include "math.h"
#include "./eMPL/inv_mpu.h"
#include "./eMPL/inv_mpu_dmp_motion_driver.h"
#include "./eMPL/dmpKey.h"
#include "./eMPL/dmpmap.h"

#define DEFAULT_MPU_HZ  (1000)//MPU采样频率（4~1000）
#define DEFAULT_DMP_HZ  (200)//DMP输出频率
#define q30  1073741824.0f//2^30 DMP输出的四元数扩大了2^30倍

extern u8 NewGyro;

short gyro_dmp[3], accel_dmp[3], sensors;
float Pitch,Roll,Yaw; 
float q0_dmp=1.0f,q1_dmp=0.0f,q2_dmp=0.0f,q3_dmp=0.0f;

static signed char gyro_orientation[9] = {1, 0, 0,
                                           0,1, 0,
                                           0, 0, 1};

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


static  unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);//Gyro biases in q16 format.Accel biases (if applicable) in q16 format.
    if (result == 0x7) //自检通过
    {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the offset registers.经过这个步骤后，读gyro,accel对应的寄存器得到的将是直接经过校正的值，DMP的采样值也是经过校正的
         */
        
        //将校正值写入offset registers
         unsigned char i = 0;

        for(i = 0; i<3; i++) {
        	gyro[i] = (long)(gyro[i] * 32.8f); //convert to +-1000dps
        	accel[i] *= 2048.f; //convert to +-16G
        	accel[i] = accel[i] >> 16;
        	gyro[i] = (long)(gyro[i] >> 16);
        }

        mpu_set_gyro_bias_reg(gyro);  //Bias inputs are LSB in +-1000dps format.
        mpu_set_accel_bias_6050_reg(accel);  //Bias inputs are LSB in +-16G format.
		printf("setting bias succesfully ......\r\n");
    }
}

void DMP_Init(void)
{ 
	struct int_param_s int_param={NULL};
    
    unsigned short dmp_features=DMP_FEATURE_6X_LP_QUAT |DMP_FEATURE_GYRO_CAL|DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO;//DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |DMP_FEATURE_GYRO_CAL)
	printf("Test......\r\n");
    
    if(!mpu_init(&int_param))
    {
        if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  	printf("mpu_set_sensor complete ......\r\n");
//	    if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
//	  	 printf("mpu_configure_fifo complete ......\r\n");
        if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))
	  	 printf("mpu_set_sample_rate complete ......\r\n");
        if(!dmp_load_motion_driver_firmware())
	  	printf("dmp_load_motion_driver_firmware complete ......\r\n");
        if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
	  	 printf("dmp_set_orientation complete ......\r\n");
        if(!dmp_enable_feature(dmp_features))
	  	 printf("dmp_enable_feature complete ......\r\n");
        if(!dmp_set_fifo_rate(DEFAULT_DMP_HZ))
	  	 printf("dmp_set_fifo_rate complete ......\r\n");
        run_self_test();
        if(!mpu_set_dmp_state(1))
	  	 printf("mpu_set_dmp_state complete ......\r\n");
  }
}

void Read_DMP(void)
{	
    if(NewGyro==1)
	{
        unsigned long sensor_timestamp;
        unsigned char more;
        long quat[4];
        dmp_read_fifo(gyro_dmp, accel_dmp, quat, &sensor_timestamp, &sensors, &more);
            
        if (sensors & INV_WXYZ_QUAT )
        {    
            q0_dmp=quat[0] / q30;
            q1_dmp=quat[1] / q30;
            q2_dmp=quat[2] / q30;
            q3_dmp=quat[3] / q30;
            Pitch = asin(-2 * q1_dmp * q3_dmp + 2 * q0_dmp* q2_dmp)* RADIAN_TO_ANGLE;
            Roll=atan2(2 * q2_dmp * q3_dmp + 2 * q0_dmp * q1_dmp, -2 * q1_dmp * q1_dmp - 2 * q2_dmp* q2_dmp + 1)* RADIAN_TO_ANGLE; 
            Yaw=atan2(2*(q1_dmp*q2_dmp + q0_dmp*q3_dmp),q0_dmp*q0_dmp+q1_dmp*q1_dmp-q2_dmp*q2_dmp-q3_dmp*q3_dmp) * RADIAN_TO_ANGLE; 				
           Data_Send_Status(Roll,Pitch,Yaw);
        }
        
        NewGyro=0;
    }

}

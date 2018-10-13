/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"

/* USER CODE BEGIN 0 */
#include "Pixy_Camera.h"
#include "AX-12A.h"
unsigned int  USART_Counter=0;

/*Pixy变量*/
uint8_t RePixy_buf[18],Re_Counter = 0;
uint8_t ReSign_OK = 0;
uint8_t Pixy_Temp[18] = {0};
uint8_t USART1_FAIL = 0;	//通信失败标志、帧头错误置高
static uint8_t Pixy_times = 4;
extern int32_t Pixy_Pos_XY[2][5];
extern Pixy_Color Pixy;

/*激光测距变量*/
float Distance = 0;				       //距离
uint8_t Laser_buff[20] = {0};    //缓存
uint8_t buff = 0;


/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  osSystickHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
  
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
* @brief This function handles UART4 global interrupt.
*/
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
* @brief This function handles UART5 global interrupt.
*/
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */

  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART1)  //PIXY接受中断
  {
    HAL_UART_Receive_IT(&huart1,&Pixy_Temp[Re_Counter],1);
  
		if(Re_Counter == 0 && Pixy_Temp[0] != 0x55 && Pixy_Temp[0] != 0x56)  USART1_FAIL = 1; //如果不是帧头返回
		if(USART1_FAIL == 0)//通信成功
		{
			 Re_Counter++;
			if(Re_Counter >= 14)
			{
					/* 单一色 1个：帧头为55 aa 55 aa
					单一色 2个：面积大的先发，帧头为55 aa 55 aa  ，下一个帧头为55 aa
					CC模式 1个：帧头为55 aa 56 aa
					CC模式+单一模式 各1个：先发单一模式，帧头为55 aa 55 aa，后发CC模式，帧头为56 aa
					CC模式 2个：帧头为55 aa 56 aa (此情况不准，两个标记会产生结合，角度几乎不对)			  
					*/
				
					//单一色1个   16个数据
					if(Pixy_Temp[0] == 0x55 && Pixy_Temp[1] == 0xAA && Pixy_Temp[2] == 0x55 && Pixy_Temp[3] == 0xAA && Re_Counter == 16)
					{
            *RePixy_buf = *Pixy_Temp;
						Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
						ReSign_OK = 0x01;
					}
						//CC模式       18个数据
					else if(Pixy_Temp[0] == 0x55 && Pixy_Temp[1] == 0xAA && Pixy_Temp[2] == 0x56 && Pixy_Temp[3] == 0xAA && Re_Counter == 18)
					{
						*RePixy_buf = *Pixy_Temp;
						Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
						ReSign_OK = 0x03;
					}
					//单一色2个   14个数据
					else if(Pixy_Temp[0] == 0x55 && Pixy_Temp[1] == 0xAA && Pixy_Temp[2] != 0x55 && Pixy_Temp[2] != 0x56 && Re_Counter == 14)
					{
						*RePixy_buf = *Pixy_Temp;
						Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
						ReSign_OK = 0x02;
					}
					//CC模式+单一模式   16个数据
					else if(Pixy_Temp[0] == 0x56 && Pixy_Temp[1] == 0xAA && Re_Counter == 16)
					{
						*RePixy_buf = *Pixy_Temp;
						Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
						ReSign_OK = 0x04;
					}
		    }
				
	    }
		else 
		{
			   USART1_FAIL=0;
			   Re_Counter=0;
		}
	
		
    Pixy_Pos_XY[0][Pixy_times] = Pixy.Pixy_Color_PosX;	//最新数据存在高位
    Pixy_Pos_XY[1][Pixy_times] = Pixy.Pixy_Color_PosY;	
    Pixy_times++;
    if(Pixy_times == 5)
    {
      Pixy_times = 0;
    }
    
    HAL_UART_Receive_IT(&huart1,&Pixy_Temp[Re_Counter],1);
  }
  else if(huart->Instance == UART4)  //激光测距接收中断
  {
    static uint8_t step = 0,high = 0,low = 0;
    switch(step)
    {
      case 0:
              if(buff == 0X5A)
                  {
                    step++;
                    break;
                  }
              else break;
      case 1:
              if(buff == 0X5A)
                {
                  step++;
                  break;
                }
              else break;
      case 2:
              if(buff == 0X15)
                {
                  step++;
                  break;
                }
              else break;
      case 3:
              if(buff == 0X03)
                {
                  step++;
                  break;
                }
              else break;
      case 4:
              high = buff;
              step++;
              break;
      case 5:
              low = buff;
              step++;
              break;
      case 6:
              if(buff == 0x03 || buff == 0x02 || buff == 0x01 || buff == 0x00)
                {
                  step++;
                  break;
                }
              else break;
      case 7:if(buff == ((0x5a + 0x5a + 0x15 +0x03 + high + low + 0x03) & 0xff))
                {
                  Distance = high << 8 | low;
                  step = 0;
                  break;
                }
              else break;
    }
        
    HAL_UART_Receive_IT(&huart4,&buff,1);
    
//    uint8_t sum = 0;
//    uint8_t num = 0;

//	if(Laser_buff[3] == 3)
//	{

//		for(sum = 0,num = 0;num < Laser_buff[3] + 4;num++)
//		{
//			sum += Laser_buff[num];    //这里校验和仅对照低八位
//		}
//		//校验正确进行赋值
//		if(Laser_buff[7] == sum)
//		{
//			Distance = Laser_buff[4] << 8 | Laser_buff[5];//接收完成
//		}	
//	}else
//	{
//		for(sum = 0,num = 0;num < Laser_buff[3] + 4;num++)
//		{
//			sum += Laser_buff[num];    //这里校验和仅对照低八位
//		}
//		//校验正确进行赋值
//		if(Laser_buff[8] == sum)
//		{

//			//十三字节如何接收？
//	
//		}
//			
//  }
//   HAL_UART_Receive_IT(&huart4,Laser_buff,8);
 }
  
   
  
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == UART5)
  {
      /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

    /* Enable the UART Parity Error and Data Register not empty Interrupts */
    SET_BIT(huart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
  }
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* 0xWS2812 16-Channel WS2812 interface library
 * 
 * Copyright (c) 2014 Elia Ritterbusch, http://eliaselectronics.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "stm32f10x_lib.h"
#include "stdio.h"
#include "stdlib.h"
//#include "stm32f10x.h"

/* this define sets the number of TIM2 overflows
 * to append to the data frame for the LEDs to 
 * load the received data into their registers */
#define WS2812_DEADPERIOD 19

#define LED_NUMBER 26                                                                                                                                                                                                                                                                                                                                                    
#define LED_BUFFER_SIZE (24 * LED_NUMBER)

u16 WS2812_IO_High = 0xFFFF;
u16 WS2812_IO_Low = 0x0000;

volatile u8 WS2812_TC = 1;
volatile u8 TIM2_overflows = 0;

/* WS2812 framebuffer
 * buffersize = (#LEDs / 16) * 24 */
//u16 WS2812_IO_framedata[48];
u16 WS2812_IO_framedata[LED_BUFFER_SIZE];

/* Array defining 12 color triplets to be displayed */
u8 colors[12][3] = 
{
	{0xFF, 0x00, 0x00},
	{0xFF, 0x80, 0x00},
	{0xFF, 0xFF, 0x00},
	{0x80, 0xFF, 0x00},
	{0x00, 0xFF, 0x00},
	{0x00, 0xFF, 0x80},
	{0x00, 0xFF, 0xFF},
	{0x00, 0x80, 0xFF},
	{0x00, 0x00, 0xFF},
	{0x80, 0x00, 0xFF},
	{0xFF, 0x00, 0xFF},
	{0xFF, 0x00, 0x80}
};



/* simple delay counter to waste time, don't rely on for accurate timing */
void Delay(u32 nCount) {
  while(nCount--) {
  }
}

/*******************************************************************************
* 函数名	: RCC_Configuration
* 函数描述  : 设置系统各部分时钟
* 输入参数  : 无
* 输出结果  : 无
* 返回值    : 无
*******************************************************************************/

void RCC_Configuration(void)
{
	/* 定义枚举类型变量 HSEStartUpStatus */
	ErrorStatus HSEStartUpStatus;

  	/* 复位系统时钟设置*/
  	RCC_DeInit();

  	/* 开启HSE*/
  	RCC_HSEConfig(RCC_HSE_ON);

  	/* 等待HSE起振并稳定*/
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	/* 判断HSE起是否振成功，是则进入if()内部 */
  	if(HSEStartUpStatus == SUCCESS)
  	{
    	/* 选择HCLK（AHB）时钟源为SYSCLK 1分频 */
    	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    	/* 选择PCLK2时钟源为 HCLK（AHB） 1分频 */
    	RCC_PCLK2Config(RCC_HCLK_Div1); 

    	/* 选择PCLK1时钟源为 HCLK（AHB） 2分频 */
    	RCC_PCLK1Config(RCC_HCLK_Div2);

    	/* 设置FLASH延时周期数为2 */
    	FLASH_SetLatency(FLASH_Latency_2);
    	/* 使能FLASH预取缓存 */
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    	/* 选择锁相环（PLL）时钟源为HSE 1分频，倍频数为9，则PLL输出频率为 8MHz * 9 = 72MHz */
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    	/* 使能PLL */ 
    	RCC_PLLCmd(ENABLE);

    	/* 等待PLL输出稳定 */
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	/* 选择SYSCLK时钟源为PLL */
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	/* 等待PLL成为SYSCLK时钟源 */
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}
   
  	/* 打开APB2总线上的GPIOA时钟*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1 , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB, ENABLE);
}

/******************************************************************************
* 函数名  		: Systick_Configuration
* 函数描述    	: 设置Systick定时器,重装载时间为1s
* 输入参数      : 无
* 输出结果      : 无
* 返回值        : 无
******************************************************************************/
void Systick_Configuration(void)
{
    /* 失能Systick定时器 */
    SysTick_CounterCmd(SysTick_Counter_Disable);
    /* 选择HCLK为Systick时钟源 */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    /* 清除Systick计数器 */
    SysTick_CounterCmd(SysTick_Counter_Clear);
    /* 主频为72/8MHz，配置计数值为9000 * 1000可以得到1s定时间隔*/
    SysTick_SetReload(9000 * 1000);			
}


/******************************************************************************
* 函数名  		: Delay_Second
* 函数描述    	: 1s定时
* 输入参数      : 无
* 输出结果      : 无
* 返回值        : 无
******************************************************************************/
void Delay_Second(void)
{
    /* 启动Systick计数 */
    SysTick_CounterCmd(SysTick_Counter_Enable);
    /* 等待Systick计数至0 */
    while(SysTick_GetFlagStatus(SysTick_FLAG_COUNT) == 0);
    /* 失能Systick定时器 */
    SysTick_CounterCmd(SysTick_Counter_Disable);
    /* 清除Systick计数器 */
    SysTick_CounterCmd(SysTick_Counter_Clear);
}

///////////////////////////////////////////////////////////////////////////

void GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// GPIOA Periph clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// GPIOA pins WS2812 data outputs
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  /* 设置PD2口为推挽输出，最大翻转频率为50MHz*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		/* 设置USART1的Tx脚（PA.9）为第二功能推挽输出模式 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
    /* 设置USART1的Rx脚（PA.10）为浮空输入脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
}

/*******************************************************************************
* 函数名  		: USART_Configuration
* 函数描述    	: 设置USART1
* 输入参数      : None
* 输出结果      : None
* 返回值        : None
*******************************************************************************/
void USART_Configuration(void)
{
    /* 定义USART初始化结构体 USART_InitStructure */
    USART_InitTypeDef USART_InitStructure;
    
    /*	
    *	波特率为9600bps
    *	8位数据长度
    *	1个停止位，无校验
    *	禁用硬件流控制
    *	禁止USART时钟
    *	时钟极性低
    *	在第2个边沿捕获数据
    *	最后一位数据的时钟脉冲不从 SCLK 输出
    */ 
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1 , &USART_InitStructure);
	
		/* enable usart transmit interrupt */
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    /* 使能USART1 */
    USART_Cmd(USART1 , ENABLE);
}

void TIM2_init(void)
{
	u32 SystemCoreClock = 72000000;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	u16 PrescalerValue;
	
	// TIM2 Periph clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	PrescalerValue = (u16) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 29; // 800kHz
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(TIM2, DISABLE);

	/* Timing Mode configuration: Channel 1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 8;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);	

	/* Timing Mode configuration: Channel 2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 17;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
	

}

void DMA_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// TIM2 Update event
	/* DMA1 Channel2 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&GPIOB->ODR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)WS2812_IO_High;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	
	// TIM2 CC1 event
	/* DMA1 Channel5 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&GPIOB->ODR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)WS2812_IO_framedata;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	
	// TIM2 CC2 event
	/* DMA1 Channel7 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel7);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&GPIOB->ODR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)WS2812_IO_Low;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel7, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);

}

void NVIC_Configure()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* configure TIM2 interrupt */
	//NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	#if 1
	/* configure DMA1 Channel7 interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* enable DMA1 Channel7 transfer complete interrupt */
	#endif
	
	#if 1
	/* Enable USART1 interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#endif
}

/* Transmit the frambuffer with buffersize number of bytes to the LEDs 
 * buffersize = (#LEDs / 16) * 24 */
void WS2812_sendbuf(u32 buffersize)
{		
	// transmission complete flag, indicate that transmission is taking place
	WS2812_TC = 0;
	
	// clear all relevant DMA flags
	DMA_ClearFlag(DMA1_FLAG_TC2 | DMA1_FLAG_HT2 | DMA1_FLAG_GL2 | DMA1_FLAG_TE2);
	DMA_ClearFlag(DMA1_FLAG_TC5 | DMA1_FLAG_HT5 | DMA1_FLAG_GL5 | DMA1_FLAG_TE5);
	DMA_ClearFlag(DMA1_FLAG_HT7 | DMA1_FLAG_GL7 | DMA1_FLAG_TE7);
	
	
	#if 1
	// configure the number of bytes to be transferred by the DMA controller
	DMA_SetCurrDataCounter(DMA1_Channel2, buffersize);
	DMA_SetCurrDataCounter(DMA1_Channel5, buffersize);
	DMA_SetCurrDataCounter(DMA1_Channel7, buffersize);
	#endif
	
	// clear all TIM2 flags
	TIM2->SR = 0;
	//currDataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);
	// enable the corresponding DMA channels
	DMA_Cmd(DMA1_Channel2, ENABLE);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	DMA_Cmd(DMA1_Channel7, ENABLE);
	//currDataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);
	
	// IMPORTANT: enable the TIM2 DMA requests AFTER enabling the DMA channels!
	TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE);
	TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE);
	TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
	
	
	//while (currDataCounter != 0)
	//{
	//		;
	//}
	
	
	// preload counter with 29 so TIM2 generates UEV directly to start DMA transfer
	TIM_SetCounter(TIM2, 29);
	
	// start TIM2
	TIM_Cmd(TIM2, ENABLE);
}

/* DMA1 Channel7 Interrupt Handler gets executed once the complete framebuffer has been transmitted to the LEDs */
void DMA1_Channel7_IRQHandler(void)
{
	// clear DMA7 transfer complete interrupt flag
	DMA_ClearITPendingBit(DMA1_IT_TC7);	
	// enable TIM2 Update interrupt to append 50us dead period
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// disable the DMA channels
	DMA_Cmd(DMA1_Channel2, DISABLE);	
	DMA_Cmd(DMA1_Channel5, DISABLE);
	DMA_Cmd(DMA1_Channel7, DISABLE);
	// IMPORTANT: disable the DMA requests, too!
	TIM_DMACmd(TIM2, TIM_DMA_CC1, DISABLE);
	TIM_DMACmd(TIM2, TIM_DMA_CC2, DISABLE);
	TIM_DMACmd(TIM2, TIM_DMA_Update, DISABLE);
	
	//currDataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);
	
}

/* TIM2 Interrupt Handler gets executed on every TIM2 Update if enabled */
void TIM2_IRQHandler(void)
{
	// Clear TIM2 Interrupt Flag
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	/* check if certain number of overflows has occured yet 
	 * this ISR is used to guarantee a 50us dead time on the data lines
	 * before another frame is transmitted */
	if (TIM2_overflows < (u8)WS2812_DEADPERIOD)
	{
		// count the number of occured overflows
		TIM2_overflows++;
	}
	else
	{
		// clear the number of overflows
		TIM2_overflows = 0;	
		// stop TIM2 now because dead period has been reached
		TIM_Cmd(TIM2, DISABLE);
		/* disable the TIM2 Update interrupt again 
		 * so it doesn't occur while transmitting data */
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		// finally indicate that the data frame has been transmitted
		WS2812_TC = 1; 	
	}
}



/* This function sets the color of a single pixel in the framebuffer 
 * 
 * Arguments:
 * row = the channel number/LED strip the pixel is in from 0 to 15
 * column = the column/LED position in the LED string from 0 to number of LEDs per strip
 * red, green, blue = the RGB color triplet that the pixel should display 
 */
void WS2812_framedata_setPixel(u8 row, u16 column, u8 red, u8 green, u8 blue)
{
	u8 i;
	for (i = 0; i < 8; i++)
	{
		// clear the data for pixel 
		
		/* each unit in WS2812_IO_framedata denote one whole whole piexl range.  */
		/* this operation only set the appoint pixel led, do not clean the others */
		WS2812_IO_framedata[((column*24)+i)] &= ~(0x01<<row);
		WS2812_IO_framedata[((column*24)+8+i)] &= ~(0x01<<row);
		WS2812_IO_framedata[((column*24)+16+i)] &= ~(0x01<<row);
		// write new data for pixel
		WS2812_IO_framedata[((column*24)+i)] |= ((((green<<i) & 0x80)>>7)<<row);
		WS2812_IO_framedata[((column*24)+8+i)] |= ((((red<<i) & 0x80)>>7)<<row);
		WS2812_IO_framedata[((column*24)+16+i)] |= ((((blue<<i) & 0x80)>>7)<<row);
	}
}

/* clean all of pixels */
void WS2812_clean_all_pixel()
{
	u32 i = 0;
	
	for (i = 0; i < LED_BUFFER_SIZE; i++)
	{
		WS2812_IO_framedata[i] = 0;
	}
}

/* This function is a wrapper function to set all LEDs in the complete row to the specified color
 * 
 * Arguments:
 * row = the channel number/LED strip to set the color of from 0 to 15
 * columns = the number of LEDs in the strip to set to the color from 0 to number of LEDs per strip
 * red, green, blue = the RGB color triplet that the pixels should display 
 */
void WS2812_framedata_setRow(u8 row, u16 columns, u8 red, u8 green, u8 blue)
{
	u8 i;
	for (i = 0; i < columns; i++)
	{
		WS2812_framedata_setPixel(row, i, red, green, blue);
	}
}

/* This function is a wrapper function to set all the LEDs in the column to the specified color
 * 
 * Arguments:
 * rows = the number of channels/LED strips to set the row in from 0 to 15
 * column = the column/LED position in the LED string from 0 to number of LEDs per strip
 * red, green, blue = the RGB color triplet that the pixels should display 
 */
void WS2812_framedata_setColumn(u8 rows, u16 column, u8 red, u8 green, u8 blue)
{
	u8 i;
	for (i = 0; i < rows; i++)
	{
		WS2812_framedata_setPixel(i, column, red, green, blue);
	}
}

/************************/
#if 0
#define STDIO_COM USART1

int fputc(int ch, FILE *f) //
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(STDIO_COM, (u8)ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(STDIO_COM, USART_FLAG_TC) == RESET);

	return ch; //
}
#endif

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

static u8 RxData[16] = {0};
static u8 RxCnt = 0;
#define NUMBER_LENGTH 3
void USART1_IRQHandler(void)
{
	u32 i = 0;

	u8 cNum[NUMBER_LENGTH] = {0};
	s32 led_index = 10000;

	
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
 {
    /* Read one byte from the receive data register */
    RxData[RxCnt] = USART_ReceiveData(USART1);
	 
		if (RxData[RxCnt] < 48 || RxData[RxCnt] > 57)
		{
			#if 0
			for (i = 0; i < RxCnt; i++)
			{
				USART_SendData(USART1, RxData[i]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			}
			USART_SendData(USART1, '\n');
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			#endif
			
			/* drive the led strip */
			for (i = 0; i < RxCnt; i++)
			{
				cNum[i] = RxData[i];
				RxData[i] = 0;
			}
			led_index = atoi((const char*)cNum);
			USART_SendData(USART1, (u8)led_index);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			USART_SendData(USART1, (u8)0x77);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		
			while(!WS2812_TC);
			WS2812_clean_all_pixel();
			WS2812_framedata_setPixel(2, led_index, 5, 0, 0);
			WS2812_sendbuf(LED_BUFFER_SIZE);
			/* end drive led strip */
			
			RxData[RxCnt] = 0;
			RxCnt = 0;
			return;
		}
		
		RxCnt++;
 }
}


/*****************************/

int main(void) 
{	
	u8 i;
	//u8 pd2on = 0;
	u8 damper = 32;
	u32 counter = 0;
	
	RCC_Configuration();
	Systick_Configuration();
	GPIO_init();
	DMA_init();
	TIM2_init();
	USART_Configuration();
	NVIC_Configure();
	
	 while(1)
	{
	}

}



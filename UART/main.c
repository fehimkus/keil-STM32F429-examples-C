#include "stm32f4xx_hal.h"
#include <string.h>


void UART_Config(void);
void DMA_Config(void);

UART_HandleTypeDef myuart;
DMA_HandleTypeDef dmauart2;

char txData[40]="Hello from stm32f4 discovery\r\n";
char rxData[40];

 
int main(void)
{
	//hal initilazie
	HAL_Init();
	//UART initilazie
	UART_Config();	
	//DMA initilazie
	DMA_Config();	
	
	while(1)
	{
	HAL_UART_Transmit(&myuart, (uint8_t *)txData, strlen(txData), 10);
		HAL_Delay(500);
	
	}


}

void UART_Config(void)
{
__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_USART2_CLK_ENABLE();
	
	GPIO_InitTypeDef myuartpin;
	
	myuartpin.Pin= GPIO_PIN_2 | GPIO_PIN_3;
	myuartpin.Mode= GPIO_MODE_AF_PP;
	myuartpin.Pull= GPIO_PULLUP;
	myuartpin.Speed= GPIO_SPEED_FREQ_VERY_HIGH;
	myuartpin.Alternate= GPIO_AF7_USART2;
	
	HAL_GPIO_Init(GPIOA, &myuartpin);

  myuart.Instance=USART2;
  myuart.Init.BaudRate=11520;
	myuart.Init.Mode=UART_MODE_TX_RX;
	myuart.Init.WordLength=UART_WORDLENGTH_8B;
	myuart.Init.StopBits=UART_STOPBITS_1;
	myuart.Init.OverSampling=UART_OVERSAMPLING_16;
	
	HAL_UART_Init(&myuart);
	
	//Enable Systick interrupt
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);	
	
}

void SysTick_Handler(void)
{
  HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void DMA_Config(void)
{
	__HAL_RCC_DMA1_CLK_ENABLE();
	dmauart2.Instance=DMA1_Stream5;
	dmauart2.Init.Channel = DMA_CHANNEL_4;
	dmauart2.Init.Direction= DMA_PERIPH_TO_MEMORY;
	dmauart2.Init.PeriphInc= DMA_PINC_DISABLE;
	dmauart2.Init.MemInc= DMA_MINC_DISABLE;
	dmauart2.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
	dmauart2.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
	dmauart2.Init.Mode=DMA_CIRCULAR;
	dmauart2.Init.Priority=DMA_PRIORITY_LOW;
	dmauart2.Init.FIFOMode= DMA_FIFOMODE_DISABLE;
	
	HAL_DMA_Init(&dmauart2);
	
	__HAL_LINKDMA(&myuart, hdmarx ,dmauart2);
	
		//Enable DMA1 stream5 interrupt
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);	
}
void DMA1_Stream5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&dmauart2);
	
}

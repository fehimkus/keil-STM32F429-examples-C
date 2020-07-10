#include "stm32f4xx_hal.h"

void GPIO_Config(void);
void ADC_Config(void);
void DMA_Config(ADC_HandleTypeDef* hadc);

  ADC_HandleTypeDef myadc;
  DMA_HandleTypeDef mydma;


uint8_t adcval[3];

int main(void)
{
  HAL_Init();
	GPIO_Config();
  ADC_Config();
  DMA_Config(&myadc);
	
	HAL_ADC_Start_DMA(&myadc, (uint32_t *)adcval, 3); 
	
while(1)
	{

	
	}
}

void GPIO_Config(void)
{
//enable GPIO clocks
__HAL_RCC_GPIOA_CLK_ENABLE();
//__HAL_RCC_GPIOD_CLK_ENABLE();
	
//Analog input	
	GPIO_InitTypeDef mypins;
	mypins.Pin= GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 ;
	mypins.Mode=GPIO_MODE_ANALOG;
	//mypin.Pull=GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &mypins);
	
// //LED pin config
//  mypins.Pin =GPIO_PIN_13;
//  mypins.Pull = GPIO_MODE_OUTPUT_PP;
//  HAL_GPIO_Init(GPIOG, &mypins);	
//	
//	//Enable Systick interrupt
//	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
//  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
//	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
//	
//	//Enable ADC interrupt
//	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(ADC_IRQn);	
}
void ADC_Config(void)
{
	//Enable ADC clock
__HAL_RCC_ADC1_CLK_ENABLE();
	
	// ADC basic config
	myadc.Instance=ADC1;
	myadc.Init.ClockPrescaler=ADC_CLOCKPRESCALER_PCLK_DIV8;
	myadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	myadc.Init.Resolution=ADC_RESOLUTION_8B;
	myadc.Init.ScanConvMode=ENABLE;
	myadc.Init.ContinuousConvMode = ENABLE;
	myadc.Init.DiscontinuousConvMode=DISABLE;
	myadc.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;
	myadc.Init.DataAlign=ADC_DATAALIGN_RIGHT;
	myadc.Init.NbrOfConversion=3;
	myadc.Init.DMAContinuousRequests=ENABLE;
	myadc.Init.EOCSelection=ADC_EOC_SEQ_CONV;
	//myadc.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_RISING;
	
	
HAL_ADC_Init(&myadc);	
	
	
	ADC_ChannelConfTypeDef myadcch;
	
	myadcch.Channel= ADC_CHANNEL_0;
	//myadcch.Offset=0;
	myadcch.Rank=1;
	myadcch.SamplingTime=ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&myadc, &myadcch);
	
	myadcch.Channel= ADC_CHANNEL_1;
	//myadcch.Offset=0;
	myadcch.Rank=2;
	myadcch.SamplingTime=ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&myadc, &myadcch);
	
	myadcch.Channel= ADC_CHANNEL_2;
	//myadcch.Offset=0;
	myadcch.Rank=3;
	myadcch.SamplingTime=ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&myadc, &myadcch);
}

void DMA_Config(ADC_HandleTypeDef* hadc)
{
	//Enable DMA clock
__HAL_RCC_DMA2_CLK_ENABLE();

	
	mydma.Instance=DMA2_Stream0;
	mydma.Init.Channel=DMA_CHANNEL_0;
	mydma.Init.Direction=DMA_PERIPH_TO_MEMORY;
	mydma.Init.PeriphInc=DMA_PINC_DISABLE;
	mydma.Init.MemInc=DMA_MINC_ENABLE;
	mydma.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
	mydma.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
	mydma.Init.Mode=DMA_CIRCULAR;
	mydma.Init.Priority=DMA_PRIORITY_LOW;
	mydma.Init.FIFOMode=DMA_FIFOMODE_DISABLE;
	
	
	HAL_DMA_Init(&mydma);
	
	__HAL_LINKDMA(hadc, DMA_Handle, mydma);
	
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	
}

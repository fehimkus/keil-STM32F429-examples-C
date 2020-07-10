#include "stm32f4xx_hal.h"

void GPIO_Config(void);
void ADC_Config(void);
void Systick_Config(void);

//definitions
ADC_HandleTypeDef myadc;
uint32_t adcvalue;

int main(void)
{
	HAL_Init();
	GPIO_Config();
	ADC_Config();
	Systick_Config();
	
	
	while(1)
	{
	//READ ADC VALUE
		HAL_ADC_Start(&myadc);
		if(HAL_ADC_PollForConversion(&myadc, 5)==HAL_OK)
		{
		adcvalue=HAL_ADC_GetValue(&myadc);
		HAL_ADC_Stop(&myadc);
		//DELAY
		HAL_Delay(100);
		}
	}
}
void GPIO_Config(void)
{
__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef myadcpin;
	myadcpin.Pin= GPIO_PIN_0;
	myadcpin.Mode=GPIO_MODE_ANALOG;
	myadcpin.Pull=GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA, &myadcpin);

}

void ADC_Config(void)
{
__HAL_RCC_ADC1_CLK_ENABLE();
	
	myadc.Instance=ADC1;
	myadc.Init.Resolution=ADC_RESOLUTION10b;         //resolution ADCvalue
	myadc.Init.EOCSelection= ADC_EOC_SINGLE_CONV;    
	myadc.Init.DataAlign=ADC_DATAALIGN_RIGHT;
	//myadc.Init.ContinuousConvMode=ENABLE;
	
HAL_ADC_Init(&myadc);
	
	ADC_ChannelConfTypeDef myadcch;
	
	myadcch.Channel= ADC_CHANNEL_0;
	myadcch.Rank=1;
	myadcch.SamplingTime=ADC_SAMPLETIME_15CYCLES;
	
	
HAL_ADC_ConfigChannel(&myadc, &myadcch);
	
}

void Systick_Config(void)
	
{
//SET CLOCK SOURCE AND SPEED
HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
//SYSTICK INTERRUPT PRIORITY AND ENABLE
HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(SysTick_IRQn);	
}

void SysTick_Handler(void)
{
HAL_IncTick();
}

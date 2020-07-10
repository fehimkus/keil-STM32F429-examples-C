#include "stm32f4xx_hal.h"

void GPIO_Config(void);



int main(void)
{

	HAL_Init();
	GPIO_Config();
	
	while(1)
		
	{
	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
	HAL_Delay(500);
		 
	
	}

}

void GPIO_Config(void)
{
//enable GPIO clocks
__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_GPIOG_CLK_ENABLE();
	
	
	GPIO_InitTypeDef mypin;

  //push button	
	mypin.Pin= GPIO_PIN_0;
	mypin.Mode=GPIO_MODE_IT_RISING;
  HAL_GPIO_Init(GPIOA, &mypin);
	
  //LED pin config
  mypin.Pin =GPIO_PIN_13 |GPIO_PIN_14;
  mypin.Pull = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOG, &mypin);	
	
	//Enable ADC interrupt
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	//Enable Systick interrupt
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);	
}
 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
 UNUSED(GPIO_Pin);
	
	 // This function should not be modified when callback is needed, 
	 // the HAL_GPIO_EXTI_Calback could be implemented in the user file
 
	 HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
	 for(uint32_t i=0; i<1000; i++);
 
 }
 
 void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
 
void SysTick_Handler(void)
{
  HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
} 
 
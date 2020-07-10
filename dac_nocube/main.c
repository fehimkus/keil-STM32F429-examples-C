#include "stm32f4xx_hal.h"

void GPIO_Config(void);
void DAC_Config(void);

DAC_HandleTypeDef mydac;

//variable definitions
float dacvalf=1.2;
uint8_t dacval;

int main(void)
{
	//HAL initialization
  HAL_Init();

	//configuration functions
	GPIO_Config();
	DAC_Config();	
	
	//convert floating point to decimal
	dacval=(uint8_t)((dacvalf/3.0)*255);
	//start the DAC device
	HAL_DAC_Start(&mydac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&mydac, DAC_CHANNEL_1,DAC_ALIGN_8B_R, dacval);
	
while(1)
	
	{
	
	
	}

}

void GPIO_Config(void)
{
//enable GPIO clocks
__HAL_RCC_GPIOA_CLK_ENABLE();
//__HAL_RCC_GPIOD_CLK_ENABLE();
	
//Analog	
	GPIO_InitTypeDef mypins;
	mypins.Pin= GPIO_PIN_4;
	mypins.Mode=GPIO_MODE_ANALOG;
	mypins.Pull=GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &mypins);
}
void DAC_Config(void)
{
__HAL_RCC_DAC_CLK_ENABLE();

	mydac.Instance=DAC;
	HAL_DAC_Init(&mydac);
	
	DAC_ChannelConfTypeDef mydacch;
	mydacch.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;
	mydacch.DAC_Trigger=DAC_OUTPUTBUFFER_DISABLE;
	
	HAL_DAC_ConfigChannel(&mydac, &mydacch, DAC_CHANNEL_1);
	
}

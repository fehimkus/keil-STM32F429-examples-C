#include "stm32f4xx_hal.h"

void GPIO_Config(void);
void SPI_Config(void);

SPI_HandleTypeDef myspi;
uint8_t spiTxBuf[2], spiRxBuf[2];

int main(void)
{
	HAL_Init();
  GPIO_Config();
	SPI_Config();
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	// SPI WRITE operation routine
	// 1. Bring CS low to activate the slave device (L3GD20)
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
  // 2. Transmit register Adress + Data
	spiTxBuf[0] = 0x20;
	spiRxBuf[1] = 0x31;
	HAL_SPI_Transmit(&myspi, spiTxBuf, 2, 50);
	// 3. Bring slave select high
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	
	
	// SPI READ operation routine
	// 1. Bring CS low to activate the slave device (L3GD20)
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
  // 2. Transmit register Adress from masked with 0x80
	spiTxBuf[0] = 0x20|0x80;
	HAL_SPI_Transmit(&myspi, spiTxBuf, 1, 50);
	// 3. Receive register 1 byte data of data
	HAL_SPI_Transmit(&myspi, spiRxBuf, 1, 50);
	// 4. Bring CS HIGH to deactivate the slave device
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	
	
//	// 1. Bring CS low to activate the slave device (L3GD20)
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//  // 2. Transmit register Adress
//	spiTxBuf[0] = 0x23;
//	HAL_SPI_Transmit(&myspi, spiTxBuf, 1, 50);
//	// 3. Transmit 1 byte data to the register
//	spiTxBuf[0] = 0xC8;
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	
	
while(1)
	
{


}


}
	
void GPIO_Config(void)
{
__HAL_RCC_SPI1_CLK_ENABLE();
__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_GPIOC_CLK_ENABLE();
__HAL_RCC_GPIOF_CLK_ENABLE();
__HAL_RCC_GPIOD_CLK_ENABLE();
  
	GPIO_InitTypeDef mypins;
	
	
	//SPI pin configuration
	mypins.Pin=GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 ;
	mypins.Mode= GPIO_MODE_AF_PP;
	mypins.Speed= GPIO_SPEED_FREQ_VERY_HIGH;
	mypins.Pull= GPIO_NOPULL;
	mypins.Alternate= GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOF, &mypins);
	
	//LED pin configurations
	mypins.Pin=GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 ;
	mypins.Mode= GPIO_MODE_AF_PP;
	mypins.Speed= GPIO_SPEED_FREQ_VERY_HIGH;
	mypins.Pull= GPIO_NOPULL;
	mypins.Alternate= GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOD, &mypins);
	
	//CS configuration
	mypins.Pin=GPIO_PIN_1;
  HAL_GPIO_Init(GPIOC, &mypins);
	
	//INT1 pin configuration
	mypins.Pin=GPIO_PIN_1;
	mypins.Mode = GPIO_MODE_IT_RISING;
	HAL_GPIO_Init(GPIOA, &mypins);
	
	//Enable EXTI0 interrupt
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);	
	
	//Enable Systick interrupt
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}

void SPI_Config(void)
{

  myspi.Instance=SPI5;
	myspi.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_16;
	myspi.Init.CLKPhase= SPI_PHASE_1EDGE;
	myspi.Init.CLKPolarity=SPI_POLARITY_LOW;
	myspi.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLED;
	myspi.Init.CRCPolynomial=10;
	myspi.Init.DataSize=SPI_DATASIZE_8BIT;
	myspi.Init.Direction=SPI_DIRECTION_2LINES;
	myspi.Init.FirstBit=SPI_FIRSTBIT_MSB;
	myspi.Init.Mode=SPI_MODE_MASTER;
	myspi.Init.NSS=SPI_NSS_SOFT;
	myspi.Init.TIMode=SPI_TIMODE_DISABLE;
	
  HAL_SPI_Init(&myspi);
	
}

void EXTI0_Handler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
void SysTick_Handler(void)
{
  HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


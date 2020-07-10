#include "stm32f4xx_hal.h"


void  GPIO_Config(void);
//void  SystemClock_Config(void);
//void  TIM4_Config(void); 

TIM_HandleTypeDef htim4;

int main(void)
{

  HAL_Init();
//  SystemClock_Config();
//  TIM4_Config();


  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);      //Timer4/CH1 Starten
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);      //Timer4/CH2 Starten

  TIM4->CCR1 =          2000;                    // 2000 == 2 ms
  TIM4->CCR2 =          2000;                    // 2000 == 2 ms
  HAL_Delay(5000);                               //Verzögerung 5s
  TIM4->CCR1 =          1000;                    // 1000 == 1 ms
  TIM4->CCR2 =          1000;                    // 1000 == 1 ms
  HAL_Delay(5000);                               //Verzögerung 5s

  while (1)
  {
   
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(2000);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(2000);
    /*Blink-Blink*/

  }
}


//Timer-Init:

static void MX_TIM4_Init(void)
{
  TIM_MasterConfigTypeDef             sMasterConfig;
  TIM_OC_InitTypeDef                  sConfigOC;
	TIM_ClockConfigTypeDef              sClockSourceConfig;
  int PrescalarValue; 
	
  PrescalarValue =                    84;

  htim4.Instance =                    TIM4;
  htim4.Init.Prescaler =              PrescalarValue;
  htim4.Init.CounterMode =            TIM_COUNTERMODE_UP;
  htim4.Init.Period =                 19999;
  htim4.Init.ClockDivision =          TIM_CLOCKDIVISION_DIV1;

  sClockSourceConfig.ClockSource =    TIM_CLOCKSOURCE_ETRMODE2;
  sClockSourceConfig.ClockPolarity =  TIM_CLOCKPOLARITY_NONINVERTED;
  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  sClockSourceConfig.ClockFilter =    0;
 
  HAL_TIM_PWM_Init(&htim4);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode =     TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);
 
  sConfigOC.OCMode =                  TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity =              TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode =              TIM_OCFAST_DISABLE;

  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);

  HAL_TIM_OnePulse_MspInit(&htim4);
}


//GPIO_Timer_Init:

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==TIM4)
  {
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    PB8     ------> TIM4_CH3
    PB9     ------> TIM4_CH4 
   Your advertisement could be displayed here!
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }

}
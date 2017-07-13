/*
 * tim.c
 *
 *  Created on: 20.07.2015
 *      Author: Aleksey
 */

#include "tim.h"

void Tim4_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Tim4 clock enabled 84 MHz
	TIM4->PSC = 500 - 1;//prescaller(1...65536)
	TIM4->ARR = 100;//auto-reload value
	TIM4->CR1 &= ~TIM_CR1_DIR;//count direction up
	TIM4->CR1 |= TIM_CR1_ARPE;//ARR preload enable
	TIM4->CR1 |= TIM_CR1_CEN;//TIM4 enabled
}

void Tim4_OC_Init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;//GPIOD clock enable
	GPIOD->MODER &= ~GPIO_MODER_MODER12;//Clear Pin 12 mode
	GPIOD->MODER |= GPIO_MODER_MODER12_1;//Pin 12 alternative function
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED12;//Low speed PD12
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_12;//Push-pull PD12
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD12;//No pull-up & pull-down PD12
	GPIOD->AFR[1] |= GPIO_AFRH_AFSEL12_1;//AF2 - Tim4 channels
	Tim4_Init();
	TIM4->CCMR1 = TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2;//PWM1 mode channels 1
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE;//Output compare preload enable
	TIM4->CCER |= TIM_CCER_CC1P;//Output polarity Low

	TIM4->CCER |= TIM_CCER_CC1E;//Output enable
}

void Tim4_DeInit(void)
{
  NVIC_DisableIRQ(TIM4_IRQn);
  TIM4->CR1 &= ~TIM_CR1_CEN;//TIM4 disabled
  RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;//Tim4 clock disabled
}


void Tim6_Init(uint32_t frequency)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;//Tim6 clock enabled 84 MHz
  TIM6->PSC = TIM6_PSC - 1;//prescaller(1...65536)
  TIM6->ARR = APB1_FREQ/(SINE_RES * TIM6_PSC * frequency);//auto-reload value
  TIM6->DIER |= TIM_DIER_UIE;//update interrupt enable
  TIM6->CR2 |= TIM_CR2_MMS_1;//update event is trigger output

  NVIC_SetPriority(TIM6_DAC_IRQn, 4);
  //NVIC_EnableIRQ(TIM6_DAC_IRQn);

  //TIM6->CR1 |= TIM_CR1_CEN;//TIM6 enabled
}

void Tim6_Start()
{
#ifndef USE_DAC1_DMA
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
#endif
  TIM6->CR1 |= TIM_CR1_CEN;//TIM6 enabled
}

void Tim6_Stop()
{
#ifndef USE_DAC1_DMA
  NVIC_DisableIRQ(TIM6_DAC_IRQn);
#endif
  TIM6->CR1 &= ~TIM_CR1_CEN;//TIM6 disabled
}

void Tim6_Set(uint32_t frequency)
{
  TIM6->PSC = TIM6_PSC - 1;//prescaller(1...65536)
  TIM6->ARR = APB1_FREQ/(SINE_RES * TIM6_PSC * frequency);;//auto-reload value
}


void Tim7_Init(uint32_t frequency)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;//Tim7 clock enabled 84 MHz
  TIM7->PSC = TIM7_PSC - 1;//prescaller(1...65536)
  TIM7->ARR = APB1_FREQ/(TIM7_PSC * frequency);//auto-reload value
  TIM7->DIER |= TIM_DIER_UIE;//update interrupt enable
  TIM7->CR1 &= ~TIM_CR1_DIR;//count direction up
  TIM7->CR1 |= TIM_CR1_ARPE;//ARR preload enable
  NVIC_SetPriority(TIM7_IRQn, 1);
  NVIC_EnableIRQ(TIM7_IRQn);
  TIM7->CR1 |= TIM_CR1_CEN;//TIM7 enabled
}

static __IO long int usTick;


void usIncTick(void)
{
  usTick++;
}

/**
  * @brief Provides a tick value in microsecond.
  * @note
  * @retval tick value
  */
long int usGetTick(void)
{
  return usTick;
}

/**
  * @brief This function provides accurate delay (in microseconds) based
  *        on variable incremented.
  * @note Timer7 is the source of time base.
  *       It is used to generate interrupts at regular time intervals where usTick
  *       is incremented.
  * @note
  * @param Delay: specifies the delay time length, in microseconds.
  * @retval None
  */
void delay_us(volatile long int Delay)
{
  uint32_t tickstart = 0U;
  tickstart = usGetTick();
  while((usGetTick() - tickstart) < Delay);
}


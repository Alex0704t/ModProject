/*
 * gpio.c
 *
 *  Created on: 10.04.2017
 *      Author: User
 */

#include "gpio.h"

  /** FSMC GPIO Configuration
  PE7     ------> FSMC_D4
  PE8     ------> FSMC_D5
  PE9     ------> FSMC_D6
  PE10    ------> FSMC_D7
  PE11    ------> FSMC_D8
  PE12    ------> FSMC_D9
  PE13    ------> FSMC_D10
  PE14    ------> FSMC_D11
  PE15    ------> FSMC_D12
  PD8     ------> FSMC_D13
  PD9     ------> FSMC_D14
  PD10    ------> FSMC_D15
  PD11    ------> FSMC_A16
  PD14    ------> FSMC_D0
  PD15    ------> FSMC_D1
  PD0     ------> FSMC_D2
  PD1     ------> FSMC_D3
  PD4     ------> FSMC_NOE
  PD5     ------> FSMC_NWE
  PD7     ------> FSMC_NE1
  */


void FSMC_Pins_Init()
{
  //GPIOD, GPIOE clock enable
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN|RCC_AHB1ENR_GPIOEEN;
  //FSMC clock enable
  RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;
  //alternate function mode
  GPIOD->MODER |= 0xA0AA8A0A;
  GPIOE->MODER |= 0xAAAA8000;
  //push-pull
  GPIOD->OTYPER &= ~0xCFB3;
  GPIOE->OTYPER &= ~0xFF80;
  //no pull-up & pull-down
  GPIOD->PUPDR &= ~0xF0FFCF0F;
  GPIOE->PUPDR &= ~0xFFFFC000;
  //very high speed
  GPIOD->OSPEEDR |= 0xF0FFCF0F;
  GPIOE->OSPEEDR |= 0xFFFFC000;
  //alternate function FSMC
  GPIOD->AFR[0] |= 0xC0CC00CC;
  GPIOD->AFR[1] |= 0xCC00CCCC;
  GPIOE->AFR[0] |= 0xC0000000;
  GPIOE->AFR[1] |= 0xCCCCCCCC;
 }

/** LCD module Pin Configuration
PA2     ------> LCD_RESX
PD12    ------> LCD_BL_CNTL
PB12    ------> TP_CS
PD6     ------> TP_IRQ
PA3     ------> SD_CS
*/

void LCD_Reset_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  GPIOA->MODER |= GPIO_MODER_MODER2_0;//output mode
  GPIOA->OTYPER &=  ~GPIO_OTYPER_OT_2;//push-pull
  GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;//low speed
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;//no pull-up & pull-down
}

void LCD_BlCntl_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  GPIOD->MODER |= GPIO_MODER_MODER12_0;//output mode
  GPIOD->OTYPER &=  ~GPIO_OTYPER_OT_12;//push-pull
  GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR12;//low speed
  GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR12;//no pull-up & pull-down
}

void SPI1_CS_Pins_Init()
{
  /*PA3 chip select for SDCard*/
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  GPIOA->MODER |= GPIO_MODER_MODER3_0;//output mode
  GPIOA->OTYPER &=  ~GPIO_OTYPER_OT_3;//push-pull
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;//low speed
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR3;//no pull-up & pull-down

  /*PE3 chip select for accelerometer*/
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
  GPIOE->MODER |= GPIO_MODER_MODER3_0;//PE3 output
  GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;//low speed
  GPIOE->OTYPER &= ~GPIO_OTYPER_OT_3;//push-pull
  GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR3;//no pull-up & pull-down

}

void TP_CS_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  GPIOB->MODER |= GPIO_MODER_MODER12_0;//output mode
  GPIOB->OTYPER &=  ~GPIO_OTYPER_OT_12;//push-pull
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR12;//low speed
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR12;//no pull-up & pull-down
}

void TP_IRQ_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  GPIOD->MODER &= ~GPIO_MODER_MODER6;//input mode
//  GPIOD->OTYPER &=  ~GPIO_OTYPER_OT_6;//push-pull
//  GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;//low speed
  GPIOD->PUPDR |= GPIO_PUPDR_PUPDR6_0;//pull-up
//  GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR6;//no pull-up & pull-down
}

void TP_IRQ_Int_Init()
{
  TP_IRQ_Pin_Init();
  EXTI->IMR |= EXTI_IMR_IM6;//no mask interrupt EXTI6
//  EXTI->RTSR |= EXTI_RTSR_TR6;//rising trigger event EXTI6
  EXTI->FTSR |= EXTI_FTSR_TR6;//falling trigger event EXTI0
  SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PD;//EXTI6 source PD6
  NVIC_SetPriority(EXTI9_5_IRQn, 4);
  NVIC_EnableIRQ(EXTI9_5_IRQn);//IRQ handler
}

void Board_LED_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  GPIOD->MODER |= GPIO_MODER_MODER13_0;//output mode
  GPIOD->OTYPER &=  ~GPIO_OTYPER_OT_13;//push-pull
  GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;//low speed
  GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR13;//no pull-up & pull-down
}

void Button_Pin_Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//GPIOA clock enable
  GPIOA->MODER &= ~GPIO_MODER_MODER0;//Input PA0
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT0;//Push-pull
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;//no pull-up & pull-down
}

void Button_Int_Init(void)
{
  Button_Pin_Init();
  EXTI->IMR |= EXTI_IMR_IM0;//no mask interrupt EXTI0
  EXTI->RTSR |= EXTI_RTSR_TR0;//rising trigger event EXTI0
  //EXTI->FTSR |= EXTI_FTSR_TR0;//falling trigger event EXTI0
  SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;//EXTI0 source PA0
  NVIC_SetPriority(EXTI0_IRQn, 4);
  NVIC_EnableIRQ(EXTI0_IRQn);//IRQ handler
}


uint8_t Button_Check()
{
  return PRESS_BUTTON;
}

void BackLight_Init()
{
#ifdef USE_PWM_BACKLIGHT
  Tim4_OC_Init();
#else
  LCD_BlCntl_Pin_Init();
#endif
}

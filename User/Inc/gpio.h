/*
 * gpio.h
 *
 *  Created on: 10.04.2017
 *      Author: User
 */

#ifndef USER_INC_GPIO_H_
#define USER_INC_GPIO_H_

#include "stm32f4xx.h"
//#include "user.h"

#define LCD_RESET_ON()    GPIOA->BSRR = GPIO_BSRR_BR_2//LCD reset pin low
#define LCD_RESET_OFF()   GPIOA->BSRR = GPIO_BSRR_BS_2//LCD reset pin high
#define SD_CS_ON()        GPIOA->BSRR = GPIO_BSRR_BR_3//SD CS pin low
#define SD_CS_OFF()       GPIOA->BSRR = GPIO_BSRR_BS_3//SD CS pin high
#define TP_CS_ON()        GPIOB->BSRR = GPIO_BSRR_BR_12//TP CS pin low
#define TP_CS_OFF()       GPIOB->BSRR = GPIO_BSRR_BS_12//TP CS pin high
#define PRESS_TOUCH       (!((GPIOD->IDR & GPIO_IDR_IDR_6) == GPIO_IDR_IDR_6))
#define PRESS_BUTTON      ((GPIOA->IDR & GPIO_IDR_IDR_0) == GPIO_IDR_IDR_0)
#define LED_ON()          GPIOD->BSRR = GPIO_BSRR_BS_13
#define LED_OFF()         GPIOD->BSRR = GPIO_BSRR_BR_13
#define LED_TOGGLE()      GPIOD->ODR ^= GPIO_ODR_ODR_13

/** select PWM backlight control, else GPIO output */
#define USE_PWM_BACKLIGHT

#ifdef USE_PWM_BACKLIGHT
#define BL_ON()           T4_CH1_SET(100)
#define BL_OFF()          T4_CH1_SET(0)
#define BL_SET(val)       T4_CH1_SET(val)
#else
/** use GPIO instead PWM mode */
#define BL_THRESHOLD      20//threshold value for backlight on
#define BL_ON()           GPIOD->BSRR = GPIO_BSRR_BS_12
#define BL_OFF()          GPIOD->BSRR = GPIO_BSRR_BR_12
#define BL_SET(val)       GPIOD->BSRR = (val > BL_THRESHOLD) ? GPIO_BSRR_BR_12 : GPIO_BSRR_BS_12
#endif

void FSMC_Pins_Init();
void LCD_Reset_Pin_Init();
void LCD_BlCntl_Pin_Init();
void SPI1_CS_Pins_Init();
void TP_CS_Pin_Init();
void TP_IRQ_Pin_Init();
void TP_IRQ_Int_Init();
void Board_LED_Pin_Init();
void Button_Pin_Init();
void Button_Int_Init(void);
uint8_t Button_Check();
void BackLight_Init();

#endif /* USER_INC_GPIO_H_ */

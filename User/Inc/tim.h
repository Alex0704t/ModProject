/*
 * tim.h
 *
 *  Created on: 20.07.2015
 *      Author: Aleksey
 */

#ifndef USER_TIM_H_
#define USER_TIM_H_

//#include "../Device/stm32f4xx.h"
#include "user.h"

#define APB1_FREQ          84000000//TIM counter clock (prescaled APB1)
#define APB2_FREQ          168000000//TIM counter clock (prescaled APB2)


#define T4_CH1_SET(value) (TIM4->CCR1 = (value))

#define TIM7_PSC          1
#define TIM6_PSC          2


void Tim4_Init(void);
void Tim4_OC_Init(void);
void Tim4_DeInit(void);
void Tim6_Init(uint32_t frequency);
void Tim6_Start();
void Tim6_Stop();
void Tim6_Set(uint32_t frequency);
void Tim7_Init(uint32_t frequency);
void usIncTick(void);
long int usGetTick(void);
void delay_us(volatile long int Delay);

#endif /* USER_TIM_H_ */

/*
 * fsmc.h
 *
 *  Created on: 05.04.2017
 *      Author: User
 */

#ifndef USER_INC_FSMC_H_
#define USER_INC_FSMC_H_

#include "stm32f4xx.h"
#include "gpio.h"

#define ADDRESS_HOLD_TIME 2
#define DATA_SETUP_TIME   5

void FSMC_Init();
#endif /* USER_INC_FSMC_H_ */

/*
 * user.c
 *
 *  Created on: 18.12.2016.
 *      Author: User
 */

#include "user.h"

void MCU_Init()
{
  RCC_Init();
  RTC_Init();




//  USB_HID_Init();
//  SCB->CPACR |= 0x00F00000;//enable FPU
  //Audio_Init();
  //AnalogWave_Init(1000, 30);
}

void LCD_Module_Init()
{
  SPI1_CS_Pins_Init();
  TP_CS_Pin_Init();
  TP_IRQ_Pin_Init();
  SD_CS_ON();
  TP_CS_ON();
}

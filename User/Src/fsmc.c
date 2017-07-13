/*
 * fsmc.c
 *
 *  Created on: 05.04.2017
 *      Author: User
 */

#include "fsmc.h"



void FSMC_Init()
{
  FSMC_Pins_Init();
  FSMC_Bank1->BTCR[1] |= (ADDRESS_HOLD_TIME << FSMC_BTR1_ADDHLD_Pos)|//AddressHoldTime = 2
                         (DATA_SETUP_TIME << FSMC_BTR1_DATAST_Pos);//DataSetupTime = 5
  FSMC_Bank1->BTCR[0] |= FSMC_BCR1_MWID_0|//16 bit width
                         FSMC_BCR1_WREN|//write enable
                         FSMC_BCR1_MBKEN;//memory bank enable
}

/*
 * flash.c
 *
 *  Created on: 23.06.2015
 *
 *
 *    Author: Aleksey
 */

#include "flash.h"

void FlashUnlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH Registers access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }
}

void FlashLock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  FLASH->CR |= FLASH_CR_LOCK;
}

void FlashEraseSector(uint32_t Sector)
{
	while(FLASH->SR & FLASH_SR_BSY);//wait end another flash operation
	FLASH->CR &= 0xFFFFFCFF;//clear flash control register
	FLASH->CR |= FLASH_CR_PSIZE_1;//program size x32 for VCC 2.7V to 3.6V
	FLASH->CR &= FLASH_CR_SNB;//clear sector number
	FLASH->CR |= FLASH_CR_SER | (Sector << 3);//set number of sector and sector erase bit
	FLASH->CR |= FLASH_CR_STRT;//start erase
	while(FLASH->SR & FLASH_SR_BSY);//wait for end erase
}

void FlashProgramWord(uint32_t Address, uint32_t Data)
{
	while(FLASH->SR & FLASH_SR_BSY);//wait end another flash operation
	FLASH->CR &= 0xFFFFFCFF;//clear flash control register
	FLASH->CR |= FLASH_CR_PSIZE_1;//program size x32 for VCC 2.7V to 3.6V
	FLASH->CR |= FLASH_CR_PG;//flash programming operation
	*(uint32_t*)Address = Data;
	while(FLASH->SR & FLASH_SR_BSY);//wait for last operation to be completed
  FLASH->CR &= (~FLASH_CR_PG);//deactivated
}

void FlashProgramByte(uint32_t Address, uint8_t Data)
{
  while(FLASH->SR & FLASH_SR_BSY);//wait end another flash operation
  FLASH->CR &= 0xFFFFFCFF;//clear flash control register
  FLASH->CR |= FLASH_CR_PSIZE_1;//program size x32 for VCC 2.7V to 3.6V
  FLASH->CR |= FLASH_CR_PG;//flash programming operation
  *(uint32_t*)Address = Data;
  while(FLASH->SR & FLASH_SR_BSY);//wait for last operation to be completed
  FLASH->CR &= (~FLASH_CR_PG);//deactivated
}

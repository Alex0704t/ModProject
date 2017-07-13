/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "user.h"

#ifndef LCD_RAM
#define LCD_RAM                     (*(__IO uint16_t *)0x60020000) //write data address
#endif
#ifndef LCD_REG
#define LCD_REG                     (*(__IO uint16_t *)0x60000000) //write command address
#endif

static GFXINLINE void init_board(GDisplay *g) {
	(void) g;
  FSMC_Init();
  LCD_Reset_Pin_Init();
  BackLight_Init();
  Tim7_Init(1000000);
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	if (state == TRUE)
	  LCD_RESET_ON();
	else
	  LCD_RESET_OFF();
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	BL_SET(percent);
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index) {
	(void) g;
	LCD_REG = index;
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data) {
	(void) g;
	LCD_RAM = data;
}

static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g) {
	(void) g;
	return LCD_RAM;
}

#endif /* _GDISP_LLD_BOARD_H */

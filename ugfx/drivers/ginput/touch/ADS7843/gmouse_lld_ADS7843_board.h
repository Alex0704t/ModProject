/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			  6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			    4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		  18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		  14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0
#include "stm32f4xx.h"
#include "gfx.h"
#include "../../../../src/ginput/ginput_driver_mouse.h"
#include "gpio.h"
#include "spi.h"



static bool_t init_board(GMouse* m, unsigned driverinstance) {
  (void) m;
  if (driverinstance)
    return FALSE;
  TP_IRQ_Pin_Init();
//  TP_IRQ_Int_Init();
  TP_CS_Pin_Init();
  SPI2_Init();
  return TRUE;
}

static GFXINLINE bool_t getpin_pressed(GMouse* m) {
  (void) m;
//  return PRESS_TOUCH;
  return PRESS_TOUCH || PRESS_BUTTON;
}

static GFXINLINE void aquire_bus(GMouse* m) {
  (void) m;
  TP_CS_ON();
}

static GFXINLINE void release_bus(GMouse* m) {
  (void) m;
  TP_CS_OFF();
}

static GFXINLINE uint16_t read_value(GMouse* m, uint16_t port) {
  uint8_t txbuf[3] = {0, 0, 0};
  uint8_t rxbuf[3] = {0, 0, 0};
  (void)m;
  txbuf[0] = port;
  SPI_TxRx(SPI2, txbuf, rxbuf, 3);
  return (rxbuf[1] << 5) | (rxbuf[2] >> 3);
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */

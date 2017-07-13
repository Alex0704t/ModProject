/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "../fatfs/ff.h"
#include "main.h"
#include <string.h>
//#include "fsmc.h"
#include "gpio.h"
#include "user.h"
#include "../gui/gui.h"
#include "gfx.h"
#include "gfile.h"
#include "../fatfs/user_fs/f_utils.h"
//#include "../ugfx/src/gwin/gwin.h"
//#include "ILI9341.h"
//#include "board_ILI9341.h"

#if 1
FRESULT scan_files(
  char* path    /* Pointer to the path name working buffer */
)
{
  DIR dirs;
  FRESULT res;
  BYTE i;
  static FILINFO Finfo;

  if ((res = f_opendir(&dirs, path)) == FR_OK) {
    i = strlen(path);
    while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
      if (Finfo.fattrib & AM_DIR) {
////        AccDirs++;
        *(path + i) = '/'; strcpy((path + i + 1), Finfo.fname);
//        res = scan_files(path);
        *(path + i) = '\0';
        if (res != FR_OK) break;
      } else {
      /*  xprintf("%s/%s\n", path, fn); */
          gwinPrintf(ghConsole1, "%s/%s\n", path, Finfo.fname);
////        AccFiles++;
////        AccSize += Finfo.fsize;
      }
    }
  }
  f_closedir(&dirs);
  return res;
}
#else

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
//                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                gwinPrintf(ghConsole1, "%s/%s\n", path, fno.fname);
//                printf("%s/%s\n", path, fno.fname);

            }
        }
        f_closedir(&dir);
    }

    return res;
}


#endif

/* Private variables ---------------------------------------------------------*/
//
//// We get nasty and look at some internal structures - get the relevant information
//#include "src/ginput/ginput_driver_mouse.h"
//
//static GConsoleObject     gc;
//static font_t         font;
//static coord_t          bHeight;
//static GHandle          ghc;
//static coord_t          swidth, sheight;
//
//#if !GWIN_CONSOLE_USE_FLOAT
//  #error "You need to enable float support for the console widget. (GWIN_CONSOLE_USE_FLOAT)"
//#endif
//
//int main(void) {
//  GMouse*         m;
//  RCC_Init();
//  // Initialize everything
//  gfxInit();
//
//  // Get the display dimensions
//  swidth = gdispGetWidth();
//  sheight = gdispGetHeight();
//
//  // Create our title
//  font = gdispOpenFont("UI2");
//  gwinSetDefaultFont(font);
//  bHeight = gdispGetFontMetric(font, fontHeight)+4;
//  gdispFillStringBox(0, 0, swidth, bHeight, "Touchscreen Calibration Grabber", font, Red, White, justifyCenter);
//  gdispSetBacklight(100);
//  // Create our main display writing window
//  {
//    GWindowInit       wi;
//
//    gwinClearInit(&wi);
//    wi.show = TRUE; wi.x = 0; wi.y = bHeight; wi.width = swidth; wi.height = sheight-bHeight;
//    ghc = gwinConsoleCreate(&gc, &wi);
//  }
//
//  // Get access to the GMouse structure
//  m = (GMouse*)gdriverGetInstance(GDRIVER_TYPE_MOUSE, 0);
//  if (!m) {
//    gfxHalt("No mouse instance 0.");
//  }
//  gdispSetBacklight(100);
//  // Print the calibration values
//  gwinPrintf(ghc, "\r\n\n");
//  gwinPrintf(ghc, "  ax: %f\r\n", m->caldata.ax);
//  gwinPrintf(ghc, "  bx: %f\r\n", m->caldata.bx);
//  gwinPrintf(ghc, "  cx: %f\r\n", m->caldata.cx);
//  gwinPrintf(ghc, "  ay: %f\r\n", m->caldata.ay);
//  gwinPrintf(ghc, "  by: %f\r\n", m->caldata.by);
//  gwinPrintf(ghc, "  cy: %f\r\n", m->caldata.cy);
//
//  while(1) {
//
//    // Always sleep a bit first to enable other events. We actually don't mind missing events.
//    gfxSleepMilliseconds(100);
//  }
//}
  FATFS f;
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
extern GListener glistener;
int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* Configure the system clock */
  RCC_Init();
  Board_LED_Pin_Init();
  Button_Pin_Init();
  SDCard_Init();             /* Initialize SPI */
  /* Initialize all configured peripherals */

  gfxInit();

  gdispSetBacklight(100);
  gdispSetContrast(100);

  geventListenerInit(&glistener);
  gwinAttachListener(&glistener);

  guiCreate();


  uint8_t res = 0;
  extern GHandle ghConsole1;

  res = f_mount(&f, "0", 0);
  gwinPrintf(ghConsole1, "MOUNT %s\n", f_res_msg(res));

  res = scan_files("");
  gwinPrintf(ghConsole1, "SCAN %s\n", f_res_msg(res));

#if 1
#if 1
  char s1[200] = "String 1";
  char s2[200] = "String 2";
  FIL f1, f2;
  UINT size = 0;
  UINT num = 0;

  res = f_open(&f1, "newfile.txt", FA_READ);
  gwinPrintf(ghConsole1, "F1 OPEN %s \n",  f_res_msg(res));
  size = f_size(&f1);

  res = f_read(&f1, s1, size, &num);
  gwinPrintf(ghConsole1, "F1 READ %s %d\n", f_res_msg(res), num);

   gwinPrintf(ghConsole1, "F1 SIZE %d\n", size);
  f_close(&f1);
#endif

#if 1
  res = f_mkdir("my_dir");
  gwinPrintf(ghConsole1, "MKDIR %s\n", f_res_msg(res));
  res = f_open(&f2, "my_dir/myfile1.txt", FA_WRITE|FA_CREATE_ALWAYS);
  gwinPrintf(ghConsole1, "F2 OPEN %s \n",  f_res_msg(res));
  res = f_write(&f2, s1, size, &num);
  gwinPrintf(ghConsole1, "F2 WRITE %s %d\n", f_res_msg(res), num);
  f_close(&f2);

  res = f_open(&f2, "my_dir/myfile1.txt", FA_READ);
  gwinPrintf(ghConsole1, "F2 OPEN %s \n",  f_res_msg(res));
  size = f_size(&f2);
  res = f_read(&f2, s2, size, &num);
  f_close(&f2);
  gwinPrintf(ghConsole1, "F2 SIZE %d\n", size);
  gwinPrintf(ghConsole1, "F2 READ %s %d\n", f_res_msg(res), num);

  gwinPrintf(ghConsole1, "S1 %s\nS2 %s\n", s1, s2);

  DIR dir;
  res = f_opendir(&dir, "my_dir");
  gwinPrintf(ghConsole1, "OPEN_DIR %s\n", f_res_msg(res));
  FILINFO fno;

  res = f_readdir(&dir, &fno);
  gwinPrintf(ghConsole1, "READ_DIR %s\n", f_res_msg(res));
  gwinPrintf(ghConsole1, "%d %s\n", fno.fsize, fno.fname);
  res = f_readdir(&dir, &fno);
  gwinPrintf(ghConsole1, "READ_DIR %s\n", f_res_msg(res));
  gwinPrintf(ghConsole1, "%d %s\n", fno.fsize, fno.fname);
  res = f_closedir(&dir);
  gwinPrintf(ghConsole1, "CLOSE_DIR %s\n", f_res_msg(res));
#endif
#endif





  while (1) {
    guiEventLoop();
  }

  return 0;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while(1) 
  {
      LED_ON();
  }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

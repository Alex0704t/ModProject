/**
  ******************************************************************************
  * @file    it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "systick.h"
/* External variables --------------------------------------------------------*/


/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{

}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{

  while (1)
  {
  }

}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{

  while (1)
  {
  }

}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{

  while (1)
  {
  }

}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{

}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{

}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{

}

/**
* @brief This function handles System tick timer.
*/


void SysTick_Handler(void)
{
  Inc_Tick();
  disk_timerproc();
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles DMA1 stream3 global interrupt.
*/
void DMA1_Stream3_IRQHandler(void)
{


}

/**
* @brief This function handles DMA1 stream4 global interrupt.
*/
void DMA1_Stream4_IRQHandler(void)
{


}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void)
{

  if (TIM7->SR & TIM_SR_UIF)
    {
      TIM7->SR &= ~TIM_SR_UIF;
      usIncTick();
    }

}

/**
* @brief This function handles DMA2 stream0 global interrupt.
*/
void DMA2_Stream0_IRQHandler(void)
{
  if (DMA2->LISR & DMA_LISR_TCIF0) {//check transfer complete
    DMA2->LIFCR |= DMA_LIFCR_CTCIF0;//clear interrupt flag
    DMA2_Stream0->CR &= ~DMA_SxCR_EN;//stream disable
    }
}

/**
* @brief This function handles DMA2 stream3 global interrupt.
*/
void DMA2_Stream3_IRQHandler(void)
{
  if (DMA2->LISR & DMA_LISR_TCIF3) {//check transfer complete
    DMA2->LIFCR |= DMA_LIFCR_CTCIF3;//clear interrupt flag
    while (!(SPI1->SR & SPI_SR_TXE));
    while ((SPI1->SR & SPI_SR_BSY));//wait for transmit complete
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;//stream disable
  }
}
/**
* @brief This function handles USB On The Go FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{

}

/**
* @brief This function handles touchscreen PENIRQ global interrupt.
*/
void EXTI9_5_IRQHandler(void)
{
  if ((EXTI->PR & EXTI_PR_PR6) == EXTI_PR_PR6)
  {
      EXTI->PR |= EXTI_PR_PR6;//clear pending bit of set 1
      LED_TOGGLE();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
